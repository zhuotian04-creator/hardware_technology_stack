# 蓝牙

蓝牙适合近距离通信、设备配网和手机交互。

## 1. 经典蓝牙和 BLE

| 类型 | 特点 | 适合场景 |
| --- | --- | --- |
| 经典蓝牙 | 连接方式接近串口，持续传输更直观 | 串口透传、旧设备通信、调试控制 |
| BLE | 功耗低，按服务和特征组织数据 | 传感器、配网、手机应用、低功耗设备 |

不同型号支持范围不同：经典 ESP32 同时支持经典蓝牙和 BLE；ESP32-S2 不支持蓝牙；ESP32-C3、C6、S3 等型号主要使用 BLE。开始实验前应先确认芯片型号，不能只看开发板商品名称；可对照 [Espressif 官方开发板与芯片说明](https://docs.espressif.com/projects/arduino-esp32/en/latest/boards/boards.html)。

## 2. 经典蓝牙串口示例

下面示例适用于支持经典蓝牙 SPP 的 ESP32。手机连接名为 `ESP32-Serial` 的设备后，发送 `1` 或 `0` 控制 LED。

```cpp
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  SerialBT.begin("ESP32-Serial");
  Serial.println("Bluetooth ready");
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();

    if (command == '1') {
      digitalWrite(ledPin, HIGH);
      SerialBT.println("LED on");
    } else if (command == '0') {
      digitalWrite(ledPin, LOW);
      SerialBT.println("LED off");
    }
  }
}
```

如果编译时提示 SPP 不可用，通常不是代码语法问题，而是当前芯片不支持经典蓝牙。这时应改做 BLE 实验。

## 3. BLE 的数据结构

BLE 不是普通无线串口，它通常按下面的层级组织数据：

```text
设备
└── Service（服务）
    ├── Characteristic（可读数据）
    └── Characteristic（可写命令）
```

一个环境传感器可以创建“环境服务”，再用不同特征保存温度、湿度和控制参数。手机读取或订阅特征，就能获得更新。

## 4. BLE 数据示例

下面示例创建一个可读取、可订阅的特征，每秒更新一次模拟量。手机可使用 BLE 调试工具扫描 `ESP32-BLE`，再查找对应服务和特征。

```cpp
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define VALUE_UUID   "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic* sensorValue;
bool deviceConnected = false;

class ConnectionCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* server) {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer* server) {
    deviceConnected = false;
    server->startAdvertising();
  }
};

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ESP32-BLE");

  BLEServer* server = BLEDevice::createServer();
  server->setCallbacks(new ConnectionCallbacks());
  BLEService* service = server->createService(SERVICE_UUID);

  sensorValue = service->createCharacteristic(
    VALUE_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_NOTIFY
  );
  sensorValue->addDescriptor(new BLE2902());
  sensorValue->setValue("ready");

  service->start();
  server->getAdvertising()->addServiceUUID(SERVICE_UUID);
  server->getAdvertising()->start();
  Serial.println("BLE advertising started");
}

void loop() {
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();

    String value = String(analogRead(34));
    sensorValue->setValue(value.c_str());
    if (deviceConnected) {
      sensorValue->notify();
    }
  }
}
```

`GPIO 34` 是经典 ESP32 的示例 ADC 引脚，其他芯片型号应按开发板引脚图修改。真实项目还要处理连接状态、权限、数据格式和配对安全。

## 5. 常见用途

- 手机控制
- 设备配对
- 简单数据传输
- 近距离配置参数
- 低功耗传感器广播

## 6. 调试提示

1. 确认开发板芯片是否支持所选蓝牙类型。
2. Android、iOS 和电脑的蓝牙工具行为可能不同，BLE 应使用 BLE 扫描工具测试。
3. 先只发送短文本，再加入传感器数据或控制协议。
4. 给每条命令设计明确的回复，便于判断设备是否收到。
5. 蓝牙名称、服务 UUID 和命令格式应记录到项目文档。

## 7. 学习重点

1. 知道蓝牙和 Wi-Fi 的差别。
2. 知道蓝牙更适合近距离场景。
3. 能区分经典蓝牙和 BLE。
4. 明白蓝牙常用于设备初始化和辅助控制。
5. 会先根据芯片型号选择正确方案。
