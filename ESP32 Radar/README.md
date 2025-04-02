# ESP32 Ultrasonic Radar System

<div align="center">
  <img src="assets/radar-control.jpg" alt="Radar Control Interface" width="300"/>
  <img src="assets/radar-display.jpg" alt="Radar Display" width="300"/>
</div>

## 📡 Overview

This project implements a fully functional radar-like system using an ESP32 microcontroller and an ultrasonic sensor (HC-SR04). The system rotates the sensor using a servo motor to scan the surrounding area and visualizes detected objects on a web interface accessible from any device on the same network. Perfect for robotics projects, security systems, or educational purposes!

## ✨ Features

- **360° Scanning**: Servo-controlled ultrasonic sensor provides full area coverage
- **Real-time Visualization**: Beautiful radar-style interface shows detected objects
- **Mobile Control**: Adjust settings and view results from any web browser
- **Configurable Parameters**: Customize scan speed, distance thresholds, and more
- **Manual or Automatic Operation**: Use auto-scan or manually control the radar angle
- **Visual Alerts**: LED indicators for object proximity warnings

## 🛠️ Hardware Requirements

| Component | Purpose | Quantity |
|-----------|---------|----------|
| ESP32 Development Board | Main controller | 1 |
| HC-SR04 Ultrasonic Sensor | Distance measurement | 1 |
| SG90/MG995 Servo Motor | Radar rotation | 1 |
| Green LED | Safe distance indicator | 1 |
| Red LED | Proximity warning indicator | 1 |
| KY-023 Joystick Module (optional) | Manual control | 1 |
| Resistors (220Ω, 1kΩ, 2kΩ) | LED current limiting & voltage divider | 3-5 |
| Breadboard & Jumper Wires | Connections | As needed |
| Power Supply (5V) | Power source | 1 |

## 📝 Wiring Diagram

### Ultrasonic Sensor (HC-SR04) Connections
- VCC → ESP32 5V
- GND → ESP32 GND
- Trig → ESP32 GPIO 5
- Echo → ESP32 GPIO 18 (Use voltage divider for 5V→3.3V conversion)

### Servo Motor Connections
- Red (Power) → ESP32 5V
- Brown/Black (GND) → ESP32 GND
- Yellow/Orange (Signal) → ESP32 GPIO 13

### LED Connections
- Green LED (+) → 220Ω resistor → ESP32 GPIO 23
- Red LED (+) → 220Ω resistor → ESP32 GPIO 22
- Both LEDs (-) → ESP32 GND

### Joystick Module (Optional)
- VCC → ESP32 3.3V
- GND → ESP32 GND
- X-axis → ESP32 GPIO 34
- Y-axis → ESP32 GPIO 35
- Button → ESP32 GPIO 32

## 📚 Software Requirements

### Libraries
```
ESP32Servo
ESPAsyncWebServer
AsyncTCP
WebSocketsServer
```

### Installation Instructions
1. Install Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Add ESP32 board support:
   - Go to File → Preferences
   - Add `https://dl.espressif.com/dl/package_esp32_index.json` to Additional Boards Manager URLs
   - Go to Tools → Board → Boards Manager
   - Search for ESP32 and install
3. Install required libraries:
   - Go to Sketch → Include Library → Manage Libraries
   - Search and install all required libraries listed above

## 💻 Code Setup

1. Clone this repository:
```bash
git clone https://github.com/yourusername/esp32-radar-system.git
```

2. Open `ESP32_Radar_System.ino` in Arduino IDE

3. Modify WiFi credentials:
```cpp
const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";
```

4. Upload the code to your ESP32

## 📱 Usage Instructions

1. Power on your ESP32 system
2. Check Serial Monitor (115200 baud) for the assigned IP address
3. Connect your smartphone/computer to the same WiFi network
4. Open a web browser and enter the ESP32's IP address
5. The radar control interface will appear as shown below:

<div align="center">
  <img src="assets/radar-control.jpg" alt="Radar Control Interface" width="400"/>
</div>

### Control Panel Features

- **Distance**: Shows current detected object distance in cm
- **Angle**: Shows current servo/sensor position in degrees
- **Speed**: Controls radar rotation speed (1-5)
- **Angle Buttons**: Click to manually position radar at specific angles
- **Auto Scan Toggle**: Enable/disable automatic scanning

6. The radar display shows detected objects in real-time:

<div align="center">
  <img src="assets/radar-display.jpg" alt="Radar Display" width="400"/>
</div>

## 🚀 How It Works

1. The ESP32 creates a WiFi access point or connects to your network
2. The ultrasonic sensor measures distance by emitting sound waves and measuring echo time
3. The servo motor rotates the sensor to scan in different directions
4. Distance and angle data are sent to the web interface via WebSockets
5. The web interface visualizes the data using HTML5 Canvas and JavaScript
6. LEDs provide physical feedback based on detected object proximity

## 🔍 Troubleshooting

| Problem | Possible Solution |
|---------|------------------|
| ESP32 not connecting to WiFi | Check SSID and password in code |
| Servo not moving | Verify wiring and ensure adequate power supply |
| Ultrasonic sensor readings unstable | Check wiring, try adding delay between readings |
| Web interface not loading | Ensure device is on same network as ESP32 |
| Incorrect distance readings | Adjust the calculation formula in code |

## 🔧 Customization

### Hardware Modifications
- Add more sensors for improved accuracy
- Use a higher-torque servo for smoother movement
- Integrate into a custom enclosure for better aesthetics

### Software Customizations
- Modify `MAX_DISTANCE` in code to change detection range
- Adjust `SCAN_STEP` to change scanning resolution
- Edit CSS in the HTML file to customize the web interface

## 🌐 Advanced Features

### Data Logging
Uncomment the SD card code sections to enable data logging of all radar readings.

### Multiple Sensor Support
Modify the code to support multiple ultrasonic sensors for better coverage.

### Alert System
Integrate with IFTTT or other notification services to send alerts when objects are detected.

## 📊 Performance

- Detection Range: 2-400 cm
- Angular Resolution: 1° (adjustable)
- Scan Speed: Full 360° scan in 10-60 seconds (depending on settings)
- Refresh Rate: Up to 20 updates per second on web interface

## 📎 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📧 Contact

If you have any questions or suggestions, please open an issue or contact me at - reganddev@gmail.com

---

Made by [Regan]