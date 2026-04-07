# ESP32 NTP Clock with SSD1306 OLED

This project displays the current time from an NTP server on a SSD1306 OLED screen using an ESP32.

## Features

* Connects to Wi-Fi
* Syncs time from an NTP server
* Displays the current local time on a 128x64 SSD1306 OLED
* Uses custom I2C pins:

  * **SDA:** GPIO 22
  * **SCL:** GPIO 21

## Hardware Requirements

* ESP32 development board
* SSD1306 OLED display (I2C, usually address `0x3C`)
* Wi-Fi network
* Jumper wires

## Wiring

| OLED Pin | ESP32 Pin |
| -------- | --------- |
| VCC      | 3.3V      |
| GND      | GND       |
| SDA      | GPIO 22   |
| SCL      | GPIO 21   |

## Required Libraries

Install these libraries in the Arduino IDE:

* `Adafruit GFX Library`
* `Adafruit SSD1306`
* `WiFi` and `time.h` are included with the ESP32 core

## Setup

1. Install the ESP32 board package in the Arduino IDE.
2. Install the required Adafruit libraries.
3. Open the sketch.
4. Replace the Wi-Fi credentials:

```cpp
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

5. Upload the code to your ESP32.

## How It Works

The ESP32 connects to Wi-Fi, requests time from `pool.ntp.org`, and displays the formatted local time on the OLED.

The time zone is set for Germany using:

```cpp
const char* tzInfo = "CET-1CEST,M3.5.0/2,M10.5.0/3";
```

This automatically handles daylight saving time.

## Notes

* Make sure your OLED uses the I2C address `0x3C`. Some displays may use a different address.
* If the display stays blank, check your wiring and power supply.
* If the time does not update, confirm that the ESP32 is connected to Wi-Fi.

## Example Output

The display shows the time in `HH:MM:SS` format and refreshes every second.

## License

You can use and modify this project freely for personal or educational use.
