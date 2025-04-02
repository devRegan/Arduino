#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define SERVO_PIN 13
#define GREEN_LED 23
#define RED_LED 22

#define JOYSTICK_X_PIN 34
#define JOYSTICK_Y_PIN 35
#define JOYSTICK_SW_PIN 32

const char* ssid = "Regan_ESP32(Radar)";
const char* password = "ESP3219970205";

IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

AsyncWebServer server(80);
WebSocketsServer webSocket(81);

Servo servo;

int currentAngle = 180;
int targetAngle = 180;
int distance = 0;
bool autoMode = false;
bool scanDirection = true;
int servoSpeed = 1;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    if (type == WStype_TEXT) {
        String command = String((char *)payload);
        Serial.print("Received command: ");
        Serial.println(command);
        
        if (command.startsWith("S:")) {
            targetAngle = command.substring(2).toInt();
            autoMode = false;
        } 
        else if (command == "Auto:ON") {
            autoMode = true;
        }
        else if (command == "Auto:OFF") {
            autoMode = false;
        }
        else if (command.startsWith("Pos:")) {
            targetAngle = command.substring(4).toInt();
            autoMode = false;
        }
        else if (command.startsWith("Speed:")) {
            servoSpeed = command.substring(6).toInt();
        }
    }
}

int measureDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(5);
    
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    
    int calculatedDistance = duration * 0.034 / 2;
    
    if (calculatedDistance == 0 || calculatedDistance > 100) {
        return 100;
    }
    
    static int lastDistance = 0;
    int filteredDistance = (calculatedDistance + lastDistance) / 2;
    lastDistance = calculatedDistance;
    
    return filteredDistance;
}

void controlLED(int distance) {
    digitalWrite(RED_LED, distance < 20);
    digitalWrite(GREEN_LED, distance >= 20);
}

void sendDataToApp(int angle, int distance) {
    String message = "D:" + String(distance) + ":" + String(angle) + ":" + String(autoMode ? 1 : 0) + ":" + String(servoSpeed);
    webSocket.broadcastTXT(message);
}

void handleAutoMode() {
    static unsigned long lastAutoUpdate = 0;
    unsigned long currentTime = millis();
    
    if (autoMode && currentTime - lastAutoUpdate > 30) {
        lastAutoUpdate = currentTime;
        
        if (scanDirection) {
            targetAngle += servoSpeed;
            if (targetAngle >= 360) {
                targetAngle = 360;
                scanDirection = false;
            }
        } else {
            targetAngle -= servoSpeed;
            if (targetAngle <= 0) {
                targetAngle = 0;
                scanDirection = true;
            }
        }
    }
}

void moveServo() {
    if (currentAngle < targetAngle) {
        currentAngle = min(currentAngle + servoSpeed, targetAngle);
    } else if (currentAngle > targetAngle) {
        currentAngle = max(currentAngle - servoSpeed, targetAngle);
    }
    
    int mappedAngle = map(currentAngle, 0, 360, 0, 180);
    servo.write(mappedAngle);
}

