# SPI

SPI 适合高速通信场景，常见于 TFT 显示屏、SD 卡、RFID 模块和部分高速传感器。它比 I2C 占用更多引脚，但速度更快，也更适合传输大量数据。

## 1. 基本概念

SPI 常见信号线包括：

- `MOSI`：主设备发给从设备
- `MISO`：从设备发给主设备
- `SCK`：时钟
- `CS`：片选，也常写作 `SS`

ESP32 常用 VSPI 引脚：

| 信号 | 常用 GPIO |
|---|---|
| MOSI | GPIO 23 |
| MISO | GPIO 19 |
| SCK | GPIO 18 |
| CS | GPIO 5 |

`CS` 用来选择当前要通信的设备。一条 SPI 总线可以共用 MOSI、MISO、SCK，但每个设备通常需要独立的 CS 引脚。

## 2. 典型应用

- TFT 彩屏
- SD 卡模块
- RFID 读卡器
- 高速 ADC 或传感器

## 3. 示例思路

以 SD 卡模块为例，先确认模块能否初始化。

```cpp
#include <SPI.h>
#include <SD.h>

const int chipSelect = 5;

void setup() {
  Serial.begin(115200);

  if (!SD.begin(chipSelect)) {
    Serial.println("SD card init failed");
    return;
  }

  Serial.println("SD card ready");
}

void loop() {
}
```

不同模块的库不一样，但排查顺序基本相同：供电、共地、线序、CS 引脚、库配置。

## 4. 常见问题

1. MOSI 和 MISO 接反会导致初始化失败。
2. CS 引脚写错时，设备通常没有响应。
3. 部分 SD 卡模块需要稳定供电，不能只看电源灯是否亮。
4. 多个 SPI 设备共线时，每个设备的 CS 都要正确拉高或拉低。

## 5. 学习目标

1. 明白主设备和从设备。
2. 明白 `CS` 的作用。
3. 知道 SPI 一般比 I2C 更快。
4. 能根据初始化失败信息反查接线和配置。
