#include <iostream>
#include <mavlink.h>
#include <common.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define SERIAL_PORT "/dev/ttyTHS1"
#define BAUD_RATE B115200

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
    printf("\tCommand: ");
    switch (command_ack.command)
    {
        case MAV_CMD_NAV_WAYPOINT:
            printf("MAV_CMD_NAV_WAYPOINT\n");
            break;
        case MAV_CMD_NAV_LOITER_UNLIM:
            printf("MAV_CMD_NAV_LOITER_UNLIM\n");
            break;
        case MAV_CMD_NAV_LOITER_TURNS:
            printf("MAV_CMD_NAV_LOITER_TURNS\n");
            break;
        case MAV_CMD_NAV_LOITER_TIME:
            printf("MAV_CMD_NAV_LOITER_TIME\n");
            break;
        case MAV_CMD_NAV_RETURN_TO_LAUNCH:
            printf("MAV_CMD_NAV_RETURN_TO_LAUNCH\n");
            break;
        case MAV_CMD_NAV_LAND:
            printf("MAV_CMD_NAV_LAND\n");
            break;
        case MAV_CMD_NAV_TAKEOFF:
            printf("MAV_CMD_NAV_TAKEOFF\n");
            break;
        case MAV_CMD_NAV_LAND_LOCAL:
            printf("MAV_CMD_NAV_LAND_LOCAL\n");
            break;
        case MAV_CMD_NAV_TAKEOFF_LOCAL:
            printf("MAV_CMD_NAV_TAKEOFF_LOCAL\n");
            break;
        case MAV_CMD_NAV_FOLLOW:
            printf("MAV_CMD_NAV_FOLLOW\n");
            break;
        case MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT:
            printf("MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT\n");
            break;
        case MAV_CMD_NAV_LOITER_TO_ALT:
            printf("MAV_CMD_NAV_LOITER_TO_ALT\n");
            break;
        case MAV_CMD_DO_FOLLOW:
            printf("MAV_CMD_DO_FOLLOW\n");
            break;
        case MAV_CMD_DO_FOLLOW_REPOSITION:
            printf("MAV_CMD_DO_FOLLOW_REPOSITION\n");
            break;
        case MAV_CMD_DO_ORBIT:
            printf("MAV_CMD_DO_ORBIT\n");
            break;
        case MAV_CMD_NAV_ROI:
            printf("MAV_CMD_NAV_ROI\n");
            break;
        case MAV_CMD_NAV_PATHPLANNING:
            printf("MAV_CMD_NAV_PATHPLANNING\n");
            break;
        case MAV_CMD_NAV_SPLINE_WAYPOINT:
            printf("MAV_CMD_NAV_SPLINE_WAYPOINT\n");
            break;
        case MAV_CMD_NAV_VTOL_TAKEOFF:
            printf("MAV_CMD_NAV_VTOL_TAKEOFF\n");
            break;
        case MAV_CMD_NAV_VTOL_LAND:
            printf("MAV_CMD_NAV_VTOL_LAND\n");
            break;
        case MAV_CMD_NAV_GUIDED_ENABLE:
            printf("MAV_CMD_NAV_GUIDED_ENABLE\n");
            break;
        case MAV_CMD_NAV_DELAY:
            printf("MAV_CMD_NAV_DELAY\n");
            break;
        case MAV_CMD_NAV_PAYLOAD_PLACE:
            printf("MAV_CMD_NAV_PAYLOAD_PLACE\n");
            break;
        case MAV_CMD_NAV_LAST:
            printf("MAV_CMD_NAV_LAST\n");
            break;
        case MAV_CMD_CONDITION_DELAY:
            printf("MAV_CMD_CONDITION_DELAY\n");
            break;
        case MAV_CMD_CONDITION_CHANGE_ALT:
            printf("MAV_CMD_CONDITION_CHANGE_ALT\n");
            break;
        case MAV_CMD_CONDITION_DISTANCE:
            printf("MAV_CMD_CONDITION_DISTANCE\n");
            break;
        case MAV_CMD_CONDITION_YAW:
            printf("MAV_CMD_CONDITION_YAW\n");
            break;
        case MAV_CMD_CONDITION_LAST:
            printf("MAV_CMD_CONDITION_LAST\n");
            break;
        case MAV_CMD_DO_SET_MODE:
            printf("MAV_CMD_DO_SET_MODE\n");
            break;
        case MAV_CMD_DO_JUMP:
            printf("MAV_CMD_DO_JUMP\n");
            break;
        case MAV_CMD_DO_CHANGE_SPEED:
            printf("MAV_CMD_DO_CHANGE_SPEED\n");
            break;
        case MAV_CMD_DO_SET_HOME:
            printf("MAV_CMD_DO_SET_HOME\n");
            break;
        case MAV_CMD_DO_SET_PARAMETER:
            printf("MAV_CMD_DO_SET_PARAMETER\n");
            break;
        case MAV_CMD_DO_SET_RELAY:
            printf("MAV_CMD_DO_SET_RELAY\n");
            break;
        case MAV_CMD_DO_REPEAT_RELAY:
            printf("MAV_CMD_DO_REPEAT_RELAY\n");
            break;
        case MAV_CMD_DO_SET_SERVO:
            printf("MAV_CMD_DO_SET_SERVO\n");
            break;
        case MAV_CMD_DO_REPEAT_SERVO:
            printf("MAV_CMD_DO_REPEAT_SERVO\n");
            break;
        case MAV_CMD_DO_FLIGHTTERMINATION:
            printf("MAV_CMD_DO_FLIGHTTERMINATION\n");
            break;
        case MAV_CMD_DO_CHANGE_ALTITUDE:
            printf("MAV_CMD_DO_CHANGE_ALTITUDE\n");
            break;
        case MAV_CMD_DO_SET_ACTUATOR:
            printf("MAV_CMD_DO_SET_ACTUATOR\n");
            break;
        case MAV_CMD_DO_LAND_START:
            printf("MAV_CMD_DO_LAND_START\n");
            break;
        case MAV_CMD_DO_RALLY_LAND:
            printf("MAV_CMD_DO_RALLY_LAND\n");
            break;
        case MAV_CMD_DO_GO_AROUND:
            printf("MAV_CMD_DO_GO_AROUND\n");
            break;
        case MAV_CMD_DO_REPOSITION:
            printf("MAV_CMD_DO_REPOSITION\n");
            break;
        case MAV_CMD_DO_PAUSE_CONTINUE:
            printf("MAV_CMD_DO_PAUSE_CONTINUE\n");
            break;
        case MAV_CMD_DO_SET_REVERSE:
            printf("MAV_CMD_DO_SET_REVERSE\n");
            break;
        case MAV_CMD_DO_SET_ROI_LOCATION:
            printf("MAV_CMD_DO_SET_ROI_LOCATION\n");
            break;
        case MAV_CMD_DO_SET_ROI_WPNEXT_OFFSET:
            printf("MAV_CMD_DO_SET_ROI_WPNEXT_OFFSET\n");
            break;
        case MAV_CMD_DO_SET_ROI_NONE:
            printf("MAV_CMD_DO_SET_ROI_NONE\n");
            break;
        case MAV_CMD_DO_SET_ROI_SYSID:
            printf("MAV_CMD_DO_SET_ROI_SYSID\n");
            break;
        case MAV_CMD_DO_CONTROL_VIDEO:
            printf("MAV_CMD_DO_CONTROL_VIDEO\n");
            break;
        case MAV_CMD_DO_SET_ROI:
            printf("MAV_CMD_DO_SET_ROI\n");
            break;
        case MAV_CMD_DO_DIGICAM_CONFIGURE:
            printf("MAV_CMD_DO_DIGICAM_CONFIGURE\n");
            break;
        case MAV_CMD_DO_DIGICAM_CONTROL:
            printf("MAV_CMD_DO_DIGICAM_CONTROL\n");
            break;
        case MAV_CMD_DO_MOUNT_CONFIGURE:
            printf("MAV_CMD_DO_MOUNT_CONFIGURE\n");
            break;
        case MAV_CMD_DO_MOUNT_CONTROL:
            printf("MAV_CMD_DO_MOUNT_CONTROL\n");
            break;
        case MAV_CMD_DO_SET_CAM_TRIGG_DIST:
            printf("MAV_CMD_DO_SET_CAM_TRIGG_DIST\n");
            break;
        case MAV_CMD_DO_FENCE_ENABLE:
            printf("MAV_CMD_DO_FENCE_ENABLE\n");
            break;
        case MAV_CMD_DO_PARACHUTE:
            printf("MAV_CMD_DO_PARACHUTE\n");
            break;
        case MAV_CMD_DO_MOTOR_TEST:
            printf("MAV_CMD_DO_MOTOR_TEST\n");
            break;
        case MAV_CMD_DO_INVERTED_FLIGHT:
            printf("MAV_CMD_DO_INVERTED_FLIGHT\n");
            break;
        case MAV_CMD_DO_GRIPPER:
            printf("MAV_CMD_DO_GRIPPER\n");
            break;
        case MAV_CMD_DO_AUTOTUNE_ENABLE:
            printf("MAV_CMD_DO_AUTOTUNE_ENABLE\n");
            break;
        case MAV_CMD_NAV_SET_YAW_SPEED:
            printf("MAV_CMD_NAV_SET_YAW_SPEED\n");
            break;
        case MAV_CMD_DO_SET_CAM_TRIGG_INTERVAL:
            printf("MAV_CMD_DO_SET_CAM_TRIGG_INTERVAL\n");
            break;
        case MAV_CMD_DO_MOUNT_CONTROL_QUAT:
            printf("MAV_CMD_DO_MOUNT_CONTROL_QUAT\n");
            break;
        case MAV_CMD_DO_GUIDED_MASTER:
            printf("MAV_CMD_DO_GUIDED_MASTER\n");
            break;
        case MAV_CMD_DO_GUIDED_LIMITS:
            printf("MAV_CMD_DO_GUIDED_LIMITS\n");
            break;
        case MAV_CMD_DO_ENGINE_CONTROL:
            printf("MAV_CMD_DO_ENGINE_CONTROL\n");
            break;
        case MAV_CMD_DO_SET_MISSION_CURRENT:
            printf("MAV_CMD_DO_SET_MISSION_CURRENT\n");
            break;
        case MAV_CMD_DO_LAST:
            printf("MAV_CMD_DO_LAST\n");
            break;
        case MAV_CMD_PREFLIGHT_CALIBRATION:
            printf("MAV_CMD_PREFLIGHT_CALIBRATION\n");
            break;
        case MAV_CMD_PREFLIGHT_SET_SENSOR_OFFSETS:
            printf("MAV_CMD_PREFLIGHT_SET_SENSOR_OFFSETS\n");
            break;
        case MAV_CMD_PREFLIGHT_UAVCAN:
            printf("MAV_CMD_PREFLIGHT_UAVCAN\n");
            break;
        case MAV_CMD_PREFLIGHT_STORAGE:
            printf("MAV_CMD_PREFLIGHT_STORAGE\n");
            break;
        case MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN:
            printf("MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN\n");
            break;
        case MAV_CMD_OVERRIDE_GOTO:
            printf("MAV_CMD_OVERRIDE_GOTO\n");
            break;
        case MAV_CMD_OBLIQUE_SURVEY:
            printf("MAV_CMD_OBLIQUE_SURVEY\n");
            break;
        case MAV_CMD_MISSION_START:
            printf("MAV_CMD_MISSION_START\n");
            break;
        case MAV_CMD_ACTUATOR_TEST:
            printf("MAV_CMD_ACTUATOR_TEST\n");
            break;
        case MAV_CMD_CONFIGURE_ACTUATOR:
            printf("MAV_CMD_CONFIGURE_ACTUATOR\n");
            break;
        case MAV_CMD_COMPONENT_ARM_DISARM:
            printf("MAV_CMD_COMPONENT_ARM_DISARM\n");
            break;
        case MAV_CMD_RUN_PREARM_CHECKS:
            printf("MAV_CMD_RUN_PREARM_CHECKS\n");
            break;
        case MAV_CMD_ILLUMINATOR_ON_OFF:
            printf("MAV_CMD_ILLUMINATOR_ON_OFF\n");
            break;
        case MAV_CMD_GET_HOME_POSITION:
            printf("MAV_CMD_GET_HOME_POSITION\n");
            break;
        case MAV_CMD_INJECT_FAILURE:
            printf("MAV_CMD_INJECT_FAILURE\n");
            break;
        case MAV_CMD_START_RX_PAIR:
            printf("MAV_CMD_START_RX_PAIR\n");
            break;
        case MAV_CMD_GET_MESSAGE_INTERVAL:
            printf("MAV_CMD_GET_MESSAGE_INTERVAL\n");
            break;
        case MAV_CMD_SET_MESSAGE_INTERVAL:
            printf("MAV_CMD_SET_MESSAGE_INTERVAL\n");
            break;
        case MAV_CMD_REQUEST_AUTOPILOT_CAPABILITIES:
            printf("MAV_CMD_REQUEST_AUTOPILOT_CAPABILITIES\n");
            break;
        case MAV_CMD_SET_CAMERA_MODE:
            printf("MAV_CMD_SET_CAMERA_MODE\n");
            break;
        default:
            printf("Unknown command\n");
            break;
    }
    printf("\tResult: ");
    switch (command_ack.result)
    {
        case 0:
            printf("MAV_RESULT_ACCEPTED\n");
            break;
        case 1:
            printf("MAV_RESULT_TEMPORARILY_REJECTED\n");
            break;
        case 2:
            printf("MAV_RESULT_DENIED\n");
            break;
        case 3:
            printf("MAV_RESULT_UNSUPPORTED\n");
            break;
        case 4:
            printf("MAV_RESULT_FAILED\n");
            break;
        case 5:
            printf("MAV_RESULT_IN_PROGRESS\n");
            break;
        case 6:
            printf("MAV_RESULT_CANCELLED\n");
            break;
        case 7:
            printf("MAV_RESULT_COMMAND_LONG_ONLY\n");
            break;
        case 8:
            printf("MAV_RESULT_COMMAND_INT_ONLY\n");
            break;
        case 9:
            printf("MAV_RESULT_COMMAND_COMMAND_UNSUPPORTED_MAV_FRAME\n");
            break;
        default:
            printf("We don't know\n");
    }
}
    

