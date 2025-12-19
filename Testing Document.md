# Testing Document
##Introduction

This document describes the testing procedures used to verify the functionality, safety and reliability of this project. The moving arm integrates multiple servo motors, a microcontroller and inverse kinematics to perform controlled and coordinated motion. Because the system combines mechanical components, electrical hardware and software logic, structured testing is necessary to ensure that each subsystem operates correctly both individually and as part of the complete system.

Objective
The objective of this testing document is to define a set of manual and automatic tests that can be performed by any user or developer building the moving arm to confirm proper operation at the user level. These tests are designed to verify that:
Each servo motor responds correctly and remains within safe mechanical limits
Automatic and inverse-kinematics based movements behave predictably and smoothly
The robotic arm performs coordinated motion across multiple degrees of freedom
User feedback mechanisms (such as the LCD display and status indicators) function as intended
The system operates safely without causing mechanical interference, overheating or damage
Successful completion of the tests outlined in this document demonstrates that the moving arm system meets functional requirements and is suitable for demonstration and further development.

Test Environment & Pre-Checks
Hardware Setup 
All servos are connected to the correct pins
External 5 V power is used for the servos 
MPU6050 (if used) is wired correctly (SDA, SCL, VCC, GND)
LCD is connected to the correct pins
Receiver
Transmitter
Software Setup 
The correct Arduino sketch is uploaded
Arduino Serial Monitor is set to the correct baud rate
Safety
The arm has enough free space without hitting objects
Nothing is blocking the joints
One hand is near the power switch in case of unexpected behavior 
Manual Tests (User-Level Verification): These tests can be done by anyone building the system to confirm basic functionality
Servo Power & Idle Test: Verify that all servos power on and hold position
Steps
Power on the system with the test code loaded
Confirm each servo moves briefly to a neutral position or holds still (depending on the sketch)
Lightly touch each joint to feel that it resists motion (servo is powered)
Pass Criteria:
All joints feel “stiff” (powered)
No servo makes continuous grinding and stalling noise
LCD Feedback Test: Verify that the LCD provides meaningful user feedback (e.g., servo angles or system status).
Steps 
Power on the system
Confirm that the initial message appears (e.g., “Initializing…” or “System Ready!”)
Move the arm or let the automatic routine run
Confirm that the LCD updates with Base angle, Gripper angle or other configured values (e.g., pitch angle, status text).
Pass Criteria
All LCD characters are visible and readable
Display updates when servos move (no frozen display)
Values makes sense (e.g., angles in a reasonable range, not random numbers)
Automatic Tests (No Manual Input Required): These tests rely on the automatic demo code to verify system behavior at the user level
Steps
Upload the automatic 5-DoF test code with limits
Power the system
Observe the sequence 
Base rotates from its minimum angle to maximum and back
Shoulder moves up and down
Elbow bends and strengthens
Wrist pitch tilts up and down
Gripper opens and closes within safe range
Pass Criteria
Each joint moves smoothly with no jerky movements
No joint moves beyond its mechanical limits 
Gripper does not cross or jam when “closing”
System can complete several cycles without overheating or stalling
Gripper Safety Test: Verify that the gripper never fully crosses or damages itself
Steps
Run the automatic motion sequence
Watch only the gripper joint
Observe the fully open and fully closed positions
Pass Criteria 
In “closed” position, the gripper fingers are gripping but not overlapping or forcing each other
No clicking, grinding, or visible strain on the plastic
Servo returns smoothly to open position
Basic Safety and Reliability Tests: Ensure the system can operate for a short continuous period without failure
Steps
Run the automatic demo motion for 5-10 minutes
Periodically touch the servos to check temperature
Listen for unusual noises or stalling
Pass Criteria
No servo gets dangerously hot
No mechanical parts come loose
Motions remain consistent over time
Summary
	By performing the tests above, a user can verify that all motors are powered and mapped correctly, motion is smooth and stays inside safe limits, the LCD correctly reports system status or angles, the gripper operates safely and does not over-close. These tests together confirm that the major user-level functionality of the 5 DoF robotic arm is working as intended.
