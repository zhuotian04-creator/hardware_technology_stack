# UART

UART is one of the easiest communication protocols to start with because it is closely related to the serial monitor.

## 1. What UART Can Do

- Exchange debug data with a computer
- Talk to GPS modules
- Talk to voice modules
- Communicate with serial-style modules

## 2. Basic Idea

UART usually needs:

- `TX`
- `RX`
- `GND`

## 3. Example Idea

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

## 4. What Learners Should Know

1. What TX and RX mean.
2. Why common ground is required.
3. What baud rate is.
4. Why hardware serial is more stable than software simulation.
