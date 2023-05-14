//#define _POSIX_C_SOURCE 200809L // enable certain POSIX-specific functionality

#include <mavlink.h>
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define SERIAL_PORT "/dev/ttyS3"
#define BAUD_RATE B115200

// Function prototypes
void print_heartbeat(mavlink_heartbeat_t heartbeat);
void print_sys_status(mavlink_sys_status_t sys_status);
void print_gps_raw_int(mavlink_gps_raw_int_t gps_raw_int);
void print_attitude(mavlink_attitude_t attitude);
void print_global_position_int(mavlink_global_position_int_t global_pos_int);
void print_request_data_stream(mavlink_request_data_stream_t request);

// Function definitions
void print_heartbeat(mavlink_heartbeat_t heartbeat)
{
    printf("Heartbeat:\n");
    printf("\tType: %d\n", heartbeat.type);
    printf("\tAutopilot: %d\n", heartbeat.autopilot);
    printf("\tBase mode: %d\n", heartbeat.base_mode);
    printf("\tCustom mode: %d\n", heartbeat.custom_mode);
    printf("\tSystem status: %d\n", heartbeat.system_status);
    printf("\tMavlink version: %d\n", heartbeat.mavlink_version);
}

void print_raw_imu(mavlink_raw_imu_t raw_imu) 
{
    printf("Raw IMU data:\n");
    printf("\tTime: %llu\n", (unsigned long long)raw_imu.time_usec);
    printf("\tX acceleration: %d\n", raw_imu.xacc);
    printf("\tY acceleration: %d\n", raw_imu.yacc);
    printf("\tZ acceleration: %d\n", raw_imu.zacc);
    printf("\tX gyro: %d\n", raw_imu.xgyro);
    printf("\tY gyro: %d\n", raw_imu.ygyro);
    printf("\tZ gyro: %d\n", raw_imu.zgyro);
    printf("\tX magnetometer: %d\n", raw_imu.xmag);
    printf("\tY magnetometer: %d\n", raw_imu.ymag);
    printf("\tZ magnetometer: %d\n", raw_imu.zmag);
}

void print_command_ack(mavlink_command_ack_t command_ack) 
{
    printf("Command ACK received:\n");
    printf("\tCommand: %u\n", command_ack.command);
    printf("\tResult: %u\n", command_ack.result);
}

void print_request_data_stream(mavlink_request_data_stream_t request)
{
    printf("Request Data Stream:\n");
    printf("\tTarget System ID: %d\n", request.target_system);
    printf("\tTarget Component ID: %d\n", request.target_component);
    printf("\tRequest Stream ID: %d\n", request.req_stream_id);
    printf("\tRequested Message Rate: %d\n", request.req_message_rate);
    printf("\tStart/Stop Stream: %d\n", request.start_stop);
}

int main()
{
    // Open the serial port for reading and writing
    int serial_port = open(SERIAL_PORT, O_RDWR | O_NOCTTY);
    if (serial_port < 0) 
    {
        std::cerr << "Error opening serial port" << std::endl;
        return 1;
    }

    // Set the baud rate, data bits, parity, and stop bits
    struct termios serial_config;
    tcgetattr(serial_port, &serial_config);
    cfsetispeed(&serial_config, BAUD_RATE);
    cfsetospeed(&serial_config, BAUD_RATE);
    serial_config.c_cflag |= (CLOCAL | CREAD);
    serial_config.c_cflag &= ~PARENB;
    serial_config.c_cflag &= ~CSTOPB;
    serial_config.c_cflag &= ~CSIZE;
    serial_config.c_cflag |= CS8;
    tcsetattr(serial_port, TCSANOW, &serial_config);

    // Initialize the Mavlink message buffer
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    // Initialize the Mavlink status
    mavlink_status_t status = {};

    /*** scratch code
    // Subscribe to HEARTBEAT message
    // sysid, compid, msg pointer, type, autopilot, base_mode, custom_mode, system_status
    //mavlink_msg_heartbeat_pack(0, MAV_COMP_ID_ALL, &msg, 0, 0, 0, 0, MAV_STATE_STANDBY);
    
    // Request MAVLINK messages at X Hz
    //mavlink_msg_command_long_pack(0, MAV_COMP_ID_ALL, &msg, 0, 0, MAV_CMD_REQUEST_MESSAGE, 0, MAVLINK_MSG_ID_RAW_IMU, 0, 0, 0, 0, 0, 0);
    ***/

    // define system and component ID for companion computer
    uint8_t SENDER_SYS_ID = 0;
    uint8_t SENDER_COMP_ID = 0;
    
    // Send a heartbeat message to the SITL simulation
    mavlink_msg_heartbeat_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, MAV_TYPE_ONBOARD_CONTROLLER, MAV_AUTOPILOT_INVALID, 0, 0, MAV_STATE_STANDBY);
    
    uint16_t len = mavlink_msg_to_send_buffer(&buffer[0], &msg);
    
    // Set the message rate for MAVLINK message to X Hz
    // system_id, component_id, msg pointer, target_system, target_component, command, 0, param1, param2, param3, param4, param5, param6, param7
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, 1, 1, MAV_CMD_SET_MESSAGE_INTERVAL, 0, MAVLINK_MSG_ID_RAW_IMU, 10000, 0, 0, 0, 0, 0);

    len = len + mavlink_msg_to_send_buffer(&buffer[len], &msg);

    // Request specific MAVLINK message
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, 1, 1, MAV_CMD_REQUEST_MESSAGE, 0, MAVLINK_MSG_ID_RAW_IMU, 0, 0, 0, 0, 0, 0);

    len = len + mavlink_msg_to_send_buffer(&buffer[len], &msg);
    /*
    // Send message to flight controller
    ssize_t n = write(serial_port, buffer, len);
    if (n < 0) 
    {
        std::cerr <<  "Error writing to serial port" << std::endl;
        return 1;
    }
    */
    // Receive and handle Mavlink messages
    while (true) 
    {   
        // Read a byte from the serial port
        uint8_t byte;
        if (read(serial_port, &byte, 1) == -1) 
		{
            std::cerr << "Error reading from serial port" << std::endl;
            return 1;
        }

        // Parse the byte and check if a message has been received
        if (mavlink_parse_char(MAVLINK_COMM_0, byte, &msg, &status)) 
		{
            // Handle the message based on its type
            switch (msg.msgid) 
			{
                case MAVLINK_MSG_ID_HEARTBEAT:
		    		mavlink_heartbeat_t heartbeat;
                    mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                    print_heartbeat(heartbeat);
                    break;
				case MAVLINK_MSG_ID_RAW_IMU:
					mavlink_raw_imu_t msg_raw_imu;
					mavlink_msg_raw_imu_decode(&msg, &msg_raw_imu);
					print_raw_imu(msg_raw_imu);
					break;
				case MAVLINK_MSG_ID_COMMAND_ACK:
					mavlink_command_ack_t command_ack;
					mavlink_msg_command_ack_decode(&msg, &command_ack);
					print_command_ack(command_ack);
					break;
	        default:
		    	std::cout << "Received message with ID " << (int)msg.msgid << std::endl;
            }
        }
    }

    // Close the serial port
    close(serial_port);

    return 0;
}

