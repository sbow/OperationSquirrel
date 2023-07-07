// Includes
#include <iostream>
#include <mavlink.h>
#include <common.h>
#include <chrono> //for wait functionality
#include <thread> //for wait functionality

// Custom includes
#include "handle_msg_mavlink.h"
#include "handle_serial_port.h"
#include "command_mavlink.h"
#include "global_objects.h"

int main() 
{
    // Initialize serial port
    open_serial_port();
    configure_serial_port();

    // Start data streams
    set_message_rates();
    request_messages();

    // Execute startup commands
    startup_sequence();

    //std::this_thread::sleep_for(std::chrono::seconds(10));



    // Receive and handle Mavlink messages
    while (true) 
	{
        // Read serial port looking for mavlink messages
        get_messages();
        if (altitude > (int32_t)594000)
        {
            // Execute landing commands
            landing_sequence();
        }
        else
        {
            printf("Max altitude not achieved\n");
        }
    }

    return 0;
}

