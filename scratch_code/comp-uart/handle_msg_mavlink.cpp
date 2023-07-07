#include "handle_msg_mavlink.h"

const uint8_t SENDER_SYS_ID = 0;
const uint8_t SENDER_COMP_ID = 0;
const uint8_t TARGET_SYS_ID = 1;
const uint8_t TARGET_COMP_ID = 1;
const int32_t MESSAGE_INTERVAL = 10000; // microseconds

void set_message_rates(void)
{
    uint16_t len = 0; // length of buffer
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN]; // define length of buffer
    mavlink_message_t msg; // initialize the Mavlink message buffer

    // Subscribe to HEARTBEAT message
    mavlink_msg_heartbeat_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, MAV_TYPE_ONBOARD_CONTROLLER, MAV_AUTOPILOT_INVALID, 0, 0, MAV_STATE_STANDBY);
    offset_buffer(buffer, len, msg);

    // Request all message streams at a rate of X Hz (not supported but should still work)
    // system_id, component_id, msg, target_system. target_component, req_stream_id, req_message_rate, start_stop
    // mavlink_msg_request_data_stream_pack(0, MAV_COMP_ID_ALL, &msg, 0, 0, MAV_DATA_STREAM_ALL, 50, 1);

    // Set the message rate for MAVLINK messages to X microseconds
    // system_id, component_id, msg pointer, target_system, target_component, command, 0, param1, param2, param3, param4, param5, param6, param7
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, MAV_CMD_SET_MESSAGE_INTERVAL, 0, MAVLINK_MSG_ID_RAW_IMU, MESSAGE_INTERVAL, 0, 0, 0, 0, 0);
    offset_buffer(buffer, len, msg);

    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, MAV_CMD_SET_MESSAGE_INTERVAL, 0, MAVLINK_MSG_ID_ATTITUDE, MESSAGE_INTERVAL, 0, 0, 0, 0, 0);
    offset_buffer(buffer, len, msg);

    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, MAV_CMD_SET_MESSAGE_INTERVAL, 0, MAVLINK_MSG_ID_GPS_RAW_INT, MESSAGE_INTERVAL, 0, 0, 0, 0, 0);
    offset_buffer(buffer, len, msg);

    // Send request to flight controller
    write_msg_request(buffer, len);
}

void request_messages(void)
{
    uint16_t len = 0; // length of buffer
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN]; // define length of buffer
    mavlink_message_t msg; // initialize the Mavlink message buffer

    // Request specific MAVLINK messages
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, MAV_CMD_REQUEST_MESSAGE, 0, MAVLINK_MSG_ID_RAW_IMU, 0, 0, 0, 0, 0, 0);
    offset_buffer(buffer, len, msg);

    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, MAV_CMD_REQUEST_MESSAGE, 0, MAVLINK_MSG_ID_ATTITUDE, 0, 0, 0, 0, 0, 0);
    offset_buffer(buffer, len, msg);
    
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, MAV_CMD_REQUEST_MESSAGE, 0, MAVLINK_MSG_ID_GPS_RAW_INT, 0, 0, 0, 0, 0, 0);
    offset_buffer(buffer, len, msg);

    // Send request to flight controller
    write_msg_request(buffer, len);
}

void get_messages(void)
{
    uint16_t len = 0; // length of buffer
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN]; // define length of buffer
    mavlink_message_t msg; // initialize the Mavlink message buffer
    mavlink_status_t status = {}; // Initialize the Mavlink status

    uint8_t byte;
    
    byte = read_serial_port();

    // Parse the byte and check if a message has been received
    if (mavlink_parse_char(MAVLINK_COMM_0, byte, &msg, &status)) 
    {
        // Handle the message based on its type
        // switch case
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
                latitude = msg_gps_raw_int.lat;
                longitude = msg_gps_raw_int.lon;
                altitude = msg_gps_raw_int.alt;
                printf("Lat: %u\n", latitude);
                printf("Lon: %u\n", longitude);
                printf("Alt: %u\n", altitude);
                //print_gps_raw_int(msg_gps_raw_int);
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
                printf("Received message with ID: %d\n", (int)msg.msgid);
        }
    }
}