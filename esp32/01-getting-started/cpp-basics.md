# ESP32 的 C++ 基础

ESP32 课程不要求学习者先成为 C++ 专家，但至少要先掌握 Arduino 开发里最常用的一组 C++ 基础。

这一页只讲真正会频繁用到的部分，目标是让学习者能看懂示例、改得动代码、能自己写出小功能。

## 1. 为什么要先学这部分

Arduino 程序看起来很短，但一旦开始做传感器、通信、状态控制和模块化开发，就会不断用到变量、函数、结构体、类和头文件。

如果这些基础不先补上，后面很容易只会“照着抄”，不会真正调试。

## 2. 必备知识

### 2.1. 变量和数据类型

变量用来保存程序运行时的数据。

常见类型包括：

- `int`
- `float`
- `bool`
- `char`
- `String`

```cpp
int led_pin = 2;
float temperature = 26.5;
bool is_ready = true;
```

### 2.2. 常量

不会在运行中改变的值，建议写成常量。

```cpp
const int button_pin = 0;
const unsigned long blink_interval = 1000;
```

### 2.3. 条件判断

条件判断用于根据输入决定程序走向。

```cpp
if (digitalRead(button_pin) == LOW) {
  digitalWrite(led_pin, HIGH);
} else {
  digitalWrite(led_pin, LOW);
}
```

### 2.4. 循环

循环用于重复执行任务。

```cpp
for (int i = 0; i < 5; i++) {
  Serial.println(i);
}
```

### 2.5. 函数

把常用逻辑封装成函数，可以让代码更清楚。

```cpp
void blink_led(int pin) {
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
  delay(500);
}
```

### 2.6. 数组

数组适合保存一组相同类型的数据。

```cpp
int sensor_values[] = {10, 20, 30};
```

### 2.7. 结构体

结构体适合把相关数据放在一起。

```cpp
struct SensorData {
  int raw_value;
  float voltage;
};
```

### 2.8. 类

类是把数据和行为打包在一起的一种组织方式。训练营前期只需要理解基本概念，不必一开始就写复杂类。

## 3. Arduino 里的 C++ 写法

Arduino 工程最常见的结构如下：

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

这里最重要的两个函数是：

- `setup()`，只执行一次
- `loop()`，反复执行

## 4. 学习重点

学习这部分时，优先掌握以下内容：

1. 会看懂变量和常量
2. 会写简单的 `if`
3. 会写简单的循环
4. 会把重复代码提取成函数
5. 会使用数组和结构体组织数据
6. 知道类在工程化开发里是干什么的

## 5. 对后续 ESP32 学习的帮助

这部分学好之后，后面你会更容易理解：

- GPIO 控制
- 传感器读取
- 通信协议封装
- 状态机
- 多文件工程结构
- 模块化代码设计
