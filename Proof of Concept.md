# Proof of Concept
## Objective 
The purpose of this proof of concept is to demonstrate that we can control a robotic system can be controlled using motion data from an MPU6050 gyroscope/accelerometer to drive servo motor movement, with basic user feedback through an LED and LCD. This will validate the feasibility of the system’s sensor-controller-actuator architecture and verifies that the Arduino can be reliably handle real-time sensor input, motor control and user feedback simultaneously. 
Establishing this functionality at a small scale allows the design to be confidently expanded to a multi-degree-of-freedom robotic arm with multiple servos, a gripper mechanism and wireless communication.
## Core Idea to Prove
This proof of concept focuses on validating three key aspects of the system
## Motion Sensing and Control
-	Demonstrate that orientation data (pitch and/or roll) from MPU6050 can be read by the Arduino using I2C communication. 
-	Show that this sensor data can be mathematically mapped to a servo motor angle.
-	Confirm that physical motion of the sensor results in proportional, smooth movement of the servo motor.
## User Feedback and System Awareness
-	Demonstrate that LED indicators can communicate system states such as power-on and active motion.
-	Show that a 16x2 LCD display can present meaningful system messages to the user (e.g., readiness, motion status).
## System Integration and Stability
-	Demonstrate that the Arduino can manage sensor input, actuator output, and user feedback devices simultaneously without resets, erratic behavior or communication failure. 
-	Confirm that the system operates safely within defined servo limits, avoiding mechanical over-rotation or damage. 

## Prototype Setup 
For the proof of concept, we will use a simplified breadboard prototype with:
-	Arduino Uno (x2) – main controller responsible for sensor processing, logic execution, and output control
-	MPU6050 Gyroscope (x1) – provides real-time orientation and motion data
-	Servo Motor (x5) – demonstrates controlled mechanical motion based on sensor input 
-	LED Indicator (x2) – provides immediate visual feedback for system power and motion activity
-	LCD Display (x2)  - displays basic system status and messages
-	Resistors and Jumper Wires – supporting components for safe and reliable connections
(Other listed components like gripper, multiple servos, RF communication, and buck converter will be integrated later during full prototype development)
## Test Plan
We will validate our proof of concept through three main demonstrations
### Test 1: Sensor-to-Servo Control
-	Tilt the MPU6050 in one axis
-	Servo rotates proportionally to the tilt
-	Confirms MPU6050 can be used for motion-based control
### Test 2: User Feedback
-	LED turns ON when system is powered
-	LED blinks while the servo is moving
-	Confirms user can visually detect system states
### Test 3: Display Output
-	LCD shows basic messages such as “System Ready”, “Servo Moving”. The display may also be used to show battery life and servo motor angles.
-	Confirms Arduino can handle both display and control simultaneously
## Expected Results
-	Servo responds smoothly to MPU6050 input 
-	LED correctly indicates system state (power on, movement active)
-	LCD provides real-time user instructions/feedback
-	No overheating, miswiring or component failures during the test
## Next Steps after POC
Once proof of concept is successful, the following will be added:
-	Gripper mechanism with servo-controlled opening/closing
-	RF transmitter and receiver for wireless communication between two Arduinos
-	Buck converter and voltage regulation for battery power integration
-	Optimized CAD design for robot body and servo placement
## Conclusion
This proof of concept shows feasibility of using an MPU6050 sensor to control mechanical motion through servo motors while providing real-time user feedback via LED indicators and an LCD display. By validating sensor communication, actuator control, and system integration at a small scale, this POC establishes a strong foundation for the development of a more advanced multi-degree-of-freedom robotic system. 
