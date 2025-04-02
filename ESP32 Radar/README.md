# Hardware Connections for ESP32 Project

## Ultrasonic Sensor (HC-SR04)
| Pin | ESP32 Pin | Description |
|------|---------|-------------|
| **VCC** (Red) | 3.3V / 5V | Power (Use 5V for better range) |
| **GND** (Black) | GND | Ground |
| **Trig** (Yellow) | GPIO 5 | Trigger signal |
| **Echo** (Green) | GPIO 18 | Echo response (use voltage divider if needed) |

## Servo Motor
| Pin | ESP32 Pin | Description |
|------|---------|-------------|
| **VCC** (Red) | 5V | Power |
| **GND** (Brown) | GND | Ground |
| **PWM (Signal)** (Yellow) | GPIO 13 | Servo control |

## LEDs (Green & Red)
| Pin | ESP32 Pin | Description |
|------|---------|-------------|
| **Green LED (+)** | GPIO 23 | Turns on when safe |
| **Red LED (+)** | GPIO 22 | Turns on when object is too close |
| **GND (Both LEDs)** (Black) | GND | Common ground |

## Joystick Module
| Pin | ESP32 Pin | Description |
|------|---------|-------------|
| **VCC** (Red) | 3.3V / 5V | Power |
| **GND** (Black) | GND | Ground |
| **X-axis** (Yellow) | GPIO 34 | Read joystick X position |
| **Y-axis** (Green) | GPIO 35 | Read joystick Y position |
| **SW (Switch)** (Blue) | GPIO 32 | Button press detection |

This setup ensures proper wiring for seamless operation of the components.

