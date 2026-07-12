# C++ Basics for ESP32

ESP32 students do not need to become C++ experts first, but they do need the small set of C++ basics that show up everywhere in Arduino projects.

This page focuses only on the parts that learners will use repeatedly: variables, constants, conditions, loops, functions, arrays, structures, and the idea of classes.

## 1. Why This Comes First

Arduino code looks short at the beginning. Once a project grows, it quickly needs data handling, repeated logic, modular code, and clean structure.

If these basics are missing, students often copy code without understanding it and struggle to debug later.

## 2. Core Concepts

### 2.1. Variables and Data Types

Variables store data while the program is running.

Common types:

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

### 2.2. Constants

Values that should not change during runtime should be written as constants.

```cpp
const int button_pin = 0;
const unsigned long blink_interval = 1000;
```

### 2.3. Conditions

Conditions let the program choose different actions.

```cpp
if (digitalRead(button_pin) == LOW) {
  digitalWrite(led_pin, HIGH);
} else {
  digitalWrite(led_pin, LOW);
}
```

### 2.4. Loops

Loops repeat work.

```cpp
for (int i = 0; i < 5; i++) {
  Serial.println(i);
}
```

### 2.5. Functions

Functions group repeated logic into a reusable block.

```cpp
void blink_led(int pin) {
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
  delay(500);
}
```

### 2.6. Arrays

Arrays store a group of values with the same type.

```cpp
int sensor_values[] = {10, 20, 30};
```

### 2.7. Structures

Structures bundle related values together.

```cpp
struct SensorData {
  int raw_value;
  float voltage;
};
```

### 2.8. Classes

Classes bundle data and behavior together. In early training, learners only need the basic idea.

## 3. Arduino Style C++

The most common Arduino program structure looks like this:

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

The two most important functions are:

- `setup()`: runs once
- `loop()`: runs repeatedly

## 4. What Learners Should Practice

1. Read and write variables and constants.
2. Use simple `if` statements.
3. Use simple loops.
4. Pull repeated code into a function.
5. Organize data with arrays and structures.
6. Understand what classes are for.

## 5. Why It Matters Later

This foundation helps with:

- GPIO control
- Sensor reading
- Communication wrappers
- State machines
- Multi-file projects
- Modular code design
