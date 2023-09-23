# Smart Car Security System

## Project Description

This project utilizes an Arduino Mega board to create a versatile RFID-controlled car with additional features like ultrasonic sensors, buttons, a buzzer, and an LDR sensor. The system enables you to control the car's movements, interact with RFID cards, and respond to its surroundings.

## Components Used

To build this project, you will need the following components:

1. Arduino Mega board
2. Ultrasonic sensors
3. RFID reader/writer
4. Buttons
5. Buzzer
6. LDR sensor
7. Car chassis with motors
8. H-Bridge motor driver
9. Batteries for the car (battery type depends on the car chassis)
10. Power source for the Arduino (e.g., a 9V battery)
11. Jumpers and wires
12. Breadboard

## Project Overview

This project combines hardware components and software to create an interactive RFID-controlled car with additional sensor functionalities. The key features of the project include:

- **RFID Card Control**: The RFID reader/writer allows you to scan MIFARE Classic cards. When a card is detected, the Arduino can read and write data to it, enabling secure access control or data storage.

- **Ultrasonic Sensors**: Ultrasonic sensors are used to measure distances on the right and left sides of the car. This data can be used for obstacle detection, navigation, or other applications.

- **Button Interface**: Buttons are integrated into the project to trigger various actions or modes, enhancing user control.

- **Buzzer Feedback**: The buzzer provides auditory feedback, such as alerts or warnings, based on the car's status or sensor readings.

- **Light Sensing**: The LDR sensor can detect ambient light levels, allowing the car to respond to changes in light conditions.

- **Motor Control**: An H-Bridge motor driver is used to control the car's motors, enabling it to move forward, backward, left, or right.

## Tasks and Threads

The project is structured with multiple tasks running concurrently to manage different aspects of the car's functionality. These tasks include:

1. **Start Engine Task**: Monitors a button to start or stop the car's engine. When the engine is started, the car becomes operational.

2. **Open Buzzer Task**: Controls the buzzer to provide sound feedback when specific conditions are met, such as seat belt warnings.

3. **Night Vision Task**: Uses the LDR sensor to detect light levels and adjust the car's behavior accordingly, such as turning on lights in low-light conditions.

4. **Ultrasonic Sensor Tasks**: Two separate tasks read data from ultrasonic sensors on the right and left sides of the car to measure distances.

## Software Integration

The software for this project is written in Arduino C/C++ and can be further customized to suit your specific requirements. The Arduino Mega board provides a versatile platform for hardware interaction and control.

## Project Outcome

Upon completion, this project results in an RFID-controlled car that responds to RFID card inputs, avoids obstacles using ultrasonic sensors, provides user feedback through a buzzer, and adapts to lighting conditions with the LDR sensor.

## Getting Started

To run this project, follow these steps:

1. Assemble the hardware components as per the circuit connections defined in the source code.

2. Upload the provided Arduino sketch, named "smart_car_security_system.ino," to your Arduino Mega board using the Arduino IDE.

3. Power the system using the appropriate power sources for the Arduino and the car's motors.

4. Observe the car's behavior based on RFID card inputs, obstacle detection, and sensor readings.

## Video


https://github.com/Ziaad-Khaled/smart-car-security-system/assets/77291238/eb0681a9-a5d4-49ff-a0ba-23c15f24e229



Feel free to modify and expand upon this project to explore more functionalities and applications. Enjoy building and experimenting with your RFID-controlled car!