void print_param_request_read(const mavlink_param_request_read_t& param_request_read) {
    printf("Param Request Read:\n");
    printf("\tTarget System: %u\n", param_request_read.target_system);
    printf("\tTarget Component: %u\n", param_request_read.target_component);
    printf("\tParameter ID: %s\n", param_request_read.param_id);
}

void print_request_data_stream(const mavlink_request_data_stream_t& request_data_stream) {
    printf("REQUEST_DATA_STREAM message:\n");
    printf("\tTarget System: %u\n", request_data_stream.target_system);
    printf("\tTarget Component: %u\n", request_data_stream.target_component);
    printf("\tStream ID: %u\n", request_data_stream.req_stream_id);
    printf("\tMessage Rate: %u\n", request_data_stream.req_message_rate);
    printf("\tStart/Stop: %u\n", request_data_stream.start_stop);
}

void print_gps_global_origin(const mavlink_gps_global_origin_t& gps_global_origin) 
{
    printf("GPS_GLOBAL_ORIGIN message:\n");
    printf("\tLatitude: %f\n", (double)gps_global_origin.latitude);
    printf("\tLongitude: %f\n", (double)gps_global_origin.longitude);
    printf("\tAltitude: %f\n", (double)gps_global_origin.altitude);
}

void print_home_position(const mavlink_home_position_t& home_position) 
{
    printf("HOME_POSITION message:\n");
    printf("\tLatitude: %f\n", (double)home_position.latitude);
    printf("\tLongitude: %f\n", (double)home_position.longitude);
    printf("\tAltitude: %f\n", (double)home_position.altitude);
}

