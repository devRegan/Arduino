# ESP32 Ultrasonic Radar System

<div align="center">
  <img src="https://raw.githubusercontent.com/yourusername/esp32-radar-system/main/images/control-interface.png" alt="Radar Control Interface" width="400"/>
  <img src="https://raw.githubusercontent.com/yourusername/esp32-radar-system/main/images/radar-display.png" alt="Radar Display" width="400"/>
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

## 📝 Wiring Connections

<div align="center">
  <table>
    <tr>
      <th colspan="3" style="text-align:center; background-color:#f0f0f0; padding:10px;">
        <b>📌 Ultrasonic Sensor (HC-SR04) Connections</b>
      </th>
    </tr>
    <tr>
      <td><b>Sensor Pin</b></td>
      <td><b>ESP32 Pin</b></td>
      <td><b>Notes</b></td>
    </tr>
    <tr>
      <td>VCC</td>
      <td>5V</td>
      <td>Power supply for better range</td>
    </tr>
    <tr>
      <td>GND</td>
      <td>GND</td>
      <td>Common ground</td>
    </tr>
    <tr>
      <td>Trig</td>
      <td>GPIO 5</td>
      <td>Trigger signal output</td>
    </tr>
    <tr>
      <td>Echo</td>
      <td>GPIO 18</td>
      <td>Use voltage divider (5V→3.3V)</td>
    </tr>
  </table>
</div>

<br>

<div align="center">
  <table>
    <tr>
      <th colspan="3" style="text-align:center; background-color:#f0f0f0; padding:10px;">
        <b>🔄 Servo Motor Connections</b>
      </th>
    </tr>
    <tr>
      <td><b>Wire Color</b></td>
      <td><b>ESP32 Pin</b></td>
      <td><b>Notes</b></td>
    </tr>
    <tr>
      <td>Red</td>
      <td>5V</td>
      <td>Power supply</td>
    </tr>
    <tr>
      <td>Brown/Black</td>
      <td>GND</td>
      <td>Common ground</td>
    </tr>
    <tr>
      <td>Yellow/Orange</td>
      <td>GPIO 13</td>
      <td>PWM control signal</td>
    </tr>
  </table>
</div>

<br>

<div align="center">
  <table>
    <tr>
      <th colspan="3" style="text-align:center; background-color:#f0f0f0; padding:10px;">
        <b>💡 LED Connections</b>
      </th>
    </tr>
    <tr>
      <td><b>Component</b></td>
      <td><b>ESP32 Pin</b></td>
      <td><b>Notes</b></td>
    </tr>
    <tr>
      <td>Green LED (+)</td>
      <td>GPIO 23</td>
      <td>Via 220Ω resistor</td>
    </tr>
    <tr>
      <td>Red LED (+)</td>
      <td>GPIO 22</td>
      <td>Via 220Ω resistor</td>
    </tr>
    <tr>
      <td>Both LEDs (-)</td>
      <td>GND</td>
      <td>Common ground</td>
    </tr>
  </table>
</div>

<br>

<div align="center">
  <table>
    <tr>
      <th colspan="3" style="text-align:center; background-color:#f0f0f0; padding:10px;">
        <b>🕹️ Joystick Module Connections (Optional)</b>
      </th>
    </tr>
    <tr>
      <td><b>Module Pin</b></td>
      <td><b>ESP32 Pin</b></td>
      <td><b>Notes</b></td>
    </tr>
    <tr>
      <td>VCC</td>
      <td>3.3V</td>
      <td>Power supply</td>
    </tr>
    <tr>
      <td>GND</td>
      <td>GND</td>
      <td>Common ground</td>
    </tr>
    <tr>
      <td>X-axis</td>
      <td>GPIO 34</td>
      <td>Analog input (ADC)</td>
    </tr>
    <tr>
      <td>Y-axis</td>
      <td>GPIO 35</td>
      <td>Analog input (ADC)</td>
    </tr>
    <tr>
      <td>Button (SW)</td>
      <td>GPIO 32</td>
      <td>Digital input with pull-up</td>
    </tr>
  </table>
</div>

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
5. The radar control interface will load:

<div align="center">
  <img src="https://raw.githubusercontent.com/yourusername/esp32-radar-system/main/images/control-interface.png" alt="Radar Control Interface" width="500"/>
</div>

### Control Panel Features

- **Distance**: Shows current detected object distance (100 cm in example)
- **Angle**: Shows current servo/sensor position (133° in example)
- **Speed**: Controls radar rotation speed (1-5)
- **Angle Buttons**: Click to manually position radar at specific angles (0° to 360°)
- **Auto Scan Toggle**: Enable/disable automatic scanning

6. The radar display shows detected objects in real-time:

<div align="center">
  <img src="https://raw.githubusercontent.com/yourusername/esp32-radar-system/main/images/radar-display.png" alt="Radar Display" width="500"/>
