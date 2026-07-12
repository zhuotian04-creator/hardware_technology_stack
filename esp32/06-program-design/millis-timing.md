# Millis Timing

`millis()` is one of the most practical non-blocking tools in Arduino and ESP32 projects.

## 1. Why Not Use `delay()`

`delay()` stops the program while waiting, which makes multi-task projects hard to manage.

## 2. The Idea Behind `millis()`

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

## 3. Learning Goals

1. Understand time-difference checking.
2. Understand why this fits multitask projects.
3. Use it instead of simple delays.
