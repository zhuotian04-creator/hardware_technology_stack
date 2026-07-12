# GPIO

GPIO 是 ESP32 最基础的通用输入输出功能。学会 GPIO，才能真正开始控制外部硬件。

## 1. 输出模式

### 1.1. 点亮 LED

```cpp
const int led_pin = 2;

void setup() {
  pinMode(led_pin, OUTPUT);
}

void loop() {
  digitalWrite(led_pin, HIGH);
  delay(500);
  digitalWrite(led_pin, LOW);
  delay(500);
}
```

### 1.2. 常见用途

- 指示灯
- 继电器
- 蜂鸣器
- 电机驱动使能脚

## 2. 输入模式

### 2.1. 读取按键

```cpp
const int button_pin = 0;
const int led_pin = 2;

void setup() {
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  if (digitalRead(button_pin) == LOW) {
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }
}
```

## 3. 需要注意的点

1. 先确认引脚电平是否安全。
2. 需要上拉或下拉时优先用内部电阻。
3. 启动相关引脚不要随便乱接。
4. 传感器和模块的供电电压要对齐。

## 4. 你应该练会什么

1. 配置输出脚。
2. 配置输入脚。
3. 读取按钮状态。
4. 控制 LED 开关。
5. 理解输入和输出的区别。
