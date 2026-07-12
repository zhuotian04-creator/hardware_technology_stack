# Basic Peripherals

This stage starts the most common ESP32 hardware peripherals. The goal is not to memorize parameters, but to make LEDs, buttons, buzzers, and analog signals actually work.

## 1. What This Stage Covers

### 1.1. Order

1. [GPIO](./gpio.md)
2. [ADC and PWM](./adc-and-pwm.md)
3. [Serial Monitor](./serial-monitor.md)

### 1.2. Learning Goals

After this stage, learners should be able to:

1. Control LEDs and relays with GPIO
2. Read button input and handle debouncing
3. Use interrupts for external events
4. Read analog signals and potentiometer values
5. Use PWM for brightness and motor speed
6. Use the serial monitor for debugging output

## 2. Key Ideas

### 2.1. GPIO

GPIO is the main bridge between ESP32 and the outside world.

### 2.2. ADC

ADC reads analog values and is useful for potentiometers, light sensors, and analog temperature sensors.

### 2.3. PWM

PWM is used for LED dimming, motor speed, and buzzer tone control.

### 2.4. Serial Debugging

The serial monitor is the most basic and important debugging tool in early training.