void readPhysicalJoystick() {
    static unsigned long lastJoystickRead = 0;
    static bool lastButtonState = HIGH;
    
    if (millis() - lastJoystickRead > 50) {
        lastJoystickRead = millis();
        
        int xValue = analogRead(JOYSTICK_X_PIN);
        int yValue = analogRead(JOYSTICK_Y_PIN);
        bool buttonState = digitalRead(JOYSTICK_SW_PIN);
        
        if (abs(xValue - 2048) > 500 || abs(yValue - 2048) > 500) {
            float angleRad = atan2(yValue - 2048, xValue - 2048);
            int newAngle = (int)((angleRad * 180.0 / PI) + 360) % 360;
            
            if (!autoMode) {
                targetAngle = newAngle;
            }
        }
        
        if (buttonState == LOW && lastButtonState == HIGH) {
            autoMode = !autoMode;
        }
        lastButtonState = buttonState;
    }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
    <title>ESP32 Radar</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #111;
            color: #fff;
            margin: 0;
            padding: 0;
            touch-action: manipulation;
        }
        .container {
            max-width: 100%;
            margin: 0 auto;
            padding: 10px;
        }
        header {
            text-align: center;
            margin-bottom: 10px;
            color: #4caf50;
        }
        .radar-container {
            position: relative;
            width: 320px;
            height: 320px;
            margin: 0 auto;
            background: #000;
            border-radius: 50%;
            border: 1px solid #4caf50;
            overflow: hidden;
            box-shadow: 0 0 15px rgba(0, 255, 0, 0.3);
        }
        .radar-sweep {
            position: absolute;
            width: 160px;
            height: 2px;
            background: linear-gradient(90deg, rgba(0,255,0,0) 0%, rgba(0,255,0,0.8) 100%);
            top: 160px;
            left: 160px;
            transform-origin: left center;
            z-index: 2;
            box-shadow: 0 0 5px rgba(0, 255, 0, 0.7);
        }
        .radar-center {
            position: absolute;
            width: 6px;
            height: 6px;
            background-color: #00ff00;
            border-radius: 50%;
            top: 160px;
            left: 160px;
            transform: translate(-50%, -50%);
            box-shadow: 0 0 5px #00ff00;
            z-index: 4;
        }
        .radar-circle {
            position: absolute;
            border: 1px solid rgba(0, 255, 0, 0.2);
            border-radius: 50%;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
        }
        .radar-distance-label {
            position: absolute;
            color: rgba(0, 255, 0, 0.6);
            font-size: 12px;
            transform: translate(-50%, -50%);
            text-shadow: 0 0 2px rgba(0, 0, 0, 0.8);
            z-index: 3;
        }
        .radar-axis {
            position: absolute;
            background-color: rgba(0, 255, 0, 0.15);
            top: 160px;
            left: 0;
            width: 100%;
            height: 1px;
            z-index: 1;
        }
        .radar-axis.vertical {
            width: 1px;
            height: 100%;
            top: 0;
            left: 160px;
        }
        .radar-object {
            position: absolute;
            width: 6px;
            height: 6px;
            background-color: red;
            border-radius: 50%;
            transform: translate(-50%, -50%);
            display: none;
            z-index: 3;
            box-shadow: 0 0 5px red;
        }
        .angle-labels {
            display: flex;
            justify-content: space-between;
            width: 100%;
            padding: 0 10px;
            box-sizing: border-box;
            margin-top: 5px;
            color: #4caf50;
        }
        .info-panel {
            display: flex;
            justify-content: space-between;
            background-color: #222;
            padding: 10px;
            border-radius: 5px;
            margin: 10px auto;
            max-width: 320px;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3);
        }
        .info-item {
            text-align: center;
        }
        .info-label {
            font-size: 12px;
            color: #aaa;
        }
        .info-value {
            font-size: 16px;
            color: #4caf50;
            text-shadow: 0 0 5px rgba(0, 255, 0, 0.3);
        }
        .alert-message {
            text-align: center;
            padding: 5px;
            margin: 10px auto;
            max-width: 320px;
            border-radius: 3px;
            background-color: #222;
            color: #4caf50;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3);
        }
        .control-panel {
            background-color: #222;
            padding: 10px;
            border-radius: 5px;
            margin: 10px auto;
            max-width: 320px;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3);
        }
        .slider-container {
            margin: 10px 0;
        }
        .slider {
            width: 100%;
            height: 15px;
            border-radius: 5px;
            background: #333;
            outline: none;
            -webkit-appearance: none;
        }
        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            width: 20px;
            height: 20px;
            border-radius: 50%;
            background: #4caf50;
            cursor: pointer;
        }
        .button-row {
            display: flex;
            justify-content: space-between;
            margin-top: 10px;
            flex-wrap: wrap;
        }
        .control-btn {
            background-color: #333;
            color: #4caf50;
            border: none;
            padding: 8px;
            border-radius: 5px;
            cursor: pointer;
            min-width: 45px;
            margin: 3px;
            font-size: 12px;
            transition: background-color 0.2s;
        }
        .control-btn:active {
            background-color: #444;
        }
        .auto-btn {
            width: 100%;
            margin-top: 10px;
            background-color: #333;
            color: #4caf50;
        }
        .auto-btn.active {
            background-color: #4caf50;
            color: #000;
        }
        .speed-control {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-top: 10px;
        }
        .spectrum-container {
            width: 100%;
            height: 60px;
            background-color: #111;
            margin: 10px 0;
            border-radius: 5px;
            overflow: hidden;
            position: relative;
        }
        .spectrum-bar {
            height: 100%;
            width: 1.8%;
            display: inline-block;
            background-color: #333;
            margin: 0 0.1%;
            vertical-align: bottom;
            transition: height 0.2s, background-color 0.2s;
        }
        .spectrum-bar.active {
            background-color: #4caf50;
        }
        .spectrum-bar.danger {
            background-color: #ff5555;
        }
    </style>
