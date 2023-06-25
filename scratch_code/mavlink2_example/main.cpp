#include <iostream>
#include <mavlink.h>
#include <common.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "print_mavlink.h"

#define SERIAL_PORT "/dev/ttyTHS1"
#define BAUD_RATE B115200



int main() {
    // Open thea serial port for reading and writing
    int serial_port = open(SERIAL_PORT, O_RDWR);
    if (serial_port < 0) {
        std::cerr << "Error opening serial port" << std::endl;
        return 1;
    }

    // Configure the serial port
    struct termios serial_config;
    tcgetattr(serial_port, &serial_config);
    serial_config.c_cflag = BAUD_RATE | CS8 | CLOCAL | CREAD;
    serial_config.c_iflag = IGNPAR;
    serial_config.c_oflag = 0;
    serial_config.c_lflag = 0;
    tcflush(serial_port, TCIFLUSH);
    tcsetattr(serial_port, TCSANOW, &serial_config);

    // Initialize the Mavlink message buffer
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    // Initialize the Mavlink status
    mavlink_status_t status = {};

    // define system and component ID for companion computer
    uint8_t SENDER_SYS_ID = 0;
    uint8_t SENDER_COMP_ID = 0;
    uint8_t TARGET_SYS_ID = 1;
    uint8_t TARGET_COMP_ID = 1;
	
    // Subscribe to HEARTBEAT message
    mavlink_msg_heartbeat_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, MAV_TYPE_ONBOARD_CONTROLLER, MAV_AUTOPILOT_INVALID, 0, 0, MAV_STATE_STANDBY);

    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

	// Request all message streams at a rate of X Hz
	// system_id, component_id, msg, target_system. target_component, req_stream_id, req_message_rate, start_stop
	// mavlink_msg_request_data_stream_pack(0, MAV_COMP_ID_ALL, &msg, 0, 0, MAV_DATA_STREAM_ALL, 50, 1);

    // Set the message rate for MAVLINK message to X Hz
    // system_id, component_id, msg pointer, target_system, target_component, command, 0, param1, param2, param3, param4, param5, param6, param7
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, 1, 1, MAV_CMD_SET_MESSAGE_INTERVAL, 0, MAVLINK_MSG_ID_RAW_IMU, 10000, 0, 0, 0, 0, 0);

    len = len + mavlink_msg_to_send_buffer(&buffer[len], &msg);

    // Request specific MAVLINK message
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, 1, 1, MAV_CMD_REQUEST_MESSAGE, 0, MAVLINK_MSG_ID_RAW_IMU, 0, 0, 0, 0, 0, 0);

    len = len + mavlink_msg_to_send_buffer(&buffer[len], &msg);

    // Set the flight mode
	mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, 1, 1, MAV_CMD_DO_SET_MODE, 0, MAV_MODE_FLAG_CUSTOM_MODE_ENABLED, 4, 0, 0, 0, 0, 0);
    
    len = len + mavlink_msg_to_send_buffer(&buffer[len], &msg);
    
    // Command to ARM the drone
	mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, 1, 1, MAV_CMD_COMPONENT_ARM_DISARM, 0, 1, 1, 0, 0, 0, 0, 0);
	
    len = len + mavlink_msg_to_send_buffer(&buffer[len], &msg);

    // Command to takeoff
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, MAV_CMD_NAV_TAKEOFF, 0, 0, 0, 0, 0, 0, 0, 15.0);
    
    len = len + mavlink_msg_to_send_buffer(&buffer[len], &msg);

    // Delay the next command for specified time
    //mavlink_msg_command_int_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, 5, MAV_CMD_NAV_DELAY, 0, 0, 10, 0, 0, 0, 0, 0, 0);
    
    //len = len + mavlink_msg_to_send_buffer(&buffer[len], &msg);
    
    // Command to set target position for the drone to fly to
    double latitude = -35.3617;  // Target latitude
    double longitude = 149.1649;  // Target longitude
    float altitude = 15.0;  // Target altitude in meters

    //mavlink_msg_set_position_target_global_int_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, 0, MAV_FRAME_GLOBAL_RELATIVE_ALT_INT, 0b0000111111111000, 0, 0, 0, latitude * 1e7, longitude * 1e7, altitude * 1e3, 0, 0, 0, 0, 0, 0, 0);
    

    // Send drone to waypoint
    //mavlink_msg_command_int_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, 5, MAV_CMD_DO_REPOSITION, 0, 0, 5, 0, 0, 0, (int)(latitude * 1e7), (int)(longitude * 1e7), 25);

    //len = len + mavlink_msg_to_send_buffer(&buffer[len], &msg);

    // Send message to flight controller
    ssize_t n = write(serial_port, buffer, len);
    if (n < 0) 
    {
        std::cerr <<  "Error writing to serial port" << std::endl;
        return 1;
    }

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
                    //print_heartbeat(heartbeat);
                    break;
                case MAVLINK_MSG_ID_GPS_RAW_INT:
		    		mavlink_gps_raw_int_t msg_gps_raw_int;
                    mavlink_msg_gps_raw_int_decode(&msg, &msg_gps_raw_int);
                    print_gps_raw_int(msg_gps_raw_int);
                    break;
                case MAVLINK_MSG_ID_ATTITUDE:
		    		mavlink_attitude_t msg_attitude;
                    mavlink_msg_attitude_decode(&msg, &msg_attitude);
                    print_attitude(msg_attitude);
                    break;
				case MAVLINK_MSG_ID_RAW_IMU:
					mavlink_raw_imu_t msg_raw_imu;
					mavlink_msg_raw_imu_decode(&msg, &msg_raw_imu);
					//print_raw_imu(msg_raw_imu);
					break;
				case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
					mavlink_global_position_int_t global_pos_int;
					mavlink_msg_global_position_int_decode(&msg, &global_pos_int);
					print_global_position_int(global_pos_int);
					break;
				case MAVLINK_MSG_ID_COMMAND_ACK:
					mavlink_command_ack_t command_ack;
					mavlink_msg_command_ack_decode(&msg, &command_ack);
					print_command_ack(command_ack);
					break;
                case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
                    mavlink_param_request_read_t param_request_read;
                    mavlink_msg_param_request_read_decode(&msg, &param_request_read);
                    print_param_request_read(param_request_read);
                    break;
                case MAVLINK_MSG_ID_REQUEST_DATA_STREAM:
                    mavlink_request_data_stream_t request_data_stream;
                    mavlink_msg_request_data_stream_decode(&msg, &request_data_stream);
                    print_request_data_stream(request_data_stream);
                    break;
                case MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN:
                    mavlink_gps_global_origin_t gps_global_origin;
                    mavlink_msg_gps_global_origin_decode(&msg, &gps_global_origin);
                    // Print the GPS_GLOBAL_ORIGIN message
                    print_gps_global_origin(gps_global_origin);
                    break;
                case MAVLINK_MSG_ID_HOME_POSITION:
                    mavlink_home_position_t home_position;
                    mavlink_msg_home_position_decode(&msg, &home_position);
                    // Print the HOME_POSITION message
                    print_home_position(home_position);
                    break;
                case MAVLINK_MSG_ID_STATUSTEXT:
                    mavlink_statustext_t statustext;
                    mavlink_msg_statustext_decode(&msg, &statustext);
                    //print_statustext(statustext) 
                    break;
                case MAVLINK_MSG_ID_PARAM_VALUE:
                    mavlink_param_value_t param_value;
                    mavlink_msg_param_value_decode(&msg, &param_value);
                    print_param_value(param_value);
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

