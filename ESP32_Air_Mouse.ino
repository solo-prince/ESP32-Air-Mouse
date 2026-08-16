#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BleMouse.h>

Adafruit_MPU6050 mpu;

BleMouse bleMouse(
  "ESP32 Air Mouse",
  "ESP32",
  100
);

// MPU6050
#define MPU_SDA 21
#define MPU_SCL 22

// Buttons
#define LEFT_BUTTON   25
#define RIGHT_BUTTON  26
#define MIDDLE_BUTTON 27

// Mouse settings
float sensitivity = 3.0;
float deadZone = 0.8;
int maxMove = 15;

// Gyro calibration
float gyroXOffset = 0;
float gyroYOffset = 0;

// Button states
bool lastLeftState = HIGH;
bool lastRightState = HIGH;
bool lastMiddleState = HIGH;


// =========================================================
// MPU6050 CALIBRATION
// =========================================================

void calibrateMPU()
{
  Serial.println();
  Serial.println("========================================");
  Serial.println("       MPU6050 CALIBRATION");
  Serial.println("========================================");
  Serial.println();

  Serial.println("KEEP THE ESP32 COMPLETELY STILL!");
  Serial.println("Calibration starting in 3 seconds...");

  delay(3000);

  float totalX = 0;
  float totalY = 0;

  const int samples = 500;

  Serial.println("Calibrating...");

  for (int i = 0; i < samples; i++)
  {
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temperature;

    mpu.getEvent(
      &accel,
      &gyro,
      &temperature
    );

    totalX += gyro.gyro.x;
    totalY += gyro.gyro.y;

    delay(5);
  }

  gyroXOffset = totalX / samples;
  gyroYOffset = totalY / samples;

  Serial.println();
  Serial.println("Calibration completed!");

  Serial.print("X Offset = ");
  Serial.println(gyroXOffset, 6);

  Serial.print("Y Offset = ");
  Serial.println(gyroYOffset, 6);

  Serial.println();
}


// =========================================================
// SETUP
// =========================================================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("========================================");
  Serial.println("       ESP32 BLUETOOTH AIR MOUSE");
  Serial.println("========================================");
  Serial.println();


  // Buttons

  pinMode(
    LEFT_BUTTON,
    INPUT_PULLUP
  );

  pinMode(
    RIGHT_BUTTON,
    INPUT_PULLUP
  );

  pinMode(
    MIDDLE_BUTTON,
    INPUT_PULLUP
  );


  // I2C

  Serial.println("Starting I2C...");

  Wire.begin(
    MPU_SDA,
    MPU_SCL
  );

  delay(500);


  // MPU6050

  Serial.println("Checking MPU6050...");

  if (!mpu.begin())
  {
    Serial.println();
    Serial.println("***************************************");
    Serial.println("ERROR: MPU6050 NOT FOUND!");
    Serial.println("***************************************");
    Serial.println();

    Serial.println("Check:");

    Serial.println("VCC -> 3.3V");
    Serial.println("GND -> GND");
    Serial.println("SDA -> GPIO 21");
    Serial.println("SCL -> GPIO 22");

    Serial.println();

    while (1)
    {
      delay(1000);
    }
  }

  Serial.println("MPU6050 detected!");
  Serial.println();


  // MPU settings

  mpu.setAccelerometerRange(
    MPU6050_RANGE_8_G
  );

  mpu.setGyroRange(
    MPU6050_RANGE_500_DEG
  );

  mpu.setFilterBandwidth(
    MPU6050_BAND_21_HZ
  );


  // Calibration

  calibrateMPU();


  // Bluetooth

  Serial.println("Starting Bluetooth Mouse...");

  bleMouse.begin();

  delay(1000);

  Serial.println();
  Serial.println("========================================");
  Serial.println("          AIR MOUSE READY");
  Serial.println("========================================");

  Serial.println();

  Serial.println("Bluetooth:");
  Serial.println("ESP32 Air Mouse");

  Serial.println();

  Serial.println("Buttons:");
  Serial.println("GPIO 25 = LEFT CLICK");
  Serial.println("GPIO 26 = RIGHT CLICK");
  Serial.println("GPIO 27 = MIDDLE CLICK");

  Serial.println();
}


// =========================================================
// LOOP
// =========================================================

void loop()
{
  sensors_event_t acceleration;
  sensors_event_t gyro;
  sensors_event_t temperature;

  mpu.getEvent(
    &acceleration,
    &gyro,
    &temperature
  );


  // Remove gyro offset

  float gyroX =
    gyro.gyro.x - gyroXOffset;

  float gyroY =
    gyro.gyro.y - gyroYOffset;


  // =======================================================
  // CORRECTED AXIS MAPPING
  // =======================================================
  //
  // Physical UP    -> Cursor UP
  // Physical DOWN  -> Cursor DOWN
  // Physical RIGHT -> Cursor RIGHT
  // Physical LEFT  -> Cursor LEFT
  //
  // =======================================================

  float mouseX =
    -gyroX * sensitivity;

  float mouseY =
    gyroY * sensitivity;


  // Dead zone

  if (abs(mouseX) < deadZone)
  {
    mouseX = 0;
  }

  if (abs(mouseY) < deadZone)
  {
    mouseY = 0;
  }


  // Limit speed

  mouseX = constrain(
    mouseX,
    -maxMove,
    maxMove
  );

  mouseY = constrain(
    mouseY,
    -maxMove,
    maxMove
  );


  // =======================================================
  // BLUETOOTH MOUSE
  // =======================================================

  if (bleMouse.isConnected())
  {

    // Cursor

    if (
      mouseX != 0 ||
      mouseY != 0
    )
    {
      bleMouse.move(
        (int)mouseX,
        (int)mouseY
      );
    }


    // =====================================================
    // LEFT CLICK
    // =====================================================

    bool leftState =
      digitalRead(LEFT_BUTTON);

    if (
      leftState == LOW &&
      lastLeftState == HIGH
    )
    {
      bleMouse.click(MOUSE_LEFT);

      Serial.println("LEFT CLICK");

      delay(50);
    }

    lastLeftState =
      leftState;


    // =====================================================
    // RIGHT CLICK
    // =====================================================

    bool rightState =
      digitalRead(RIGHT_BUTTON);

    if (
      rightState == LOW &&
      lastRightState == HIGH
    )
    {
      bleMouse.click(MOUSE_RIGHT);

      Serial.println("RIGHT CLICK");

      delay(50);
    }

    lastRightState =
      rightState;


    // =====================================================
    // MIDDLE CLICK
    // =====================================================

    bool middleState =
      digitalRead(MIDDLE_BUTTON);

    if (
      middleState == LOW &&
      lastMiddleState == HIGH
    )
    {
      bleMouse.click(MOUSE_MIDDLE);

      Serial.println("MIDDLE CLICK");

      delay(50);
    }

    lastMiddleState =
      middleState;
  }


  delay(10);
}
