// Includes
#include <iostream>
#include <mavlink.h>
#include <common.h>
#include <chrono>
#include <thread>

// Custom includes
#include "handle_msg_mavlink.h"
#include "handle_serial_port.h"
#include "command_mavlink.h"

int32_t A_lat = -353630743;
int32_t A_lon = 1491646454;
float A_alt = 5;
int32_t B_lat = -353638947;
int32_t B_lon = 1491648283;
float B_alt = 6;
int32_t C_lat = -353637206;
int32_t C_lon = 1491660477;
float C_alt = 5;

int32_t t = 0;
bool start_timer = false;
uint8_t stage = 0;

void timer_increment(void)
{
    t = t + 1;
}

void timer_reset(void)
{
    t = 0;
}

int main() 
{
    // Desired interval of 9 microseconds
    std::chrono::microseconds desiredInterval(50000);

    // Initialize serial port
    open_socket();
    configure_socket();
    connect_to_sitl();

    // Start data streams
    set_message_rates();
    request_messages();

    // Execute startup commands
    startup_sequence();

    // Receive and handle Mavlink messages
    while (true) 
	{
        auto startTime = std::chrono::high_resolution_clock::now();

        // Read serial port looking for mavlink messages
        get_messages();
        if (altitude > (int32_t)593000 && stage == 0)
        {
            // Move to waypoint
            printf("Moving to A\n");
            start_timer = true;
            stage = stage + 1;
            go_to_waypoint(A_lat, A_lon, A_alt);

        }

        if (t > 200 && stage == 1)
        {
            printf("Moving to B\n");
            stage = stage + 1;
            go_to_waypoint(B_lat, B_lon, B_alt);
        }

        if (t > 400 && stage == 2)
        {
            printf("Moving to C\n");
            stage = stage + 1;
            go_to_waypoint(C_lat, C_lon, C_alt);
        }

        if (t > 600 && stage == 3)
        {
            printf("Returning to base\n");
            start_timer = false;
            stage = stage + 1;
            landing_sequence();
            timer_reset();
        }

        if (start_timer == true)
        {
            timer_increment();
        }

        // Handle the loop rate
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

        if (elapsedTime < desiredInterval)
        {
            std::this_thread::sleep_for(desiredInterval - elapsedTime);
        }
    }

    return 0;
}

