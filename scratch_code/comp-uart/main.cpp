// Custom headers
#include "standard_libs.h"
#include "global_objects.h"
#include "serial_port_handler.h"
#include "mavlink_msg_handler.h"
#include "mavlink_command_handler.h"
#include "scheduler.h"
#include "time_calc.h"

// Test flights
#include "sim_flight_test_1.h"

int main() 
{
    initialize();
    startTask_25ms();

    while (!stopProgram) 
	{
        // Main code is executed in task_25ms()
    }

    stopTask_25ms();

    return 0;
}

void initialize(void)
{
    // Code here is to be run once at the start of the program
    calcStartTimeMS();
    setupTask_25ms();

    // Setup serial communication
    open_serial_port();
    configure_serial_port();

    // Set rates and request mavlink data from the flight controller
    set_message_rates();
    request_messages();

    // Startup commands for drone
    startup_sequence();
}

// Function to handle timer interrupt at 40Hz
void task_25ms(int sig, siginfo_t* si, void* uc)
{
    std::lock_guard<std::mutex> lock(mutex);

    calcExecutionTime(); // printf("Elapsed Time: %d\n", elapsedTimeMS);
    test_flight_1();
}