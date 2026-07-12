# ADC and PWM

This page groups analog input and PWM output together because they often appear in the same kind of project.

## 1. ADC

ADC converts analog voltage into a digital value.

### 1.1. Typical Uses

- Potentiometer
- Light sensor
- Analog temperature sensor
- Battery voltage measurement

### 1.2. Example

```cpp
const int adc_pin = 34;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int raw_value = analogRead(adc_pin);
  Serial.println(raw_value);
  delay(200);
}
```

## 2. PWM

PWM does not really lower voltage. It switches a pin very quickly to simulate an average output effect.

### 2.1. Typical Uses

- LED dimming
- Servo control
- Motor speed control
- Buzzer output

### 2.2. Example

```cpp
const int pwm_pin = 2;
const int pwm_channel = 0;
const int pwm_freq = 5000;
const int pwm_resolution = 8;

void setup() {
  ledcSetup(pwm_channel, pwm_freq, pwm_resolution);
  ledcAttachPin(pwm_pin, pwm_channel);
}

void loop() {
  for (int duty = 0; duty <= 255; duty++) {
    ledcWrite(pwm_channel, duty);
    delay(10);
  }
  for (int duty = 255; duty >= 0; duty--) {
    ledcWrite(pwm_channel, duty);
    delay(10);
  }
}
```

## 3. What Learners Should Understand

1. What ADC reads.
2. What PWM solves.
3. How raw values map to real behavior.
4. Why pin and voltage limits matter.
