# FOTA_NTI_GraduationProject
This repo will be used to Document our Firmware Over The Air graduation project as a part of our 4 month Embedded Diploma sponsored by the NTI

when it comes to the Rapberry PI there were a few steps that needed to be taken before we can use it with : 1) firebase 
2) UART
3) run the scipts in the background of the PI ,so you can use if you want for other tasks and you can run multiple tasks at a time (which is handeled by the Systmd of the raspian image).


## Firebase

1- this repo was very useful. It provides a python wrapper API to the firebase C++ API -> https://github.com/thisbejim/Pyrebase#storage


## UART

the first step we did is to add an overlay in the config.txt of the kernel to assign the ttyAMA0 (which is the main Raspberry Pi serial port for communication with peripherals) to UART communication instead of Bluetooth in our case and this link was very useful for that -> http://www.deater.net/weave/vmwprod/hardware/pi-rts/

the second step was to disconnect the default login shell that is provided over the serial port of the board ,so we can assign the ttyAMA0 solely to our UART communication with the STM. Failure to do so caused UART overrun data because the board was trying to recieve from the STM while writing on the terminal and this link was very useful to do so -> https://www.instructables.com/Raspberry-PI-3-Enable-Serial-Communications-to-Tty/

## run the scipts in the background of the PI

This final step is optional but it is useful because it lets the Kernel handle the script schedulling and other properties that define how to run the python scripts according to your needs.This link was veryuseful ->https://stackoverflow.com/questions/64837834/run-python-script-on-startup-as-root 
I will put our .service file in the repo ,so you can take a look at it and customize it how you like it.
