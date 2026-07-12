# Actuators

Actuators turn ESP32 control signals into action in the real world.

## 1. Common Actuators

### 1.1. Relay

Useful for fans, lights, pumps, and other higher-power loads.

### 1.2. Servo

Useful for angle control, robot arms, and pointing mechanisms.

### 1.3. DC Motor

Useful for fans, small vehicles, and any continuously rotating mechanism.

### 1.4. Stepper Motor

Useful when position control matters.

## 2. Important Points

1. Control signal and load power are not the same thing.
2. Driver chips are often necessary.
3. Do not let a GPIO pin directly drive a large current device.
