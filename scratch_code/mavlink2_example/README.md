# Description
This code is an example of using mavlink over UART between the jetson-nano and
a drone flight controller.  My drone flight controller is using ArduPilot.  It will ARM the drone (if pre-arm checks pass) and
display messages in the jetson-nano terminal.
###### For testing purposes, run this command before executing mavlink over uart on the jetson-nano, temporarily enables access to the port if it doesn't automatically work when executing the code
sudo chmod a+rw /dev/ttyTHS1 

# How to use this code
1. Execute "make" to build the example
2. Execute "./mavlink2_example" (for drone to ARM make sure pre-arm checks are passing)
3. Execute "make clean" to remove the build files including the .exe
