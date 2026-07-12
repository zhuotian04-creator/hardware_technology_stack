# Arduino IDE Setup

Arduino IDE is the best starting environment for beginners in the ESP32 training camp.

It is simple to install, easy to understand, and gives fast feedback for the full loop of writing code, compiling, uploading, and checking serial output.

## 1. Install Arduino IDE

### 1.1. Download

1. Open the [Arduino official download page](https://www.arduino.cc/en/software)
2. Download `Arduino IDE 2.x`
3. Install and launch the program

### 1.2. First Launch

Learners should get familiar with:

- Menu bar
- Side tool area
- Editor area
- Bottom output area
- Serial monitor entry

## 2. Add ESP32 Board Support

Arduino IDE does not include ESP32 support by default. The ESP32 board package must be added manually.

### 2.1. Add the URL

1. Open `File -> Preferences`
2. Find `Additional boards manager URLs`
3. Add this address:

```text
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

4. If there are already other URLs, separate them with commas
5. Click `OK`

### 2.2. Install the Board Package

1. Open `Tools -> Board -> Boards Manager`
2. Search for `esp32`
3. Find the package published by `Espressif Systems`
4. Click `Install`
5. Wait for the installation to finish

## 3. Choose the Board and Port

### 3.1. Board Selection

For a common ESP32 board, the usual starting choice is:

- `ESP32 Dev Module`

### 3.2. Serial Port

1. Use a USB cable that supports data transfer
2. Open `Tools -> Port`
3. Select the matching COM port

## 4. Upload the First Program

### 4.1. Use a Simple Blink Test

The classic blink example is enough for the first test.

### 4.2. Upload Flow

1. Select the correct board
2. Select the correct port
3. Click `Upload`
4. Wait for compile and flashing to finish
5. Check whether the onboard LED blinks

### 4.3. Common Problems

If upload fails, check:

- Whether the USB cable supports data
- Whether the port is correct
- Whether the board model is correct
- Whether the board needs `BOOT` to be held during upload

## 5. Serial Monitor

The serial monitor is one of the most important debugging tools in the ESP32 course.

It can be used to:

- Show program output
- Observe sensor data
- Check debugging messages
- Verify communication

## 6. Practical Goal

This page has two success conditions:

1. Arduino IDE recognizes the ESP32 board.
2. A simple example can be uploaded successfully.

After that, move to `[ESP32 Basics](./esp32-basics.md)` to learn the board itself.
