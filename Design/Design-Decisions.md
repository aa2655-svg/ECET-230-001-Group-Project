# Design Decisions

## Block Diagram
<img width="835" height="794" alt="block diagram" src="https://github.com/user-attachments/assets/d2a40835-49a0-48e3-a900-833b4614970d" />


## Current Design Choices
- **Controller**: Arduino Uno (chosen for simplicity and cost)
- **Power Supply**: 9V Battery, Charger
- **Outputs**: Gripper, laser, LED, LCD Display
- **Sensor**: Gyroscope for position feedback
- **Wireless**: RF Transmitter and Reciever

## Componenet Selection
| Components | Manufactura name | datasheet |
|----------|----------|----------|
| Arduino Uno x2 | Data     |     | https://www.ti.com/lit/ds/swrs039b/swrs039b.pdf?ts=1758485023645&ref_url=https%253A%252F%252Fwww.google.com%252F
| RF Transmitter | Data     | More    |

## Alternatives Considered
- Esp32
- STM32
- DC motors

## Future Decisions To Be Made
- Deciding on the microcontroller and servo motors to use

## Guiding Principles
- Must be controlled with a gyroscope/Accelerometer
- Must use LED as an indicator
- Integrate a laser and a gripper together somehow
- Use servos x3 max
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
- Size: Approximately 10 inches maybe
- Servo (MS90) for joint movement

