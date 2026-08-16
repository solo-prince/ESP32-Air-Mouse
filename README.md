🤖 ESP32 Wireless Air Mouse

A **DIY wireless Bluetooth Air Mouse** built using an **ESP32-WROOM-32, MPU6050 IMU, and three push buttons**.

The MPU6050 detects the movement and rotation of the controller. The ESP32 processes the motion and sends it to a computer as a **Bluetooth HID mouse**.

This project is designed for students, electronics enthusiasts, embedded-systems learners, and robotics developers who want to understand **IMU-based human-machine interaction, Bluetooth HID, and ESP32 development**.

---

## 📸 Project Hardware

The prototype is built on a breadboard using an ESP32 DevKit, MPU6050 and three push buttons.

![ESP32 Air Mouse Hardware](images/ESP32_Air_Mouse_Hardware.png)

---

## 🔍 Project Overview

The ESP32 Air Mouse works like a traditional computer mouse, but instead of moving a physical mouse on a desk, the user moves the controller in the air.

The **MPU6050** measures angular motion using its gyroscope. The ESP32 converts this motion into X/Y mouse movement and sends the commands wirelessly to the computer using Bluetooth HID.

Three push buttons provide mouse functions:

- **Button 1 → Left Click**
- **Button 2 → Right Click**
- **Button 3 → Middle Click**

### Basic working principle

```text
             ┌─────────────────┐
             │    MPU6050      │
             │   Motion Sensor │
             └────────┬────────┘
                      │
                      │ I2C
                      │
                      ▼
             ┌─────────────────┐
             │      ESP32      │
             │  Motion + HID   │
             │    Processing   │
             └────────┬────────┘
                      │
                      │ Bluetooth
                      │ HID
                      ▼
             ┌─────────────────┐
             │       PC        │
             │  Mouse Cursor   │
             └─────────────────┘

      ┌─────────┐
      │ Button 1│ ──────┐
      └─────────┘       │
      ┌─────────┐       ├──► ESP32
      │ Button 2│ ──────┤
      └─────────┘       │
      ┌─────────┐       │
      │ Button 3│ ──────┘
      └─────────┘
````

---

## ✨ Features

* 🖱️ Wireless Bluetooth mouse
* 🎮 Air-based cursor control
* 📐 MPU6050 motion sensing
* 🖱️ Left mouse click
* 🖱️ Right mouse click
* 🖱️ Middle mouse click
* 📡 Bluetooth HID communication
* 🎯 Adjustable cursor sensitivity
* 🧭 MPU6050 gyro calibration
* 🔌 Simple I2C interface
* 🔧 No external pull-up resistors required for buttons
* 🧪 Wokwi simulation version
* 💻 Compatible with Bluetooth-enabled computers

---

## 🧰 Components Required

| Component                     |    Quantity | Purpose                     |
| ----------------------------- | ----------: | --------------------------- |
| ESP32 DevKit / ESP32-WROOM-32 |           1 | Main controller + Bluetooth |
| MPU6050                       |           1 | Motion/gyro sensor          |
| Push Button                   |           3 | Mouse buttons               |
| Breadboard                    |           1 | Prototyping                 |
| Jumper Wires                  | As required | Connections                 |
| USB Cable                     |           1 | Programming and power       |

---

# 🔌 Circuit Diagram

## MPU6050 → ESP32

```text
        MPU6050
     ┌─────────────┐
     │             │
 VCC │─────────────┼──── ESP32 3.3V
 GND │─────────────┼──── ESP32 GND
 SDA │─────────────┼──── ESP32 GPIO 21
 SCL │─────────────┼──── ESP32 GPIO 22
     │             │
     └─────────────┘
```

### Connection table

| MPU6050 Pin | ESP32 Pin | Function  |
| ----------- | --------- | --------- |
| VCC         | 3.3V      | Power     |
| GND         | GND       | Ground    |
| SDA         | GPIO 21   | I2C Data  |
| SCL         | GPIO 22   | I2C Clock |

---

# 🔘 Push Button Connections

The buttons use the ESP32's internal pull-up resistors.

Therefore, **no external resistor is required**.

```text
                    ESP32

GPIO 25 ────────────┐
                    │
                ┌───┴───┐
                │BUTTON 1│
                └───┬───┘
                    │
                   GND


GPIO 26 ────────────┐
                    │
                ┌───┴───┐
                │BUTTON 2│
                └───┬───┘
                    │
                   GND


GPIO 27 ────────────┐
                    │
                ┌───┴───┐
                │BUTTON 3│
                └───┬───┘
                    │
                   GND
