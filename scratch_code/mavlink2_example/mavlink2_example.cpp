#include <iostream>
#include <mavlink.h>
#include <common.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define SERIAL_PORT "/dev/ttyTHS1"
#define BAUD_RATE B921600

// Function prototypes
void print_heartbeat(mavlink_heartbeat_t heartbeat);
void print_sys_status(mavlink_sys_status_t sys_status);
void print_gps_raw_int(mavlink_gps_raw_int_t gps_raw_int);
void print_attitude(mavlink_attitude_t attitude);
void print_global_position_int(mavlink_global_position_int_t global_pos_int);

// Function definitions
void print_heartbeat(mavlink_heartbeat_t heartbeat) {
    printf("Heartbeat:\n");
    printf("\tType: %d\n", heartbeat.type);
    printf("\tAutopilot: %d\n", heartbeat.autopilot);
    printf("\tBase mode: %d\n", heartbeat.base_mode);
    printf("\tCustom mode: %d\n", heartbeat.custom_mode);
    printf("\tSystem status: %d\n", heartbeat.system_status);
    printf("\tMavlink version: %d\n", heartbeat.mavlink_version);
}

void print_sys_status(mavlink_sys_status_t sys_status) {
    printf("System status:\n");
    printf("\tOnboard control sensors present: %u\n", sys_status.onboard_control_sensors_present);
    printf("\tOnboard control sensors enabled: %u\n", sys_status.onboard_control_sensors_enabled);
    printf("\tOnboard control sensors health: %u\n", sys_status.onboard_control_sensors_health);
    printf("\tLoad: %u%%\n", sys_status.load);
    printf("\tVoltage battery: %u mV\n", sys_status.voltage_battery);
    printf("\tCurrent battery: %d mA\n", sys_status.current_battery);
    printf("\tBattery remaining: %d%%\n", sys_status.battery_remaining);
    printf("\tDrop rate communication: %u%%\n", sys_status.drop_rate_comm);
    printf("\tErrors comm: %u\n", sys_status.errors_comm);
    printf("\tErrors count 1: %u\n", sys_status.errors_count1);
    printf("\tErrors count 2: %u\n", sys_status.errors_count2);
    printf("\tErrors count 3: %u\n", sys_status.errors_count3);
    printf("\tErrors count 4: %u\n", sys_status.errors_count4);
}

void print_gps_raw_int(mavlink_gps_raw_int_t gps_raw_int) {
    printf("GPS raw data:\n");
    printf("\tTimestamp: %lu ms\n", gps_raw_int.time_usec);
    printf("\tFix type: %d\n", gps_raw_int.fix_type);
    printf("\tLatitude: %d degrees (1e-7)\n", gps_raw_int.lat);
    printf("\tLongitude: %d degrees (1e-7)\n", gps_raw_int.lon);
    printf("\tAltitude: %d meters\n", gps_raw_int.alt);
    printf("\tGround speed: %d m/s\n", gps_raw_int.vel);
    printf("\tCourse over ground: %d degrees\n", gps_raw_int.cog);
}

void print_attitude(mavlink_attitude_t attitude) {
    printf("Attitude:\n");
    printf("\tRoll: %.4f radians\n", attitude.roll);
    printf("\tPitch: %.4f radians\n", attitude.pitch);
    printf("\tYaw: %.4f radians\n", attitude.yaw);
    printf("\tRoll speed: %.4f rad/s\n", attitude.rollspeed);
    printf("\tPitch speed: %.4f rad/s\n", attitude.pitchspeed);
    printf("\tYaw speed: %.4f rad/s\n", attitude.yawspeed);
}

void print_global_position_int(mavlink_global_position_int_t global_pos_int) {
    printf("Global position:\n");
    printf("\tLatitude: %d degrees (1e-7)\n", global_pos_int.lat);
    printf("\tLongitude: %d degrees (1e-7)\n", global_pos_int.lon);
    printf("\tAltitude: %d\n", global_pos_int.alt);
}

void print_raw_imu(mavlink_raw_imu_t raw_imu) {
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

void print_command_ack(mavlink_command_ack_t command_ack) {
    printf("Command ACK received:\n");
    printf("\tCommand: %u\n", command_ack.command);
    printf("\tResult: %u\n", command_ack.result);
}


int main() {
    // Open the serial port for reading and writing
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
	
    // Subscribe to HEARTBEAT message
    mavlink_msg_heartbeat_pack(0, MAV_COMP_ID_ALL, &msg, MAV_TYPE_ONBOARD_CONTROLLER, MAV_AUTOPILOT_INVALID, 0, 0, MAV_STATE_STANDBY);

	// Request all message streams at a rate of X Hz
	// system_id, component_id, msg, target_system. target_component, req_stream_id, req_message_rate, start_stop
	// mavlink_msg_request_data_stream_pack(0, MAV_COMP_ID_ALL, &msg, 0, 0, MAV_DATA_STREAM_ALL, 50, 1);

	// Set the message rate for MAVLINK message to X Hz
	// system_id, component_id, msg pointer, target_system, target_component, command, 0, param1, param2, param3, param4, param5, param6, param7
	mavlink_msg_command_long_pack(0, MAV_COMP_ID_ALL, &msg, 0, 0, MAV_CMD_SET_MESSAGE_INTERVAL, 0, MAV_DATA_STREAM_ALL, 100, 0, 0, 0, 0, 0);
	
    // Set the flight mode
	mavlink_msg_command_long_pack(0, MAV_COMP_ID_ALL, &msg, 0, 0, MAV_CMD_DO_SET_MODE, 0, MAV_MODE_GUIDED_ARMED, 0, 0, 0, 0, 0, 0);
    
    // Command to ARM the drone
	mavlink_msg_command_long_pack(0, MAV_COMP_ID_ALL, &msg, 0, 0, MAV_CMD_COMPONENT_ARM_DISARM, 0, 1, 1, 0, 0, 0, 0, 0);
	
    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

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
                    print_heartbeat(heartbeat);
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
					print_raw_imu(msg_raw_imu);
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
	        default:
		    	std::cout << "Received message with ID " << (int)msg.msgid << std::endl;
            }
        }
    }

    // Close the serial port
    close(serial_port);

    return 0;
}

