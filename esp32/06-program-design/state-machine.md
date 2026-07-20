# 状态机

状态机是组织 ESP32 项目的重要方法之一。它特别适合按钮、模式切换、流程控制和多阶段项目。

## 1. 核心思想

把程序分成多个状态，让程序在不同状态下执行不同逻辑。

## 2. 示例场景

- 单击、双击、长按
- 待机、工作、报警
- 自动、手动、设置

## 3. 先画状态转换表

以环境监测设备为例：

| 当前状态 | 触发条件 | 下一个状态 |
| --- | --- | --- |
| 待机 | 串口收到 `s` | 监测 |
| 监测 | 传感器值大于 3000 | 报警 |
| 报警 | 传感器值小于 2500 | 监测 |
| 任意工作状态 | 串口收到 `x` | 待机 |

报警和恢复使用两个不同阈值，可以避免数值在临界点附近波动时反复切换状态。

## 4. 最小示例

```cpp
enum class DeviceState {
  Idle,
  Monitoring,
  Alarm
};

const int sensorPin = 34;
const int ledPin = 2;
DeviceState state = DeviceState::Idle;
unsigned long stateStarted = 0;

void enterState(DeviceState next) {
  state = next;
  stateStarted = millis();
  Serial.printf("state=%d\n", static_cast<int>(state));
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  enterState(DeviceState::Idle);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  char command = Serial.available() ? Serial.read() : '\0';

  switch (state) {
    case DeviceState::Idle:
      digitalWrite(ledPin, LOW);
      if (command == 's') {
        enterState(DeviceState::Monitoring);
      }
      break;

    case DeviceState::Monitoring:
      digitalWrite(ledPin, HIGH);
      if (command == 'x') {
        enterState(DeviceState::Idle);
      } else if (sensorValue > 3000) {
        enterState(DeviceState::Alarm);
      }
      break;

    case DeviceState::Alarm:
      digitalWrite(ledPin, (millis() / 200) % 2);
      if (command == 'x') {
        enterState(DeviceState::Idle);
      } else if (sensorValue < 2500) {
        enterState(DeviceState::Monitoring);
      }
      break;
  }
}
```

示例中的 `GPIO 34` 和阈值只适用于演示，应根据开发板和传感器实测数据调整。输入 `s` 开始监测，输入 `x` 回到待机。

## 5. 编写规则

1. 状态名称要表达设备当前在做什么。
2. 每次切换都集中调用一个入口函数，方便记录日志和初始化状态。
3. 转换条件要明确，同一条件不要散落在多个位置。
4. 状态内部不要使用长时间阻塞等待。
5. 给网络失联、传感器故障等异常情况设计安全状态。

`stateStarted` 可以用来计算进入当前状态后的持续时间，例如报警超过 30 秒后自动关闭执行器。

## 6. 学习目标

1. 知道状态是什么。
2. 知道状态如何切换。
3. 知道状态机比一堆 `if` 更好维护。
4. 能先写状态转换表，再实现程序。
5. 能为异常情况定义安全状态。
