#include <Adafruit_NeoPixel.h>

// 8 颗 WS2812B 灯珠，DI 接 ESP32 GPIO18。
// Arduino IDE 需要先安装库：Adafruit NeoPixel。
const int LED_PIN = 18;
const int LED_COUNT = 8;
const int BRIGHTNESS = 40;  // 0-255，开发测试先限制亮度，减小供电压力。

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

enum EffectMode {
  EFFECT_RAINBOW = 0,
  EFFECT_CHASE = 1,
  EFFECT_BREATH = 2,
  EFFECT_STATUS = 3,
  EFFECT_STATIC = 4
};

EffectMode currentMode = EFFECT_RAINBOW;
uint32_t staticColor;

unsigned long lastFrameTime = 0;
unsigned long lastReportTime = 0;
int frameIndex = 0;
int breathValue = 0;
int breathDirection = 1;

void setAll(uint32_t color) {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void selfTest() {
  Serial.println("Self test: red, green, blue, white, off");

  setAll(strip.Color(255, 0, 0));
  delay(500);
  setAll(strip.Color(0, 255, 0));
  delay(500);
  setAll(strip.Color(0, 0, 255));
  delay(500);
  setAll(strip.Color(255, 255, 255));
  delay(500);
  setAll(strip.Color(0, 0, 0));
  delay(300);
}

void showRainbow() {
  for (int i = 0; i < LED_COUNT; i++) {
    int hue = (frameIndex * 256 + i * 65536L / LED_COUNT) & 65535;
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue)));
  }
  strip.show();
  frameIndex = (frameIndex + 1) % 256;
}

void showChase() {
  strip.clear();

  int head = frameIndex % LED_COUNT;
  strip.setPixelColor(head, strip.Color(255, 80, 0));
  strip.setPixelColor((head + LED_COUNT - 1) % LED_COUNT, strip.Color(40, 5, 0));
  strip.setPixelColor((head + LED_COUNT - 2) % LED_COUNT, strip.Color(8, 1, 0));

  strip.show();
  frameIndex++;
}

void showBreath() {
  breathValue += breathDirection * 5;

  if (breathValue >= 180) {
    breathValue = 180;
    breathDirection = -1;
  }

  if (breathValue <= 0) {
    breathValue = 0;
    breathDirection = 1;
  }

  setAll(strip.Color(0, 0, breathValue));
}

void showStatusMeter() {
  strip.clear();

  int litCount = frameIndex % (LED_COUNT + 1);
  for (int i = 0; i < litCount; i++) {
    if (i < 3) {
      strip.setPixelColor(i, strip.Color(0, 180, 0));
    } else if (i < 6) {
      strip.setPixelColor(i, strip.Color(180, 120, 0));
    } else {
      strip.setPixelColor(i, strip.Color(180, 0, 0));
    }
  }

  strip.show();
  frameIndex++;
}

void printHelp() {
  Serial.println();
  Serial.println("WS2812B RGB board ready.");
  Serial.println("Wiring: 5V -> 4-7VDC, GND common, GPIO18 -> 330R -> DI.");
  Serial.println("Commands:");
  Serial.println("  0/rainbow  rainbow flow");
  Serial.println("  1/chase    chasing light");
  Serial.println("  2/breath   blue breathing light");
  Serial.println("  3/meter    status meter demo");
  Serial.println("  4/static   static color");
  Serial.println("  r/g/b/w    red, green, blue, white");
  Serial.println("  off        turn off");
  Serial.println();
}

void handleCommand(String command) {
  command.trim();
  command.toLowerCase();

  if (command.length() == 0) {
    return;
  }

  frameIndex = 0;

  if (command == "0" || command == "rainbow") {
    currentMode = EFFECT_RAINBOW;
    Serial.println("Mode: rainbow");
  } else if (command == "1" || command == "chase") {
    currentMode = EFFECT_CHASE;
    Serial.println("Mode: chase");
  } else if (command == "2" || command == "breath") {
    currentMode = EFFECT_BREATH;
    breathValue = 0;
    breathDirection = 1;
    Serial.println("Mode: breath");
  } else if (command == "3" || command == "meter") {
    currentMode = EFFECT_STATUS;
    Serial.println("Mode: status meter");
  } else if (command == "4" || command == "static") {
    currentMode = EFFECT_STATIC;
    staticColor = strip.Color(255, 80, 0);
    setAll(staticColor);
    Serial.println("Mode: static amber");
  } else if (command == "r" || command == "red") {
    currentMode = EFFECT_STATIC;
    staticColor = strip.Color(255, 0, 0);
    setAll(staticColor);
    Serial.println("Color: red");
  } else if (command == "g" || command == "green") {
    currentMode = EFFECT_STATIC;
    staticColor = strip.Color(0, 255, 0);
    setAll(staticColor);
    Serial.println("Color: green");
  } else if (command == "b" || command == "blue") {
    currentMode = EFFECT_STATIC;
    staticColor = strip.Color(0, 0, 255);
    setAll(staticColor);
    Serial.println("Color: blue");
  } else if (command == "w" || command == "white") {
    currentMode = EFFECT_STATIC;
    staticColor = strip.Color(255, 255, 255);
    setAll(staticColor);
    Serial.println("Color: white");
  } else if (command == "off") {
    currentMode = EFFECT_STATIC;
    staticColor = strip.Color(0, 0, 0);
    setAll(staticColor);
    Serial.println("Color: off");
  } else if (command == "help" || command == "?") {
    printHelp();
  } else {
    Serial.println("Unknown command. Type help.");
  }
}

void updateEffect() {
  unsigned long now = millis();

  if (now - lastFrameTime < 50) {
    return;
  }
  lastFrameTime = now;

  if (currentMode == EFFECT_RAINBOW) {
    showRainbow();
  } else if (currentMode == EFFECT_CHASE) {
    showChase();
  } else if (currentMode == EFFECT_BREATH) {
    showBreath();
  } else if (currentMode == EFFECT_STATUS) {
    showStatusMeter();
  } else {
    setAll(staticColor);
  }
}

void reportStatus() {
  unsigned long now = millis();

  if (now - lastReportTime >= 5000) {
    lastReportTime = now;
    Serial.println("Running. Type help for commands.");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.clear();
  strip.show();

  staticColor = strip.Color(255, 80, 0);

  printHelp();
  selfTest();
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    handleCommand(command);
  }

  updateEffect();
  reportStatus();
}
