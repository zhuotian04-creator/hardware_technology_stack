# Wi-Fi

Wi-Fi 是 ESP32 最有代表性的能力之一。训练营里最先要做的，是让开发板连上网络，并能在断线后重新连接。

## 1. 常见模式

### 1.1. STA 模式

ESP32 连接到路由器或手机热点，像手机、电脑一样成为局域网里的一个设备。

### 1.2. AP 模式

ESP32 自己开启热点，手机或电脑直接连接到它。这个模式适合配网、现场调试和离线控制。

## 2. 连接 Wi-Fi

```cpp
#include <WiFi.h>

const char* ssid = "your-wifi-name";
const char* password = "your-wifi-password";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
}
```

上传前把 `ssid` 和 `password` 改成自己的网络信息。训练营里建议先用手机热点测试，排除路由器隔离、频段等问题。

## 3. 断线检查

项目不能只在 `setup()` 里连接一次。长期运行时，`loop()` 里需要检查连接状态。

```cpp
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi lost, reconnecting");
    WiFi.reconnect();
    delay(1000);
  }
}
```

后续项目可以把重连逻辑改成 `millis()` 非阻塞写法，避免网络等待影响传感器读取。

## 4. 常见用途

- 获取天气数据
- 同步网络时间
- 对接物联网平台
- 提供 Web 控制页面
- 上传传感器数据

## 5. 学习重点

1. 会连接网络。
2. 会查看本机 IP。
3. 会检查连接状态。
4. 知道“连上网”不是结束，还要处理断线和重连。