```

### Button configuration

| Button   | ESP32 GPIO | Function     |
| -------- | ---------: | ------------ |
| Button 1 |    GPIO 25 | Left Click   |
| Button 2 |    GPIO 26 | Right Click  |
| Button 3 |    GPIO 27 | Middle Click |

---

# 📌 Complete Pin Configuration

| Device   | Pin            | ESP32   |
| -------- | -------------- | ------- |
| MPU6050  | VCC            | 3.3V    |
| MPU6050  | GND            | GND     |
| MPU6050  | SDA            | GPIO 21 |
| MPU6050  | SCL            | GPIO 22 |
| Button 1 | Signal         | GPIO 25 |
| Button 2 | Signal         | GPIO 26 |
| Button 3 | Signal         | GPIO 27 |
| Buttons  | Other terminal | GND     |

---

# 🧠 How It Works

The project can be divided into four main stages.

### 1. Motion Detection

The MPU6050 detects the rotational movement of the controller.

```text
Physical movement
       ↓
    MPU6050
       ↓
Gyroscope data
```

### 2. ESP32 Processing

The ESP32 reads the MPU6050 data through I2C.

```text
MPU6050
   ↓
I2C
   ↓
ESP32
   ↓
Gyro calibration
   ↓
Sensitivity + dead zone
   ↓
Mouse X/Y
```

### 3. Button Detection

The ESP32 monitors three push buttons.

```text
GPIO 25 → Left Click
GPIO 26 → Right Click
GPIO 27 → Middle Click
```

The buttons are configured using:

```cpp
INPUT_PULLUP
```

Therefore, pressing a button connects the GPIO to GND.

### 4. Bluetooth HID

The ESP32 sends the mouse commands wirelessly.

```text
ESP32
  │
  │ Bluetooth HID
  ▼
Computer
  │
  ▼
Mouse Cursor
```

---

# 🎯 Axis Mapping

The MPU6050 axis mapping was adjusted for the physical orientation of the prototype.

Current mapping:

| Physical Movement | Cursor Movement |
| ----------------- | --------------- |
| Move UP           | Cursor UP       |
| Move DOWN         | Cursor DOWN     |
| Move RIGHT        | Cursor RIGHT    |
| Move LEFT         | Cursor LEFT     |

The main mapping in the code is:

```cpp
float mouseX = -gyroX * sensitivity;
float mouseY = gyroY * sensitivity;
```

If the sensor is mounted in another orientation, the X/Y signs may need to be changed.

---

# ⚙️ Mouse Settings

The cursor sensitivity can be adjusted in the Arduino code.

```cpp
float sensitivity = 3.0;
```

Increase the value for faster movement:

```cpp
float sensitivity = 5.0;
```

Decrease the value for slower movement:

```cpp
float sensitivity = 1.5;
```

The dead zone removes very small unwanted movements:

```cpp
float deadZone = 0.8;
```

Maximum cursor movement is limited using:

```cpp
int maxMove = 15;
```

---

# 🧭 MPU6050 Calibration

When the ESP32 starts, the MPU6050 is calibrated automatically.

The controller must remain completely still during calibration.

```text
ESP32 starts
     ↓
MPU6050 detected
     ↓
Calibration
     ↓
Gyroscope offsets calculated
     ↓
Bluetooth mouse starts
```

The calibration uses multiple sensor samples to calculate the gyro offset.

---

# 💻 Software & Libraries

## Development Environment

* Arduino IDE
* ESP32 Arduino Core
* C/C++

## Arduino Libraries

### Adafruit MPU6050

Used to communicate with the MPU6050 sensor.

### Adafruit Unified Sensor

Required by the Adafruit sensor libraries.

### ESP32 BLE Mouse

Used to make the ESP32 behave as a Bluetooth HID mouse.

---

# 🔵 Bluetooth Connection

After uploading the firmware:

1. Power the ESP32.
2. Keep the controller still during calibration.
3. Wait for the Bluetooth mouse to start.
4. Open Bluetooth settings on the computer.
5. Search for:

```text
ESP32 Air Mouse
```

6. Pair/connect the device.
7. Move the ESP32 to control the cursor.

---

# 🧪 Wokwi Simulation

A Wokwi simulation version is included separately.

The simulation can test:

* ESP32
* MPU6050
* Push buttons
* I2C communication
* Motion processing
* Button detection

### Important limitation

Wokwi does not provide the same real Bluetooth HID connection required to control the physical computer cursor.

Therefore, the Wokwi version displays simulated mouse movement and button events through the Serial Monitor.

```text
Wokwi

MPU6050
   ↓
ESP32
   ↓
Serial Monitor
   ↓
