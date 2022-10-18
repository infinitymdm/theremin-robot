This is currently a work in progress! Once complete, this repository will contain all resources necessary to build and program a basic arduino robot that steers based on audio frequency, plus a small theremin-like controller. 

## Purpose

The goal of this project is to introduce high-school-aged students to a variety of electrical,mechanical, and computer engineering concepts. We hope that this will inspire young people to consider engineering as an interesting and fulfilling career option. 

## Project Description

This project should provide you all the information you need to construct the two halves of this project: a simple audio-controlled robot and a small theremin controller. 

The robot is based around a Seeedstudio XIAO RP2040 and is programmed using the Arduino IDE. It uses its microphone to measure the loudest frequency in the environment and steers based on that frequency. (The actual details of the steering implementation are discussed a bit later - that's a part of the fun of the project!) 

The theremin is based around a 555 timer set up as an oscillator. The oscillation frequency is controlled by a photoresistor. The output of the oscillator is fed to a piezoelectric speaker. This combination lets you vary the pitch of the audio by increasing or decreasing the amount of light on the photoresistor. 

Your task is to choose components for the theremin such that its output varies within a desired frequency range, and to program the robot such that it can easily be controlled using the theremin. 

## Hardware

### Bill of Materials

#### For the Robot:
- 1 line follower robot kit (TODO: add link)
- 1 Seeedstudio XIAO RP2040 (TODO: add link)
- 1 KY-037 microphone sensor for Arduino (TODO: add link)
- 1 2-position DIP switch (TODO: add link)
- 1 miniature breadboard (TODO: add link)
- 2 AA batteries

#### For the Theremin: 
- 1 555 timer (TODO: add link)
- 1 photoresistor (TODO: add link)
- 1 piezo speaker (TODO: add link)
- 1 9V battery connector (TODO: add link)
- Resistors
    - TODO: add values and quantities
- Capacitors
    - TODO: add values and quantities
- 1 miniature breadboard (TODO: add link)
- 1 9V battery

#### For both (and your future electronics projects): 
- Wire kit (TODO: add link)

### Assembly Instructions

TODO

## Software

### Setting up Arduino IDE

#### Install the Board Support Package for the Seeedstudio XIAO RP2040
1. Open Arduino IDE. Click File > Preferences. The Preferences dialog window should appear.
2. In the “Additional Board Manager URLs” field, paste the following hyperlink:
    - https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json 
3. Click OK to close the Preferences Dialog.
4. Click Tools > Boards > Boards Manager. The Boards Manager dialog window should appear.
5. In the search bar, type “xiao”. The results should update with a single result labeled “Raspberry Pi Pico/RP2040”. Click install to download the board support package.
6. Click Close to close the Boards Manager dialog. 
7. Click Tools > Boards > Raspberry Pi RP2040 Boards > Seeed XIAO RP2040. Arduino should now be ready to program the Seeed XIAO RP2040 board. 

#### Download the arduinoFFT library
1. Open Arduino IDE. Click Tools > Manage Libraries. The Library Manager dialog window should appear.
2. In the search bar, type "arduinoFFT". The results should update with a single result labeled "arduinoFFT" by Enrique. Click install to download the software package. 
3. Click Close to close the Library Manager dialog. Arduino should now have access to the arduinoFFT library includes.

#### Download the robot source code
TODO