</head>
<body>
    <div class="container">
        <header><h2>ESP32 Radar (360°)</h2></header>
        
        <div class="radar-container">
            <div class="radar-axis"></div>
            <div class="radar-axis vertical"></div>
            <div class="radar-circle" style="width:32px; height:32px;"></div>
            <div class="radar-circle" style="width:64px; height:64px;"></div>
            <div class="radar-circle" style="width:96px; height:96px;"></div>
            <div class="radar-circle" style="width:128px; height:128px;"></div>
            <div class="radar-circle" style="width:160px; height:160px;"></div>
            <div class="radar-circle" style="width:192px; height:192px;"></div>
            <div class="radar-circle" style="width:224px; height:224px;"></div>
            <div class="radar-circle" style="width:256px; height:256px;"></div>
            <div class="radar-circle" style="width:288px; height:288px;"></div>
            <div class="radar-circle" style="width:320px; height:320px;"></div>
            
            <div class="radar-distance-label" style="top: 160px; left: 160px;">0<br>cm</div>
            <div class="radar-distance-label" style="top: 160px; left: 176px;">10<br>cm</div>
            <div class="radar-distance-label" style="top: 160px; left: 192px;">20<br>cm</div>
            <div class="radar-distance-label" style="top: 160px; left: 224px;">40<br>cm</div>
            <div class="radar-distance-label" style="top: 160px; left: 256px;">60<br>cm</div>
            <div class="radar-distance-label" style="top: 160px; left: 288px;">80<br>cm</div>
            <div class="radar-distance-label" style="top: 160px; left: 320px;">100<br>cm</div>
            
            <div class="radar-center"></div>
            <div class="radar-sweep" id="radar-sweep"></div>
            <div class="radar-object" id="radar-object"></div>
        </div>
        
        <div class="angle-labels">
            <span>0°</span>
            <span>90°</span>
            <span>180°</span>
            <span>270°</span>
            <span>360°</span>
        </div>
        
        <div class="spectrum-container" id="spectrum-container">
        </div>
        
        <div class="info-panel">
            <div class="info-item">
                <div class="info-label">Distance</div>
                <div class="info-value" id="distance-value">0 cm</div>
            </div>
            <div class="info-item">
                <div class="info-label">Angle</div>
                <div class="info-value" id="angle-value">180°</div>
            </div>
            <div class="info-item">
                <div class="info-label">Speed</div>
                <div class="info-value" id="speed-value">1</div>
            </div>
        </div>
        
        <div id="alert-box" class="alert-message">Scanning...</div>
        
        <div class="control-panel">
            <div class="slider-container">
                <input type="range" min="0" max="360" value="180" class="slider" id="servo-slider">
            </div>
            
            <div class="button-row">
                <button class="control-btn" id="pos-0">0°</button>
                <button class="control-btn" id="pos-20">20°</button>
                <button class="control-btn" id="pos-40">40°</button>
                <button class="control-btn" id="pos-60">60°</button>
                <button class="control-btn" id="pos-80">80°</button>
                <button class="control-btn" id="pos-100">100°</button>
                <button class="control-btn" id="pos-120">120°</button>
                <button class="control-btn" id="pos-140">140°</button>
                <button class="control-btn" id="pos-160">160°</button>
                <button class="control-btn" id="pos-180">180°</button>
                <button class="control-btn" id="pos-200">200°</button>
                <button class="control-btn" id="pos-220">220°</button>
                <button class="control-btn" id="pos-240">240°</button>
                <button class="control-btn" id="pos-260">260°</button>
                <button class="control-btn" id="pos-280">280°</button>
                <button class="control-btn" id="pos-300">300°</button>
                <button class="control-btn" id="pos-320">320°</button>
                <button class="control-btn" id="pos-340">340°</button>
                <button class="control-btn" id="pos-360">360°</button>
            </div>
            
            <div class="speed-control">
                <span>Speed:</span>
                <button class="control-btn" id="speed-minus">-</button>
                <span id="speed-display">1</span>
                <button class="control-btn" id="speed-plus">+</button>
            </div>
            
            <button class="control-btn auto-btn" id="auto-btn">AUTO SCAN: OFF</button>
        </div>
    </div>
    
    <script>
        var gateway = `ws://${window.location.hostname}:81`;
        var websocket;
        var servoAngle = 180;
        var distance = 0;
        var autoMode = false;
        var servoSpeed = 1;
        var detectionHistory = [];
        var spectrumBars = [];
        
        function initWebSocket() {
            console.log('Connecting to WebSocket...');
            websocket = new WebSocket(gateway);
            websocket.onopen = onOpen;
            websocket.onclose = onClose;
            websocket.onmessage = onMessage;
        }
        
        function onOpen(event) { 
            console.log('WebSocket connected'); 
        }
        
        function onClose(event) { 
            console.log('WebSocket disconnected'); 
            setTimeout(initWebSocket, 2000); 
        }
        
        function initSpectrum() {
            var container = document.getElementById('spectrum-container');
            container.innerHTML = '';
            
            for (var i = 0; i < 50; i++) {
                var bar = document.createElement('div');
                bar.className = 'spectrum-bar';
                bar.style.height = '10%';
                container.appendChild(bar);
                spectrumBars.push(bar);
            }
        }
        
        function updateSpectrum(angle, distance) {
            var index = Math.floor(angle / (360 / spectrumBars.length));
            if (index >= 0 && index < spectrumBars.length) {
                var height = 0;
                
                if (distance < 100) {
                    height = 100 - distance;
                }
                
                spectrumBars[index].style.height = height + '%';
                
                if (distance < 20) {
                    spectrumBars[index].className = 'spectrum-bar danger';
                } else if (distance < 100) {
                    spectrumBars[index].className = 'spectrum-bar active';
                } else {
                    spectrumBars[index].className = 'spectrum-bar';
                }
            }
        }
        
        function onMessage(event) {
            var message = event.data;
            if (message.startsWith('D:')) {
                var parts = message.substring(2).split(':');
                distance = parseInt(parts[0]);
                servoAngle = parseInt(parts[1]);
                autoMode = parseInt(parts[2]) === 1;
                servoSpeed = parseInt(parts[3]) || 1;
                
                document.getElementById('distance-value').textContent = distance + ' cm';
                document.getElementById('angle-value').textContent = servoAngle + '°';
                document.getElementById('speed-value').textContent = servoSpeed;
                document.getElementById('speed-display').textContent = servoSpeed;
                document.getElementById('servo-slider').value = servoAngle;
                
                updateRadar(servoAngle, distance);
                updateSpectrum(servoAngle, distance);
                
                var alertBox = document.getElementById('alert-box');
                if (distance < 30) {
                    alertBox.style.color = '#ff5555';
                    alertBox.textContent = 'Object detected at ' + distance + ' cm';
                } else {
                    alertBox.style.color = '#4caf50';
                    alertBox.textContent = 'Scanning...';
                }
                
                var autoBtn = document.getElementById('auto-btn');
                if (autoMode) {
                    autoBtn.classList.add('active');
                    autoBtn.textContent = 'AUTO SCAN: ON';
                } else {
                    autoBtn.classList.remove('active');
                    autoBtn.textContent = 'AUTO SCAN: OFF';
                }
            }
        }
        
        function updateRadar(angle, distance) {
            document.getElementById('radar-sweep').style.transform = `rotate(${angle}deg)`;
            
            if (distance < 100) {
                var maxRadius = 160;
                var scaledDistance = (distance / 100) * maxRadius;
                
                var angleRad = (angle - 90) * (Math.PI / 180);
                var x = 160 + scaledDistance * Math.cos(angleRad);
                var y = 160 + scaledDistance * Math.sin(angleRad);
                
                var objectElement = document.getElementById('radar-object');
                objectElement.style.left = x + 'px';
                objectElement.style.top = y + 'px';
                objectElement.style.display = 'block';
                
                var dotSize = Math.max(6, 15 - (distance / 10));
                objectElement.style.width = dotSize + 'px';
                objectElement.style.height = dotSize + 'px';
            } else {
                document.getElementById('radar-object').style.display = 'none';
            }
        }
        
        function sendServoPosition(angle) {
            websocket.send('S:' + angle);
        }
        
        function sendServoSpeed(speed) {
            websocket.send('Speed:' + speed);
        }
        
        function toggleAutoMode() {
            autoMode = !autoMode;
            websocket.send('Auto:' + (autoMode ? 'ON' : 'OFF'));
        }
        
        window.addEventListener('load', function() {
            initWebSocket();
            initSpectrum();
            
            var servoSlider = document.getElementById('servo-slider');
            servoSlider.addEventListener('input', function() {
                var angle = parseInt(this.value);
                sendServoPosition(angle);
            });
            
            document.querySelectorAll('[id^="pos-"]').forEach(function(button) {
                button.addEventListener('click', function() {
                    var angle = parseInt(this.id.split('-')[1]);
                    websocket.send('Pos:' + angle);
                });
            });
            
            document.getElementById('speed-plus').addEventListener('click', function() {
                servoSpeed = Math.min(servoSpeed + 1, 10);
                sendServoSpeed(servoSpeed);
            });
            
            document.getElementById('speed-minus').addEventListener('click', function() {
                servoSpeed = Math.max(servoSpeed - 1, 1);
                sendServoSpeed(servoSpeed);
            });
            
            document.getElementById('auto-btn').addEventListener('click', function() {
                toggleAutoMode();
            });
        });
    </script>
</body>
</html>
)rawliteral";

void setup() {
    Serial.begin(115200);
    
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    
    pinMode(JOYSTICK_X_PIN, INPUT);
    pinMode(JOYSTICK_Y_PIN, INPUT);
    pinMode(JOYSTICK_SW_PIN, INPUT_PULLUP);
    
    servo.attach(SERVO_PIN);
    servo.write(90);
    
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_IP, gateway, subnet);
    
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", index_html);
    });
    server.begin();
    
    Serial.println("HTTP server started");
}

void loop() {
    webSocket.loop();
    
    readPhysicalJoystick();
    
    static unsigned long lastDistanceMeasure = 0;
    if (millis() - lastDistanceMeasure > 50) {
        lastDistanceMeasure = millis();
        distance = measureDistance();
        
        controlLED(distance);
    }
    
    handleAutoMode();
    
    static unsigned long lastServoMove = 0;
    if (millis() - lastServoMove > 15) {
        lastServoMove = millis();
        moveServo();
    }
    
    static unsigned long lastSend = 0;
    if (millis() - lastSend > 150) {
        lastSend = millis();
        sendDataToApp(currentAngle, distance);
    }
}