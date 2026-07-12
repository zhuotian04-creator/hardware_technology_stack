# GPIO

GPIO is the most basic general-purpose input and output feature on ESP32. Once learners understand GPIO, they can begin controlling external hardware for real.

## 1. Output Mode

### 1.1. Blink an LED

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

### 1.2. Common Uses

- Indicator light
- Relay module
- Buzzer
- Motor driver enable pin

## 2. Input Mode

### 2.1. Read a Button

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

## 3. Important Notes

1. Check whether the pin level is safe first.
2. Prefer internal pull-up or pull-down when possible.
3. Do not connect boot-related pins casually.
4. Match the supply voltage of sensors and modules.

## 4. Skills to Practice

1. Configure an output pin.
2. Configure an input pin.
3. Read a button state.
4. Control an LED.
5. Understand the difference between input and output.
