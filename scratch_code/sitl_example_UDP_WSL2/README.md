# Description
This code is an example of using mavlink over between the ArduPilot SITL and a simulated companion computer program.



# How to use this code
1. Follow the instructions at https://github.com/mavlink/mavlink to generate the C headers (included here for reference)
    
    a) Dependencies
        sudo apt install python3-pip

    b) Clone mavlink into the directory of your choice
        git clone https://github.com/mavlink/mavlink.git --recursive
        cd mavlink
        
        python3 -m pip install pymavlink/requirements.txt
        
    c) You can then build the MAVLink2 C-library for message_definitions/v2.0/common.xml
        python3 -m pymavlink.tools.mavgen --lang=C --wire-protocol=2.0 --output=generated/include/mavlink/v2.0 message_definitions/v1.0/common.xml
        
2. Change path of "/mavlink/v2.0/common" in your make file to match
3. Execute "make" to build the example
4. Execute "./sitl_example_UDP"
5. Execute "make clean" to remove the build files including the .exe

This code should be run after starting the ArduPilot SITL