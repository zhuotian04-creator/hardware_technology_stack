# ADC 与 PWM

这一页把模拟输入和 PWM 输出放在一起讲，因为它们通常会在同一类项目里出现。

## 1. ADC

ADC 的作用是把模拟电压转换成数字值。

### 1.1. 典型场景

- 电位器
- 光敏电阻
- 模拟温度传感器
- 电池电压检测

### 1.2. 示例

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

PWM 不是“真的调低电压”，而是通过快速开关来模拟平均输出效果。

### 2.1. 典型场景

- LED 调光
- 舵机控制
- 电机调速
- 蜂鸣器发声

### 2.2. 示例

```cpp
const int pwm_pin = 2;
const int pwm_freq = 5000;
const int pwm_resolution = 8;

void setup() {
  ledcAttach(pwm_pin, pwm_freq, pwm_resolution);
}

void loop() {
  for (int duty = 0; duty <= 255; duty++) {
    ledcWrite(pwm_pin, duty);
    delay(10);
  }
  for (int duty = 255; duty >= 0; duty--) {
    ledcWrite(pwm_pin, duty);
    delay(10);
  }
}
```

这个示例使用 `Arduino-ESP32 Core 3.x` 的 [LEDC 接口](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html)。Core 2.x 使用 `ledcSetup()` 和 `ledcAttachPin()`，不要把两套接口混在同一个项目中。

## 3. 学习重点

1. 知道 ADC 读到的是什么。
2. 知道 PWM 解决的是什么问题。
3. 能把原始数据和实际效果联系起来。
4. 明白 ESP32 的引脚和电平限制。