</div>

## 🚀 How It Works

<div align="center">
  <table>
    <tr>
      <th colspan="2" style="text-align:center; background-color:#f0f0f0; padding:10px;">
        <b>⚙️ System Operation</b>
      </th>
    </tr>
    <tr>
      <td><b>Step</b></td>
      <td><b>Description</b></td>
    </tr>
    <tr>
      <td>1. Initialization</td>
      <td>ESP32 connects to WiFi and sets up web server</td>
    </tr>
    <tr>
      <td>2. Distance Measurement</td>
      <td>Ultrasonic sensor emits sound waves and measures echo time</td>
    </tr>
    <tr>
      <td>3. Scanning</td>
      <td>Servo motor rotates sensor to scan in different directions</td>
    </tr>
    <tr>
      <td>4. Data Transmission</td>
      <td>Distance and angle data sent to web interface via WebSockets</td>
    </tr>
    <tr>
      <td>5. Visualization</td>
      <td>Web interface renders radar display with detected objects</td>
    </tr>
    <tr>
      <td>6. Alerts</td>
      <td>LEDs provide visual feedback based on object proximity</td>
    </tr>
  </table>
</div>

## 🔍 Troubleshooting

<div align="center">
  <table>
    <tr>
      <th colspan="2" style="text-align:center; background-color:#f0f0f0; padding:10px;">
        <b>🛠️ Common Issues & Solutions</b>
      </th>
    </tr>
    <tr>
      <td><b>Problem</b></td>
      <td><b>Solution</b></td>
    </tr>
    <tr>
      <td>ESP32 not connecting to WiFi</td>
      <td>Check SSID and password in code</td>
    </tr>
    <tr>
      <td>Servo not moving</td>
      <td>Verify wiring and ensure adequate power supply</td>
    </tr>
    <tr>
      <td>Unstable sensor readings</td>
      <td>Add capacitor (100μF) between sensor power pins</td>
    </tr>
    <tr>
      <td>Web interface not loading</td>
      <td>Ensure device is on same network as ESP32</td>
    </tr>
    <tr>
      <td>Incorrect distance readings</td>
      <td>Calibrate sound speed constant in code</td>
    </tr>
  </table>
</div>

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

## 📚 Sample Code

Here's a simplified version of the main code:

```cpp
#include <ESP32Servo.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>

// Pin definitions
#define TRIGGER_PIN 5
#define ECHO_PIN 18
#define SERVO_PIN 13
#define GREEN_LED_PIN 23
#define RED_LED_PIN 22

// Constants
#define MAX_DISTANCE 400
#define SCAN_STEP 1
#define SPEED_DELAY 15

// WiFi credentials
const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";

// Objects
Servo radarServo;
AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

// Variables
int angle = 0;
int distance = 0;
int scanSpeed = 1;
bool autoScan = false;
int scanDirection = 1;

void setup() {
  Serial.begin(115200);
  
  // Initialize pins
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  
  // Setup servo
  radarServo.attach(SERVO_PIN);
  radarServo.write(0);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Setup web server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", htmlPage);
  });
  
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  
  if (autoScan) {
    // Auto scanning mode
    angle += (SCAN_STEP * scanDirection * scanSpeed);
    
    if (angle >= 180) {
      scanDirection = -1;
    } else if (angle <= 0) {
      scanDirection = 1;
    }
    
    radarServo.write(angle);
  }
  
  // Measure distance
  distance = getDistance();
  
  // Update LEDs based on distance
  if (distance < 20 && distance > 0) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  } else {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
  
  // Send data to clients
  String data = String(distance) + "," + String(angle) + "," + String(scanSpeed);
  webSocket.broadcastTXT(data);
  
  delay(SPEED_DELAY * (6 - scanSpeed));
}

int getDistance() {
  // Trigger ultrasonic pulse
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  // Read echo time
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate distance in cm
  int distance = duration * 0.034 / 2;
  
  // Limit reading to valid range
  if (distance > MAX_DISTANCE || distance <= 0) {
    return 0;
  }
  
  return distance;
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    String message = String((char*)payload);
    
    if (message.startsWith("ANGLE:")) {
      // Set specific angle
      int newAngle = message.substring(6).toInt();
      angle = newAngle;
      radarServo.write(angle);
      autoScan = false;
    }
    else if (message.startsWith("SPEED:")) {
      // Set scan speed
      scanSpeed = message.substring(6).toInt();
    }
    else if (message.startsWith("AUTO:")) {
      // Toggle auto scan
      autoScan = (message.substring(5) == "ON");
    }
  }
}
```

## 📎 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📧 Contact

If you have any questions or suggestions, please open an issue or contact me at - reganddev@gmail.com.

---

<div align="center">
  Made by <a href="https://github.com/devRegan">Regan</a>
</div>