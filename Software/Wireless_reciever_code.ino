#include <RH_ASK.h>
#include <SPI.h>
#include <ServoTimer2.h> 


// Initial Start Positions (Degrees)
int startBaseDeg     = 90;   
int startShoulderDeg = 50;   
int startElbowDeg    = 100;  
int startWristPDeg   = 90;   

// GRIPPER LIMITS (Degrees)
int gripOpenLimit    = 140; // Max open
int gripClosedLimit  = 125;  // Max closed
// ------------------------------------------------

RH_ASK rf_driver(2000, 11, 12); 
ServoTimer2 base, shoulder, elbow, wristPitch, gripper;

const int signalLed = 4; 

struct Data_Packet {
  int8_t x;
  int8_t y;
  int8_t z;
  int8_t gripperState; 
};
Data_Packet data;

void setup() {
  Serial.begin(9600);
  rf_driver.init();
  pinMode(signalLed, OUTPUT);

  // 1. Move to Initial Positions
  base.write(map(startBaseDeg, 0, 180, 750, 2250));
  shoulder.write(map(startShoulderDeg, 0, 180, 750, 2250));
  elbow.write(map(startElbowDeg, 0, 180, 750, 2250));
  wristPitch.write(map(startWristPDeg, 0, 180, 750, 2250));
  gripper.write(map(gripClosedLimit, 0, 180, 750, 2250));
  

  // 2. Attach pins
  base.attach(3);
  shoulder.attach(5);
  elbow.attach(6);
  wristPitch.attach(9);
  gripper.attach(10);

  Serial.println("Initial Position Set. Waiting 2 seconds...");
  delay(2000); // STAIR AT THE ROBOT NOW to see if positions are right!
  Serial.println("Starting MPU Control...");
}

void loop() {
  uint8_t buf[sizeof(data)];
  uint8_t buflen = sizeof(buf);

  if (rf_driver.recv(buf, &buflen)) {
    memcpy(&data, buf, sizeof(data));
    digitalWrite(signalLed, HIGH);

    // Convert MPU data to degrees
    int degZ = map(data.z, -90, 90, 0, 180);   
    int degX = map(data.x, -90, 90, 0, 180);   
    int degY = map(data.y, -90, 90, 0, 180);   
    int degE = 180 - degX; 

    // Gripper Logic with applied limits
    int targetGrip = (data.gripperState == 1) ? gripOpenLimit : gripClosedLimit;
    // Extra safety: ensure the logic never exceeds our limits
    targetGrip = constrain(targetGrip, gripClosedLimit, gripOpenLimit);

    // Write to Servos
    base.write(map(degZ, 0, 180, 750, 2250));
    shoulder.write(map(degX, 0, 180, 750, 2250));
    elbow.write(map(degE, 0, 180, 750, 2250)); 
    wristPitch.write(map(degY, 0, 180, 750, 2250));
    gripper.write(map(targetGrip, 0, 180, 750, 2250));

    // Monitor Output
    Serial.print("B:"); Serial.print(degZ);
    Serial.print(" | Grip:"); Serial.println(targetGrip);

    delay(5);
    digitalWrite(signalLed, LOW);
  }
}
