# Millis 计时

`millis()` 是 Arduino 和 ESP32 项目里非常实用的非阻塞工具。

## 1. 为什么不用 `delay()`

`delay()` 会让程序在等待期间停住，项目一复杂就很难同时处理多个任务。

## 2. `millis()` 的思路

```cpp
unsigned long last_time = 0;
const unsigned long interval = 1000;

void loop() {
  if (millis() - last_time >= interval) {
    last_time = millis();
    Serial.println("tick");
  }
}
```

判断时要写成 `当前时间 - 上次时间 >= 间隔`。这种写法可以正确处理 `millis()` 计数回绕，不要改成 `当前时间 >= 上次时间 + 间隔`。

## 3. 同时安排多个任务

每个任务保存自己的上次执行时间，就能在一个 `loop()` 中按不同频率运行。

```cpp
const int ledPin = 2;

unsigned long lastBlink = 0;
unsigned long lastReport = 0;
const unsigned long blinkInterval = 500;
const unsigned long reportInterval = 2000;

bool ledState = false;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  if (now - lastBlink >= blinkInterval) {
    lastBlink = now;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }

  if (now - lastReport >= reportInterval) {
    lastReport = now;
    Serial.println("device is running");
  }
}
```

## 4. 常见错误

1. 所有任务共用一个计时变量，导致彼此影响。
2. 定时到了以后忘记更新上次执行时间。
3. 虽然用了 `millis()`，任务内部仍有很长的 `delay()` 或循环等待。
4. 使用 `int` 保存时间，较快发生溢出；时间变量应使用 `unsigned long`。
5. 每轮 `loop()` 都打印日志，串口输出反过来拖慢程序。

## 5. 学习目标

1. 理解时间差判断。
2. 理解它为什么适合多任务场景。
3. 能拿它代替简单延时。
4. 能给多个任务设置互不干扰的更新周期。
