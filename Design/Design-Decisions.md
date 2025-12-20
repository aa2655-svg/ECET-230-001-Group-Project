# Design Decisions

## Block Diagram
<img width="971" height="568" alt="image" src="https://github.com/user-attachments/assets/23433afe-e750-48fe-b520-00bed206be9a" />
<img width="920" height="566" alt="image" src="https://github.com/user-attachments/assets/333ba76a-3fcb-492b-8567-0a657e466f2b" />



## Current Design Choices
- **Controller**: Arduino Uno (chosen for simplicity and cost)
- **Power Supply**: 9V Battery, Charger
- **Outputs**: Gripper, LED, LCD Display, Push Button
- **Sensor**: Gyroscope for position feedback, Ultrasonic sensor to detect objects and measure distances
- **Wireless**: RF Transmitter and Reciever

## Component Selection
| Components | Manufactura name | datasheet | Software Libraries |
|------------|------------------|-----------|--------------------|
| Arduino x2 | Arduino Uno      | https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf| |
| RF Transmitter and Reciever | 433MHz RF Transmitter/Receiver Module  | https://www.handsontec.com/dataspecs/module/433MHz-RF-Mod-2.pdf  | virtualWire.h, RadioHead.h, RH_ASK.h|
|Servos x5   |Mg90 servo      |https://components101.com/motors/mg90s-metal-gear-servo-motor|Servo.h|
|LCD display | Liquid crystal | https://www.vishay.com/docs/37484/lcd016n002bcfhet.pdf |wire.h |
|LED | | https://www.farnell.com/datasheets/1498852.pdf | | NA|
|Push Button | | | |
|Ultrasonic Sensor | | | |
|Buzzer| | | |
|Gyroscope | MPU5060 | https://www.digikey.com/htmldatasheets/production/1732757/0/0/1/sen-11028.pdf | |
|Breadboards| prototypin board| https://components101.com/sites/default/files/component_datasheet/Breadboard%20Datasheet.pdf | NA|
|Wires | | |
|Laser| | |

## Alternatives Considered
- Esp32
- STM32
- DC motors
- Laser

## Future Decisions To Be Made
- Implement Isaac Sim lab - NVIDIA
- Refine code
- Fix antenna issues

## Guiding Principles
- Must be controlled with a gyroscope/Accelerometer
- Must use LED as an indicator
- Use servos x5
- 9V battery Pack
- 9V battery

## Starting point
- Block Diagram
- Component selection
- Prototype
- Design the body
- PCB designing

## User Story
- Wear the controller and control the robot with your fingers

## User Interface
- Using your fingertip to move up, down, left, right, or a hand gesture.

## Priorities and Dependencies
- Getting all electronic equipment
- Size: Approximately 10 inches
- Servo (MS90 metal gear) for joint movement


## Checklist
- [x] Have modules ordered for your prototype
- [x] Have datasheets for what is on your modules
- [x] Have software libraries
- [x] Have development environment for software
- [x] Have breadboards, wires, mechanical elements
        - Need to complete mechanical elements
- [x] Have access to a workbench with appropriate tools
        - Need access to a workbench
