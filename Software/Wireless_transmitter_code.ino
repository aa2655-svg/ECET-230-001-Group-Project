#include <MPU6050_tockn.h>
#include <Wire.h>
#include <RH_ASK.h>
#include <SPI.h>

MPU6050 mpu6050(Wire);
RH_ASK rf_driver(2000, 11, 12); 

const int calibLed = 4;
const int buttonPin = 2; // Button for Gripper

struct Data_Packet {
  int8_t x;
  int8_t y;
  int8_t z;
  int8_t gripper; // 0 for closed, 1 for open
};

Data_Packet data;

void setup() {
  pinMode(calibLed, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Uses internal resistor
  
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  digitalWrite(calibLed, HIGH);

  rf_driver.init();
}

void loop() {
  mpu6050.update();

  data.x = (int8_t)mpu6050.getAngleX();
  data.y = (int8_t)mpu6050.getAngleY();
  data.z = (int8_t)mpu6050.getAngleZ();
  
  // Read button: LOW means pressed because of INPUT_PULLUP
  if (digitalRead(buttonPin) == LOW) {
    data.gripper = 1; // Open
  } else {
    data.gripper = 0; // Closed
  }

  rf_driver.send((uint8_t *)&data, sizeof(data));
  rf_driver.waitPacketSent();
  delay(50); 
}
