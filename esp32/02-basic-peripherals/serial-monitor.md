# Serial Monitor

The serial monitor is one of the most important debugging windows in the ESP32 course. Many problems can be found by reading serial output before touching any advanced tool.

## 1. What It Can Do

- Print debug messages
- Show sensor values
- Verify whether the program is running
- Check whether initialization succeeds
- Observe state changes

## 2. Basic Use

```cpp
void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 is ready");
}

void loop() {
  Serial.println("loop running");
  delay(1000);
}
```

## 3. Debugging Habits

1. Print key messages in `setup()`.
2. Add clear messages for each major step.
3. Check the baud rate when output looks wrong.
4. Keep output simple and useful.

## 4. Good Habits to Build

1. Plan what to print before writing code.
2. Read serial output before changing code.
3. Treat serial output as the first debugging tool.
