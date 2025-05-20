#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

const int buttonPin = 9;  // button on GPIO9
bool lastButtonState = HIGH;
bool capture = false;
unsigned long capture_start_time = 0;
const unsigned long CAPTURE_DURATION = 1000; 
long last_sample_millis = 0;

void setup(void) {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);

  while (!Serial) delay(10);
  while (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    delay(10);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("");
  delay(100);
}

void capture_data() {
  if ((millis() - last_sample_millis) >= 10) {
    last_sample_millis = millis();
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print(a.acceleration.y);
    Serial.print(",");
    Serial.print(a.acceleration.z);
    Serial.print("\n");

    if (millis() - capture_start_time >= CAPTURE_DURATION) {
      capture = false;
      Serial.print("\n\n\n\n");
      Serial.println("Capture complete (1 seconds)");
    }
  }
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    capture = true;
    capture_start_time = millis();
    Serial.print("-,-,-\n");
    Serial.println("Starting capture (will run for 1 seconds)");
  }
  lastButtonState = currentButtonState;

  if (capture) {
    capture_data();
  }
}