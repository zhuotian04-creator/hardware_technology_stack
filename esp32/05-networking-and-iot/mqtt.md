# MQTT

MQTT 是物联网里非常常见的轻量级消息协议，适合设备上报和远程控制。

## 1. 核心概念

- Broker：消息服务器，负责接收和转发消息
- Topic：主题，相当于消息的地址
- Publish：向某个主题发布消息
- Subscribe：订阅主题并接收消息
- Payload：消息携带的实际内容

设备之间通常不直接连接，而是都连接到 Broker。例如：

```text
传感器 ESP32  --发布-->  lab/room1/temperature  --Broker-->  监控页面
控制页面      --发布-->  lab/room1/led/set      --Broker-->  执行器 ESP32
```

## 2. 主题设计

主题最好能看出位置、设备和数据类型。推荐使用统一层级：

```text
lab/room1/esp32-01/temperature
lab/room1/esp32-01/humidity
lab/room1/esp32-01/led/set
lab/room1/esp32-01/status
```

不要把所有数据都发到 `data` 这样的宽泛主题，也不要把密码等敏感信息放进主题或消息。

## 3. 最小客户端结构

在 Arduino IDE 的库管理器中安装 `PubSubClient`。下面示例会连接 Wi-Fi，并演示订阅控制主题与定时上报状态。

```cpp
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "your-wifi-name";
const char* password = "your-wifi-password";
const char* broker = "192.168.1.10";
const int ledPin = 2;

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println(WiFi.localIP());
}

void onMessage(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += static_cast<char>(payload[i]);
  }

  if (String(topic) == "lab/esp32/led/set") {
    digitalWrite(ledPin, message == "on" ? HIGH : LOW);
  }
}

void connectMqtt() {
  while (!mqtt.connected()) {
    String clientId = "esp32-";
    clientId += WiFi.macAddress();
    clientId.replace(":", "");

    if (mqtt.connect(clientId.c_str())) {
      mqtt.subscribe("lab/esp32/led/set");
      mqtt.publish("lab/esp32/status", "online", true);
    } else {
      Serial.printf("MQTT failed, state=%d\n", mqtt.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  connectWiFi();
  mqtt.setServer(broker, 1883);
  mqtt.setCallback(onMessage);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!mqtt.connected()) {
    connectMqtt();
  }
  mqtt.loop();

  static unsigned long lastPublish = 0;
  if (millis() - lastPublish >= 5000) {
    lastPublish = millis();
    mqtt.publish("lab/esp32/heartbeat", "alive");
  }
}
```

把 Wi-Fi 信息和 `broker` 换成自己的配置。正式项目还应加入 MQTT 用户名和密码，并尽量用 `millis()` 安排 Wi-Fi 与 MQTT 重试，避免设备长时间卡在 `while` 中。

## 4. 常见用途

- 上传传感器数据
- 接收远程控制命令
- 对接云平台
- 上报设备在线状态
- 让多个设备共享同一组数据

## 5. 调试顺序

1. 先确认 ESP32 已连接 Wi-Fi。
2. 再确认 Broker 地址和端口可访问。
3. 用 MQTT 客户端工具手动发布、订阅主题。
4. 查看 `mqtt.state()` 的错误码。
5. 最后再接入真实传感器和执行器。

## 6. 学习重点

1. 知道 MQTT 是“发消息”的模型。
2. 知道主题怎么设计。
3. 知道设备和平台之间怎么分工。
4. 会订阅控制消息并发布设备数据。
5. 会处理断线和重复连接。
