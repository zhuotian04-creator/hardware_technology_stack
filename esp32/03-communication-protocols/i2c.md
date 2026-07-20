# I2C

I2C 是训练营里最常见的传感器连接方式之一，适合 OLED、温湿度传感器、IMU、IO 扩展芯片等设备。它的优势是线少，一条总线上可以挂多个设备。

## 1. 基本概念

I2C 只需要两根信号线：

- `SDA`：数据线
- `SCL`：时钟线

ESP32 常用默认引脚是：

| 信号 | 常用 GPIO |
|---|---|
| SDA | GPIO 21 |
| SCL | GPIO 22 |

不同开发板可能会标注不同名称，接线前优先看开发板丝印和原理图。

SDA 和 SCL 需要上拉到 3.3V。多数成品模块已经带有上拉电阻；如果总线上完全没有上拉，通信会失败，而并联过多模块也可能让总上拉阻值过小。

## 2. 典型设备

- OLED 显示屏
- AHT20、SHT30、BME280 等环境传感器
- MPU6050、ICM20948 等姿态传感器
- PCF8574、MCP23017 等 IO 扩展芯片

## 3. 地址扫描

第一次连接 I2C 设备时，先运行扫描程序确认设备是否被识别。

```cpp
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  Serial.println("I2C scanner start");
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }
}

void loop() {
}
```

如果串口没有扫描到地址，优先检查供电、GND、SDA/SCL 是否接反。

## 4. 接线检查

1. ESP32 和模块必须共地。
2. 确认模块支持 `3.3V` 电平。
3. SDA 接 SDA，SCL 接 SCL，不要只看线的颜色。
4. 一条总线上多个设备时，地址不能冲突。
5. 长线连接容易不稳定，训练营实验建议先用短杜邦线。

## 5. 学习目标

1. 会连接 SDA 和 SCL。
2. 知道什么是 I2C 设备地址。
3. 会用扫描程序确认设备是否在线。
4. 理解上拉电阻的作用。
5. 能判断“程序问题”和“接线问题”的区别。
