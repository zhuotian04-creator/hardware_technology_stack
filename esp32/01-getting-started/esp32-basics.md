# ESP32 Basics

This page helps learners understand the ESP32 board before they start writing projects.

If the board, power, logic level, pins, and common limitations are clear, GPIO, sensors, and protocols will make much more sense.

## 1. What ESP32 Is

ESP32 is a family of low-cost, low-power microcontrollers from Espressif. Common features include:

- Built-in Wi-Fi
- Built-in Bluetooth
- Rich GPIO support
- ADC, PWM, UART, I2C, and SPI

It is a great choice for:

- Smart hardware
- IoT devices
- Sensor systems
- Wireless control
- Small embedded systems

## 2. Concepts to Know First

### 2.1. GPIO

GPIO is the general-purpose input/output pin used for buttons, LEDs, relays, buzzers, and more.

### 2.2. Logic Level

ESP32 GPIO usually works at `3.3V`.

That means:

1. Most pins should not receive `5V` signals directly.
2. Level shifting is required when connecting `5V` modules.
3. `5V` must not be connected directly to `3.3V` pins.

### 2.3. Input-Only Pins

Some pins are input-only and are common on higher ADC channels or special-purpose pins.

### 2.4. Boot-Related Pins

Some pins affect the boot mode, so they should not be forced to the wrong level by external hardware.

## 3. Common Peripheral Capabilities

| Capability | Use |
| --- | --- |
| GPIO | Input and output control |
| ADC | Read analog signals |
| PWM | Brightness and speed control |
| UART | Serial communication |
| I2C | Sensors and expansion modules |
| SPI | High-speed peripherals |
| Wi-Fi | Wireless networking |
| Bluetooth | Nearby device communication |

## 4. Powering the Board

### 4.1. Common Power Paths

ESP32 development boards are usually powered by:

- USB power
- 5V input pin
- 3.3V input pin

### 4.2. Important Notes

1. Check whether the board already includes a regulator.
2. Never connect `5V` directly to a `3.3V` pin.
3. Do not guess current requirements.
4. For multi-module projects, do a power budget first.

## 5. What to Remember

After finishing this page, a learner should know:

1. What kind of board ESP32 is.
2. What `3.3V` means.
3. Why GPIO is not just "plug and play".
4. Why some pins cannot be used casually.
5. Why power planning matters.

## 6. Next Step

The best next pages are:

- `[Arduino IDE Setup](./arduino-ide.md)`
- `[C++ Basics for ESP32](./cpp-basics.md)`

Build the environment and code basics first, then move into GPIO and peripherals.
