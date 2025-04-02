# 📌 ESP32 Wiring Connections

This document provides a clear and structured wiring guide for connecting various components to an **ESP32** microcontroller.

## 🔗 **Component Wiring Table**

| **Component**              | **ESP32 Pin**  | **Description**                                      |
|----------------------------|---------------|--------------------------------------------------|
| **🔊 Ultrasonic Sensor (HC-SR04)**  |               |                                                   |
| **VCC**                    | 3.3V / 5V     | Power (Use **5V** for better range)               |
| **GND**                    | GND           | Ground                                            |
| **Trig**                   | GPIO 5        | Trigger signal                                    |
| **Echo**                   | GPIO 18       | Echo response (**Use voltage divider if needed**) |
| **⚙️ Servo Motor**            |               |                                                   |
| **VCC**                    | 5V            | Power                                             |
| **GND**                    | GND           | Ground                                            |
| **Signal**                 | GPIO 13       | Servo control signal                              |
| **💡 LEDs (Green & Red)**      |               |                                                   |
| **Green LED (+)**          | GPIO 23       | Turns on when **safe**                            |
| **Red LED (+)**            | GPIO 22       | Turns on when **object is too close**            |
| **GND (Both LEDs)**        | GND           | Common ground                                     |
| **🎮 Joystick Module**       |               |                                                   |
| **VCC**                    | 3.3V / 5V     | Power                                             |
| **GND**                    | GND           | Ground                                            |
| **X-axis**                 | GPIO 34       | Reads joystick **X** position                     |
| **Y-axis**                 | GPIO 35       | Reads joystick **Y** position                     |
| **SW (Switch)**            | GPIO 32       | Detects button press                              |

## ⚠️ **Important Notes**
- The **Echo pin (HC-SR04)** operates at **5V**, while ESP32 uses **3.3V logic**. Use a **voltage divider** (1kΩ + 2kΩ resistors) to step down the signal before connecting to GPIO 18.
- The **Servo Motor** should be powered from **5V** (ESP32’s 5V pin or an external power supply).
- The **Joystick** uses **analog pins** (GPIO 34 & 35) for position detection.

---

### ✅ **Follow this wiring to ensure correct setup!**

For any issues, feel free to create a **GitHub Issue** in this repository. 🚀

