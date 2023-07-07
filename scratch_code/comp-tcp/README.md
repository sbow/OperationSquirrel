# Description
This code is an example of using mavlink over TCP with the ArduPilot SITL.  It will ARM the drone (if pre-arm checks pass), request IMU mavlink messages, and cause the drone to takeoff to a set height and display messages in the terminal.  It is intended to be used for testing companion computer code without any hardware.  One thing to note with this code is that when communicating with the SITL over TCP, the communication speed may be significantly faster than the UART connection that the actual companion computer will be using.  This might make it less realistic.  Take this into account when testing companion computer logic with this code.

Some of the code is commented out intentionally, and the print functions are to help debug.

## How to use this code
1. Execute `make` to build the example
2. Execute `sudo ./main` (for drone to ARM make sure pre-arm checks are passing)
3. Execute `make clean` to remove the build files including the executable

## Connect compiled executable to ArduPilot SITL on Windows WSL2
1. Go to ArduCopter directory
	- `cd ardupilot/ArduCopter`
2. Start the SITL and access the uart port that the Jetson-Nano is connected to
	- `sim_vehicle.py --console --map`
3. Execute the program in another instance of WSL2
    - `sudo ./main`
4. The drone should ARM, send back messages, and takeoff