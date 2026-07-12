# UART

UART 是最适合训练营前期接触的通信协议之一，因为它和串口监视器关系最直接。

## 1. UART 能做什么

- 和电脑交换调试数据
- 和 GPS 模块通信
- 和语音模块通信
- 和串口类外设通信

## 2. 基本概念

UART 通常只需要：

- `TX`
- `RX`
- `GND`

## 3. 示例思路

```cpp
HardwareSerial my_serial(1);

void setup() {
  Serial.begin(115200);
  my_serial.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  my_serial.println("hello");
  delay(1000);
}
```

## 4. 你应该掌握什么

1. TX 和 RX 分别是什么意思。
2. 为什么串口通信要共地。
3. 什么是波特率。
4. 为什么硬件串口比软件模拟更稳定。
