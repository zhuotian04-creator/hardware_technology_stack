# I2C

I2C is one of the most common ways to connect sensors in the training camp. It is often used for OLEDs, temperature and humidity sensors, IMUs, and IO expanders.

## 1. Basic Idea

I2C only needs two signal lines:

- `SDA`
- `SCL`

## 2. Typical Devices

- OLED display
- Temperature and humidity sensor
- Accelerometer and gyroscope
- IO expander

## 3. Learning Goals

1. Connect SDA and SCL correctly.
2. Understand what a device address is.
3. Use a scan sketch to find devices.
4. Know why pull-up resistors matter.

## 4. Important Note

I2C is great for connecting multiple devices with few wires, but the address and logic level must be checked before wiring.
