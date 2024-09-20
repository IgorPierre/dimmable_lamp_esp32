# Dimmable Lamp using ESP32 and Dimmer ESP32 Module

Project developed for the **Real-Time Software** course in the **Computer Engineering** program at the **Federal University of Ceará** (Sobral Campus). This project aims to apply concepts discussed during the course and to develop students' practical skills with microcontrollers.

## Objective
Control the light intensity of a dimmable lamp according to the ambient brightness using an **ESP32**, a **dimmer**, and a **light sensor**.

## Notes
Make sure to identify/modify the component pinout according to your board. In our case, this entire project was based on the ESP32-WROOM-32D board.

## Materials Used
- **ESP32**
  The specific model of the board used is the ESP32-WROOM-32D.
- **Dimmer ESP32 MC-8A 220V**
- **Dimmable Lamp**
  The lamp used had the following specifications:
  20500controlled |
  autodimmable 9W |
  100-240v |
  cool white 6500k fp > 0.7 |
- **Potentiometer B10k**
- **Wires and breadboard**

## Important Libraries
- **WiFi**
- **WebServer**

## Assembly
The assembly of the components must follow the pinout specified in the code, with special attention to the potentiometer and dimmer pins, as well as the proper connections for the ESP32 and the dimmable lamp. For the project, we used the following configurations:

- **GPIO Pin 5**: Connected to the Dimmer.
- **GPIO Pin 36**: Connected to the Potentiometer.