Mouse X/Y
Button events
```

---

# 📁 Project Structure

```text
ESP32-Air-Mouse/
│
├── ESP32_Air_Mouse.ino
│
├── README.md
│
├── images/
│   └── ESP32_Air_Mouse_Hardware.png
│
└── wokwi/
    ├── sketch.ino
    └── diagram.json
```

---

# 🛠️ Installation

## 1. Install ESP32 Board Package

Open Arduino IDE.

Go to:

```text
Tools
→ Board
→ Boards Manager
```

Search for:

```text
esp32
```

Install the ESP32 board package.

Select:

```text
ESP32 Dev Module
```

---

## 2. Install Required Libraries

Open:

```text
Sketch
→ Include Library
→ Manage Libraries
```

Install:

```text
Adafruit MPU6050
Adafruit Unified Sensor
```

Install the:

```text
ESP32 BLE Mouse
```

library for Bluetooth HID mouse functionality.

---

# ⚠️ ESP32 Core 3.x Compatibility

The original ESP32 BLE Mouse library may require a small compatibility modification when used with newer ESP32 Arduino Core 3.x versions.

For ESP32 Core 3.x, the following conversions may be required in `BleMouse.cpp`:

```cpp
BLEDevice::init(
    String(bleMouseInstance->deviceName.c_str())
);
```

and:

```cpp
bleMouseInstance->hid->manufacturer()->setValue(
    String(bleMouseInstance->deviceManufacturer.c_str())
);
```

This project was tested with ESP32 Arduino Core 3.3.11.

---

# 🧪 Testing Procedure

### Test 1 — MPU6050

Check that the serial monitor reports:

```text
MPU6050 detected!
```

### Test 2 — Calibration

Keep the controller still while calibration is running.

### Test 3 — Bluetooth

Check that:

```text
ESP32 Air Mouse
```

appears in the computer's Bluetooth devices.

### Test 4 — Cursor

Move the ESP32:

```text
UP    → Cursor UP
DOWN  → Cursor DOWN
LEFT  → Cursor LEFT
RIGHT → Cursor RIGHT
```

### Test 5 — Buttons

```text
GPIO 25 → Left Click
GPIO 26 → Right Click
GPIO 27 → Middle Click
```

---

# 🛠️ Troubleshooting

## MPU6050 not detected

Check:

```text
VCC → 3.3V
GND → GND
SDA → GPIO 21
SCL → GPIO 22
```

Also check that the MPU6050 module is powered.

---

## Cursor moves in the wrong direction

Change the signs in:

```cpp
float mouseX = -gyroX * sensitivity;
float mouseY = gyroY * sensitivity;
```

Depending on the physical orientation of the MPU6050, the signs may need to be reversed.

---

## Cursor moves when the controller is stationary

Increase the dead zone:

```cpp
float deadZone = 1.2;
```

or:

```cpp
float deadZone = 1.5;
```

Also make sure the controller is completely still during startup calibration.

---

## Cursor movement is too slow

Increase:

```cpp
float sensitivity = 3.0;
```

For example:

```cpp
float sensitivity = 5.0;
```

---

## Cursor movement is too fast

Decrease:

```cpp
float sensitivity = 2.0;
```

---

## Bluetooth mouse does not appear

Check:

* ESP32-WROOM-32 is being used
* Bluetooth is enabled
* Firmware uploaded successfully
* ESP32 has restarted
* Computer Bluetooth is enabled

---

# 🚀 Future Improvements

Possible upgrades include:

* 🔋 Rechargeable battery
* 🔘 Dedicated DPI/sensitivity button
* 🖱️ Scroll wheel
* 🖐️ Gesture-based controls
* 🖥️ OLED status display
* 🔋 Battery voltage monitoring
* 🔒 Bluetooth connection status indicator
* 🎮 Presentation-control mode
* 📱 Mobile configuration interface
* 📡 Wi-Fi configuration
* 🧠 Machine-learning-based gesture recognition
* 🧭 Sensor fusion using accelerometer + gyroscope
* 🎯 Improved cursor stabilization
* 🖨️ Custom 3D-printed enclosure

---

# 📚 Learning Outcomes

This project demonstrates practical concepts in:

* Embedded systems
* ESP32 programming
* I2C communication
* IMU sensors
* Gyroscope calibration
* Bluetooth HID
* Human-machine interaction
* GPIO input handling
* Sensor data processing
* Wireless embedded devices
* Hardware prototyping

---

# 👨‍💻 Author

**solo-prince**

ESP32 Wireless Air Mouse project.

---

# 📄 License

This project is intended for educational and personal development purposes.

You may modify and improve the project for your own robotics and embedded-systems experiments.
EOF
