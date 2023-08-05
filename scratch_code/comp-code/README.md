# Description
This code is an example of using mavlink over UART between the jetson-nano and
a drone flight controller or ArduPilot SITL.  It can also be configured to work in WSL2 and connect to the ArduPilot SITL without any additional hardware.  It will ARM the drone (if pre-arm checks pass), request IMU mavlink messages, and cause the drone to takeoff to a set height, flight in a pattern and return to home.  It should easily work for raspberry pi or other companion computers, however the UART will likely need to be configured a little differently.  They would just need to have the UART port configured differently and use the appropriate read and write functions for the desired platform.

Some of the code is commented out intentionally, and the print functions are to help debug.

#### For testing purposes, run this command before executing the program on the jetson-nano.  It temporarily enables access to the physical UART port (or whichever port you need to access) if it doesn't automatically work when executing the code.  You may be able to run the code without this command, so you may try that first.
`sudo chmod a+rw /dev/ttyTHS1`

## How to use this code
1. Execute `make` to build the example
2. Execute `sudo ./main` (for drone to ARM make sure pre-arm checks are passing)
3. Execute `make clean` to remove the build files including the executable
4. If running on the Jetson-Nano using UART, uncomment one of the following lines in the Makefile to compile for use on
   the Jetson Nano using UART or on WSL2 using a TCP connection
   - CFLAGS += -DUSE_UART
   - CFLAGS += -DUSE_TCP

#### Other preprocessing directives will be added to configure the code to enable or disable other features

## Connect Jetson-Nano to ArduPilot SITL on Windows WSL2
1. Connect Jetson-Nano UART ports to FTDI device (3v3 logic)
2. Connect FTDI device to laptop
3. Set up USBIPD https://learn.microsoft.com/en-us/windows/wsl/connect-usb (first time only)
4. Check what devices are visible using windows powershell (see what bus ID the FTDI device is)
	- `usbipd wsl list`
5. Open WSL2 instance
6. Attach the FTDI device to WSL2 using windows powershell
	- `usbipd wsl attach --busid 2-1` (or whatever the bus id matches your device)
7. Change owner of device
	- `sudo chown root:dialout /dev/ttyUSB0`
8. Check that device is added to dialout
	- `ls -l /dev/ttyUSB0`
9. Give read+write access to the device
	- `sudo chmod g+rw /dev/ttyUSB0`
10. Go to ArduCopter directory
	- `cd ardupilot/ArduCopter`
11. Start the SITL and access the uart port that the Jetson-Nano is connected to
	- `sim_vehicle.py --console --map -A --serial2=uart:/dev/ttyUSB0:115200`
12. Execute the program on the Jetson-Nano
    - `sudo ./main`
13. The drone should ARM, send back messages, and takeoff

## Connect Jetson-Nano to real flight controller
1. Connect Jetson-Nano UART ports to flight controller UART
2. Configure the appropriate flight controller UART port in mission planner to send and receive mavlink messages
3. Execute the program on the Jetson-Nano
    - `sudo ./main`
13. The drone should ARM, send back messages, and takeoff

## Connect compiled executable to ArduPilot SITL on Windows WSL2
1. Go to ArduCopter directory
	- `cd ardupilot/ArduCopter`
2. Start the SITL and access the uart port that the Jetson-Nano is connected to
	- `sim_vehicle.py --console --map`
3. Execute the program in another instance of WSL2
    - `sudo ./main`
4. The drone should ARM, send back messages, and takeoff