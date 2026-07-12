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

## 3. 学习目标

1. 理解时间差判断。
2. 理解它为什么适合多任务场景。
3. 能拿它代替简单延时。
