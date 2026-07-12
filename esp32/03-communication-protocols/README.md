# Communication Protocols

ESP32 is strong because it can talk to many external modules. Once learners reach this stage, they begin to understand how devices connect, how data moves, and how protocol choice affects a project.

## 1. What This Stage Covers

### 1.1. Order

1. [UART](./uart.md)
2. [I2C](./i2c.md)
3. [SPI](./spi.md)

### 1.2. Learning Goals

After this stage, learners should be able to:

1. Use UART to talk to a computer, GPS module, or voice module
2. Use I2C to connect OLEDs and sensors
3. Use SPI to connect displays and SD cards
4. Read pin and wiring requirements for each protocol
5. Choose the right protocol for the task

## 2. Quick Comparison

| Protocol | Wires | Speed | Typical Use |
| --- | --- | --- | --- |
| UART | 2 | Medium | Serial communication, debugging |
| I2C | 2 | Medium | Sensors, OLEDs, expansion chips |
| SPI | 4+ | Higher | Displays, SD cards, fast peripherals |
