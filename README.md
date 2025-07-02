# Smart Watering System IoT

This project is an IoT-based Smart Watering System that reads temperature data using a DHT11 sensor and uploads the data to Firebase Realtime Database via WiFi. The microcontroller used is compatible with the Arduino platform (such as ESP32 or ESP8266).

## Features

- Reads temperature from a DHT11 sensor.
- Connects to WiFi for internet access.
- Sends temperature data to Firebase Realtime Database.
- Includes error handling for sensor reading and Firebase communication.
- Serial output for debugging and status monitoring.

## Requirements

- Arduino-compatible board with WiFi (e.g., ESP32, ESP8266)
- DHT11 temperature and humidity sensor
- Firebase Realtime Database account and project
- Arduino IDE with the following libraries installed:
  - [Firebase ESP Client](https://github.com/mobizt/Firebase-ESP-Client)
  - [DHT sensor library](https://github.com/adafruit/DHT-sensor-library)
  - WiFi library (usually included with board support)

## Hardware Connections

| DHT11 Pin | Arduino/ESP Pin |
|-----------|-----------------|
| VCC       | 3.3V/5V         |
| GND       | GND             |
| DATA      | GPIO 5          |

Make sure to connect the DATA pin of the DHT11 sensor to the GPIO number defined in the code (`#define DHTPIN 5`).

## Configuration

Edit the following in `main.ino` to match your setup:

- **WiFi Credentials**  
  ```c++
  #define WIFI_SSID "YourSSID"
  #define WIFI_PASSWORD "YourPassword"
  ```

- **Firebase API Key & Database URL**  
  ```c++
  #define API_KEY "YourFirebaseAPIKey"
  #define DATABASE_URL "https://your-database-url.firebaseio.com/"
  ```

## How It Works

1. On startup, the device connects to WiFi and initializes Firebase authentication.
2. The DHT11 sensor is initialized.
3. Every 2 seconds, the device reads the temperature from the DHT11 sensor.
4. If the reading is successful, the temperature value is sent to the Firebase Realtime Database under the key `"Suhu"`.
5. Success and failure messages are printed to the serial monitor.

## Example Serial Output

```
DHT11 Test
Connecting to Wi-Fi...
Connected with IP: 192.168.1.100

Firebase Client v4.x.x

Firebase success
Temperature : 29.00 *C 
Data sukses terkirim
```

## Troubleshooting

- If you see "Failed to read sensor..", check your DHT11 wiring and power supply.
- If Firebase communication fails, check your WiFi credentials, API key, and database URL.
- Ensure your device has internet access and your Firebase rules allow data writes.

---

**Note:**  
For production use, avoid hardcoding sensitive information (such as WiFi credentials and API keys) in the source code. Consider using environment variables or secure storage.
