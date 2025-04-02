# ESP32 Wiring Guide

## Ultrasonic Sensor (HC-SR04)
| Pin | ESP32 Connection | Description |
|------|-----------------|-------------|
| VCC  | 3.3V / 5V       | Power (Use 5V for better range) |
| GND  | GND             | Ground |
| Trig | GPIO 5          | Trigger signal |
| Echo | GPIO 18         | Echo response (Use voltage divider if needed) |

## Servo Motor
| Pin    | ESP32 Connection | Description |
|--------|-----------------|-------------|
| VCC    | 5V              | Power |
| GND    | GND             | Ground |
| Signal | GPIO 13         | Servo control |

## LEDs (Green & Red)
| LED Type  | ESP32 Connection | Description |
|-----------|-----------------|-------------|
| Green LED (+) | GPIO 23 | Turns on when safe |
| Red LED (+)   | GPIO 22 | Turns on when object is too close |
| GND (Both)    | GND     | Common ground |

## Joystick Module
| Pin  | ESP32 Connection | Description |
|------|-----------------|-------------|
| VCC  | 3.3V / 5V       | Power |
| GND  | GND             | Ground |
| X-axis | GPIO 34       | Read joystick X position |
| Y-axis | GPIO 35       | Read joystick Y position |
| SW (Switch) | GPIO 32  | Button press detection |

This setup ensures that all components are properly connected to the ESP32 for optimal performance. Happy coding! 🚀

