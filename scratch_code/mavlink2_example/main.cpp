// Includes
#include <iostream>
#include <mavlink.h>
#include <common.h>

// Custom includes
#include "handle_msg_mavlink.h"
#include "handle_serial_port.h"
#include "command_mavlink.h"

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

    // Receive and handle Mavlink messages
    while (true) 
	{
        // Read serial port looking for mavlink messages
        get_messages();
    }

    return 0;
}

