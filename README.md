# FOTA_NTI_GraduationProject
This repo will be used to Document our Firmware Over The Air graduation project as a part of our 4 month Embedded Diploma sponsored by the NTI


## Hardware Components Used:
1- Raspberry Pi 3 model B

2- 3 STM32f103C8T6

3- 2 High-Speed CAN Transceiver MCP2551-I/P 

4- ST Link V2 (optional ...a debugger that was used only during development and it was very useful to solve any bugs in the STM32)  

Note: all these components we bought from a local electronics store in cairo called Ram Electronics but you can find these components in almost any electronics store


## Software Components Used:
1- Raspbian Image for the Raspberry PI -> you can download it from there : https://www.raspberrypi.com/software/

2- Eclipse with the ARM based toolchain

3- Firebase Accout with Realtime Database Service Configured ->this video had some info about how to set up the Cloud Service  https://www.youtube.com/watch?v=Orp1QqKN5rc&t=338s

4-Vscode with Ssh extension for remote connection to the PI-> this video had all the info i needed : https://www.youtube.com/watch?v=BkQ2hL0fkWM

Note: when downloading the Raspbian Image you need to enable SSH so we can connect Vscode from our PC to the PI so we can deploy and develop code on the PI


![pi_imager_advanced](https://github.com/ahmed19897/FOTA_NTI_GraduationProject/assets/45523675/1a122508-f7fc-44ba-98d8-5e3c49296916)


## Project Architecture


![BLOCK DIAG](https://github.com/ahmed19897/FOTA_NTI_GraduationProject/assets/45523675/72e4d33a-99b4-40ac-afef-c28fbfd5e239)
