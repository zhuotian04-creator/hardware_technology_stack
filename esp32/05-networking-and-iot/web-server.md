# Web 服务器

Web 服务器是 ESP32 训练营里非常适合展示成果的一节。它能让手机或电脑通过浏览器直接控制开发板。

## 1. 能做什么

- 浏览器控制 LED
- 显示传感器数据
- 提供简单配置页面
- 作为局域网控制面板

## 2. 请求和响应

浏览器访问 ESP32 的地址时，会发送一个 HTTP 请求。ESP32 根据访问路径执行动作，再返回网页或文字。

例如：

- 访问 `/`：返回控制页面
- 访问 `/led/on`：点亮 LED
- 访问 `/led/off`：熄灭 LED

## 3. 最小控制示例

先完成 [Wi-Fi](./wifi.md) 的连接实验，再把下面代码中的网络名称和密码换成自己的信息。

```cpp
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "your-wifi-name";
const char* password = "your-wifi-password";
const int ledPin = 2;

WebServer server(80);

void showPage() {
  String page = R"(
    <!doctype html>
    <html lang="zh-CN">
      <meta name="viewport" content="width=device-width,initial-scale=1">
      <body>
        <h1>ESP32 LED</h1>
        <p><a href="/led/on">打开</a></p>
        <p><a href="/led/off">关闭</a></p>
      </body>
    </html>
  )";
  server.send(200, "text/html; charset=utf-8", page);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, showPage);
  server.on("/led/on", HTTP_GET, []() {
    digitalWrite(ledPin, HIGH);
    showPage();
  });
  server.on("/led/off", HTTP_GET, []() {
    digitalWrite(ledPin, LOW);
    showPage();
  });
  server.onNotFound([]() {
    server.send(404, "text/plain; charset=utf-8", "页面不存在");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
```

上传后打开串口监视器，记下打印出的 IP 地址。让手机和 ESP32 连接同一个局域网，再用浏览器访问这个地址。

部分开发板的板载 LED 不是 `GPIO 2`，也可能采用低电平点亮。遇到按钮动作相反或 LED 无反应时，应先查看开发板引脚说明。

## 4. 常见问题

1. 浏览器打不开：确认手机和 ESP32 在同一局域网，并检查 IP 是否发生变化。
2. 页面只能偶尔打开：确认 `loop()` 持续调用了 `server.handleClient()`。
3. 网页能开但硬件不动作：先用单独的 GPIO 程序验证引脚和接线。
4. 路由器开启了设备隔离：改用手机热点进行排查。

## 5. 学习重点

1. 会搭一个最小网页。
2. 会处理按钮点击。
3. 会把页面和硬件动作连起来。
4. 会理解请求和响应。
5. 会根据串口信息排查访问失败的问题。
