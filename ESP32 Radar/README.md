# Ultrasonic Radar System with ESP32 & Android Control

## Overview
This project uses an **ESP32**, an **ultrasonic sensor (HC-SR04)**, a **servo motor**, and a **joystick module** to create a radar-like system for detecting objects. The system can be controlled via an **Android device** and displays real-time data on a web-based UI.

---

## Components Used
| Component | Model |
|-----------|--------|
| Microcontroller | ESP32 |
| Ultrasonic Sensor | HC-SR04 |
| Servo Motor | SG90 / MG995 |
| LEDs | Green & Red |
| Joystick Module | KY-023 |
| Resistors | (if needed for voltage divider on Echo pin) |
| Power Source | 5V USB or Battery |

---

## Wiring Connections
### **Ultrasonic Sensor (HC-SR04)**
| Pin | ESP32 Pin | Description |
|-----|----------|-------------|
| VCC | 3.3V / 5V | Power (Use 5V for better range) |
| GND | GND | Ground |
| Trig | GPIO 5 | Trigger signal |
| Echo | GPIO 18 | Echo response (use voltage divider if needed) |

### **Servo Motor**
| Wire Color | ESP32 Pin | Description |
|------------|----------|-------------|
| Red (VCC) | 5V | Power |
| Brown (GND) | GND | Ground |
| Yellow (PWM) | GPIO 13 | Servo control |

### **LEDs (Green & Red)**
| LED Color | ESP32 Pin | Description |
|-----------|----------|-------------|
| Green LED (+) | GPIO 23 | Turns on when safe |
| Red LED (+) | GPIO 22 | Turns on when object is too close |
| GND (Both LEDs) | GND | Common ground |

### **Joystick Module**
| Pin | ESP32 Pin | Description |
|-----|----------|-------------|
| VCC | 3.3V / 5V | Power |
| GND | GND | Ground |
| X-axis | GPIO 34 | Read joystick X position |
| Y-axis | GPIO 35 | Read joystick Y position |
| SW (Switch) | GPIO 32 | Button press detection |

---

## Required Libraries
To use this project, install the following libraries in **Arduino IDE**:
- **ESPAsyncWebServer**
- **AsyncTCP**
- **Servo.h**
- **WebSocketsServer.h**

### **How to Install Libraries**
1. Open **Arduino IDE**
2. Go to **Sketch** > **Include Library** > **Manage Libraries**
3. Search and install the required libraries

Or, install manually via **GitHub**:
```sh
mkdir -p ~/Arduino/libraries
cd ~/Arduino/libraries
git clone https://github.com/me-no-dev/ESPAsyncWebServer.git
git clone https://github.com/me-no-dev/AsyncTCP.git
git clone https://github.com/Links2004/arduinoWebSockets.git
```

---

## Setting Up in Arduino IDE
1. **Select Board**: ESP32 Dev Module
2. **Set Upload Speed**: 115200
3. **Choose Correct Port**
4. **Upload the Code**

### **Serial Monitor Debugging**
- Open **Serial Monitor** (115200 baud rate)
- Check for WiFi connection and assigned **IP Address**

---

## Connecting to Android
1. **Find ESP32 IP Address** in Serial Monitor
2. Connect Android device to the same WiFi network
3. Open a web browser and enter the ESP32 IP (e.g., `http://192.168.1.100`)
4. The UI will load, allowing you to control the radar system

---

## How to Control
- **Joystick** moves the radar manually
- **Servo Motor** scans the area automatically
- **Ultrasonic Sensor** detects objects and displays distance
- **LEDs** indicate object proximity:
  - **Green** = Safe
  - **Red** = Object too close
- **Web UI** displays real-time radar visualization

---

## Troubleshooting
### **No IP Address Showing?**
- Check WiFi credentials in the code
- Restart ESP32 and check Serial Monitor

### **Servo Motor Not Moving?**
- Ensure correct wiring (PWM to GPIO 13)
- Use an external 5V power source if needed

### **Web UI Not Loading?**
- Ensure ESP32 and phone are on the same network
- Try different browsers (Chrome recommended)

---

## Future Enhancements
- **Bluetooth Control** instead of WiFi
- **Mobile App** integration
- **Advanced Radar UI** with animations

---

## License
This project is open-source under the **MIT License**.

Happy Coding! 🚀