void print_statustext(const mavlink_statustext_t& statustext) 
{
    printf("STATUSTEXT message:\n");
    printf("\tSeverity: %u\n", statustext.severity);
    printf("\tText: %s\n", statustext.text);
}

// Function to print PARAM_VALUE message
void printParamValueMessage(const mavlink_param_value_t& paramValue) {
    printf("Parameter Name: %s\n", paramValue.param_id);
    printf("\tParameter Value: %.4f\n", paramValue.param_value);
    printf("\tParameter Type: %d\n", paramValue.param_type);
    printf("\tParameter Count: %d\n", paramValue.param_count);
    printf("\tParameter Index: %d\n", paramValue.param_index);
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
                    // Extract and print relevant fields
                    break;
                case MAVLINK_MSG_ID_HOME_POSITION:
                    mavlink_home_position_t home_position;
                    mavlink_msg_home_position_decode(&msg, &home_position);
                    // Print the HOME_POSITION message
                    // Extract and print relevant fields
                    break;
                case MAVLINK_MSG_ID_STATUSTEXT:
                    mavlink_statustext_t statustext;
                    mavlink_msg_statustext_decode(&msg, &statustext);
                    // Print the STATUSTEXT message
                    // Extract and print relevant fields
                    break;
                case MAVLINK_MSG_ID_PARAM_VALUE:
                    mavlink_param_value_t paramValue;
                    mavlink_msg_param_value_decode(&msg, &paramValue);
                    printParamValueMessage(paramValue);
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

