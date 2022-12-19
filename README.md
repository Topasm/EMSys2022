# 2022 Embedded System team project
Myongji University Undergraduate student project

### Target device
#### CNDI eCUBE
- Ubuntu 14.04LTS
- NXP i.MX6 Quad-Core 1GHz
- 7 inch screen
- FND, Buzzer, LED, Color LED, Accelerometer, Magnetometer, Temperture Sensor, Button, Gyroscope Sensor


#### Project rules
- Use compile languages (C, C++)
- Use frame buffer when screen uses
- Use more than 5 sensors listed above


## Project Description : MARI MARU Volleyball game

There are famous game pikachu volleyball that everyone knows. So we implemented this game into our device with some changes. This game can play 2 users as same as orignal game and can toss the ball too. Charater of this game is  Mari & Maru (official character of Myongji University).


## How to play
1. Download game(mju_baegu.out) and source folder in same folder.
2. Run game file.
3. Choose player (if you choose mari opponent should be mari).
4. Put ip address and enter. game will start soon.
5. Tilt the device to move charater left or right.

## How it works
- C socket communication used to connet two devices via TCP method
- Gyro sensor data (rad/s) integrals are add up to charater position. This is not physically correct but okay for game
- AABB collision algorism for collision detection between ball and charater.
- PNG images load by lodepng library all pngs are merged with one buffer array then copy to frame buffer
(this can prevent flickering, tranperancy of png img can implemented too)
- Led ON/OFF for score
- Buzzer for Background music
- text lcd shows game start and charater select
- button for character select

