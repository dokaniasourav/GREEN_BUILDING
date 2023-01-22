# Decentralized AC Controller

## This project was submitted for the IICDC-2016 contest by me, Ayush Agarwal and Chirag Mehta.
----------------------------------------------------------------------------------
----------------------------------------------------------------------------------

#### Checkout the YouTube Video [Part 1](https://www.youtube.com/watch?v=2Hlg9OIjZZw)
#### Also check out our [Final Submission](https://github.com/dokaniasourav/GREEN_BUILDING/blob/master/Final%20Submission.pdf)
----------------------------------------------------------------------------------

# Setup

### Introduction

In the previous part we discussed about the purpose of the project. Let us now discussed about
its working. The whole module is consistent of three sub-modules working independently,
namely

1. `Person Counter`
2. `User Interface`
3. `Signal processor & Actuator (Master)`

### The Person Counter

This device keeps a track of number of people inside a testing area. It can detect the incoming
and outgoing people and change the counter respectively. The device then sends this data to
the Master module.

_HARDWARE DESCRIPTION:_

This device has an additional flasher which produces the required IR signal required by a person
to cut in order to get detected. Both the module and its flasher are placed on opposite side of
the room. The diagrammatic description of this module is given below:-

![The Person Counter](https://github.com/dokaniasourav/GREEN_BUILDING/blob/master/Draw.png)

As we see this is consistent of many sub parts:

1. The Microcontroller: This device processes the sensor data and produces desired person
    count to be displayed and sent. It also transmits data to the Master module via
    Transceiver.
2. The Transceiver: This is used to wirelessly transmit/receive person count data to the
    Master module.
3. The Seven Segment display: It displays the present person count value.
4. The Sensors: This is the sensing element which detects an intruded signal from the
    flasher and the Microcontroller processes this data to generate a person count.

## User Interface:

This module has an interactive interface and a visual guidance of all parameters in the room as
shown in the figure.

![The User Interface](https://github.com/dokaniasourav/GREEN_BUILDING/blob/master/UserInterface.png)

This module can be used to manually set the present person count in the room. The module
contains of various parts as follows:

1. The Display Device: It is a 16X2 LCD which displays the present person count, the
    ON/OFF states of all AC’s and the room temperature. This also displays the menus used
    for setting a few parameters in the room like person count.

- SELECT NEXT
- BUTTON BUTTON

2. The Microcontroller: It controls the Display Device and collects data received from the
    transceiver. The device also collects data from push-switches about setting modifying
    parameters (like person count) and is then sent to the master module.
3. The Transceiver: It receives all relevant data from the master module, which is then read
    by the microcontroller.
4. Tap-switches: They are used as input device for modifying master module parameters
    like person count.

## The Master Module:

This is the central processing unit of the room which with the help of Person Counter module
and the User Interface module controls the state of the air conditioners. The master as we shall
refer to it, collects person count data from the Person Counter module and three PIR sensors
fitted in the room to generate a status variable which determines which of the air conditioners
need to be On/Off at any given time. The AC’s are turned on and off using a remote control
fitted in front of all three ACs. The complete working of this module can be done by dividing it
into its component parts (sub modules).

![The Master Module](https://github.com/dokaniasourav/GREEN_BUILDING/blob/master/MasterMod.png)

1. PIR sensors: Three PIR (passive infrared sensors) are placed in different section of the
    room. They detect the movement of people in front of them. The data is fed to the
    microcontroller which processes them to predict the possible location of people in the
    room.
2. Temperature sensor: A temperature sensor detects the current temperature of the
    environment and the data is sent to the microcontroller. This data is used by the
    microcontroller to adjust the fan speed and operating temperature of ACs.
3. The Transceiver: This is a communicating device which with the help of microcontroller
    sends and receives data from the Person counter module and the User Interface
    module. The person count data is received from the person counter and modifying data
    is received from the User Interface. The current state of all AC’s, person count and
    current temperature is sent to the user interface periodically.
4. The IR Transmitters: An infrared led is placed in front of each AC which act as a remote
    controller. The data is sent from the microcontroller.
5. The EEPROM: This is a permanent memory storage device, like a SD card (only simpler
    and has lesser memory) used to store the various codes required for the IR transmitters
    to control the ACs. For example the code for turning on and turning off the AC. These
    codes are retrieved by the microcontroller when it needs to send them to the
    transmitters.

6. The Microcontroller: This is the central unit which constantly analyses all the data
    namely the person count, the PIR sensor data and room temperature and controls the
    states of all the AC’s using the remote controls.

