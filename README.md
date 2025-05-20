# Magic Sword - TECHIN515 Final Project

## Overview
This project is a gesture-controlled magic sword built using the ESP32-C3 and MPU6050. It recognizes three sword-like gestures:

- Horizontal Slash  
- Vertical Slash  
- Diagonal Slash  

Each gesture lights up an RGB LED in a different color. The model is trained with Edge Impulse and runs locally on the ESP32-C3.

---

## Hardware Components

- Seeed XIAO ESP32-C3  
- Adafruit MPU6050 IMU  
- RGB LED (common cathode)  
- Push button  
- 3.7V LiPo battery (optional)  
- Jumper wires, breadboard, enclosure

---

## Hardware Setup

| Component       | ESP32-C3 Pin     |
|----------------|------------------|
| MPU6050 VCC     | 3.3V             |
| MPU6050 GND     | GND              |
| MPU6050 SCL     | GPIO7            |
| MPU6050 SDA     | GPIO6            |
| RGB LED Red     | GPIO3            |
| RGB LED Green   | GPIO4            |
| RGB LED Blue    | GPIO5            |
| Button          | GPIO9 (INPUT_PULLUP) |

---

## Software Setup

1. Open `sword.ino` in Arduino IDE  
2. Install required libraries:
   - Adafruit MPU6050
   - Adafruit Sensor
   - Wire
   - sword_inferencing.h (Edge Impulse export)
3. Select board: Seeed XIAO ESP32-C3  
4. Upload the sketch

---

## How to Use

- Open Serial Monitor at 115200 baud  
- Press the button to trigger gesture capture (1 second window)  
- The system predicts the motion and lights up the corresponding LED:
  - Red = Horizontal Slash  
  - Green = Vertical Slash  
  - Blue = Diagonal Slash  

---

## Train Your Own Model

1. Use the provided Python script to collect 1-second accelerometer data at 100Hz  
2. Upload the CSV files to Edge Impulse and label them accordingly  
3. Use the following impulse settings:
   - DSP: Spectral Analysis (FFT length 16, log scale, overlap)
   - Learning Block: Keras (Classification)
4. Train and test the model, then export as Arduino library  
5. Replace the `.h` model file in the Arduino code  

---

## Known Issues

- Horizontal and Diagonal gestures are sometimes confused  
- Swinging the real sword was tiring, so fewer training samples were collected  
- PCB originally didn’t fit inside the blade and had to be moved to the handle  

---

## Future Improvements

- Add an OLED display to show prediction results  
- Collect more training samples from more users  
- Redesign the enclosure with better PCB space planning  
