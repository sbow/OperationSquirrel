#include "mavlink_command_handler.h"

// MAV_CMD_DO_MOTOR_TEST instance, MOTOR_TEST_THROTTLE_TYPE, throttle, timeout, motor count, test order, empty
// MAV_CMD_DO_FENCE_ENABLE enable, empty, etc
// MAV_CMD_DO_SET_ROI, ROI mode, WP index, ROI index, empty, MAV_ROI__WPNEXT pitch, MAV_ROI__WPNEXT roll, MAV_ROI__WPNEXT yaw
// MAV_CMD_DO_SET_PARAMETER param number, value
// MAV_CMD_DO_SET_SERVO instance (servo #),PWM value
// MAV_CMD_DO_SET_HOME 1 use current 0 use specified, empty, empty, yaw (NAN for default), lat, lon, altitude
// MAV_CMD_DO_CHANGE_SPEED speed type, speed, throttle. reserved, etc (all set 0)
// MAV_CMD_NAV_GUIDED_ENABLE enable (> 05f on), empty, etc

const uint8_t SENDER_SYS_ID = 0;
const uint8_t SENDER_COMP_ID = 0;
const uint8_t TARGET_SYS_ID = 1;
const uint8_t TARGET_COMP_ID = 1;
const int32_t MESSAGE_INTERVAL = 12.5e3; // microseconds

void startup_sequence(void)
{
    uint16_t len = 0; // length of buffer
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN]; // define length of buffer
    mavlink_message_t msg; // initialize the Mavlink message buffer

    // Set flight mode to guided
    // enable or disable custom mode (including guided), mode # (found in mode.h), custom submode, empty, etc
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, MAV_CMD_DO_SET_MODE, 0, MAV_MODE_FLAG_CUSTOM_MODE_ENABLED, 4, 0, 0, 0, 0, 0);
    offset_buffer(buffer, len, msg);
    
    // ARM the drone
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, MAV_CMD_COMPONENT_ARM_DISARM, 0, 1, 1, 0, 0, 0, 0, 0);
    offset_buffer(buffer, len, msg);

    // Takeoff
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, MAV_CMD_NAV_TAKEOFF, 0, 0, 0, 0, 0, 0, 0, 15.0);
    offset_buffer(buffer, len, msg);

    // Send commands to flight controller
    write_msg_request(buffer, len);
}

void landing_sequence(void)
{
    uint16_t len = 0; // length of buffer
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN]; // define length of buffer
    mavlink_message_t msg; // initialize the Mavlink message buffer

    // Set flight mode to RTL
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, MAV_CMD_DO_SET_MODE, 0, MAV_MODE_FLAG_CUSTOM_MODE_ENABLED, 6, 0, 0, 0, 0, 0);
    offset_buffer(buffer, len, msg);

    write_msg_request(buffer, len);
}

void go_to_waypoint(int32_t lat, int32_t lon, float alt)
{
    uint16_t len = 0; // length of buffer
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN]; // define length of buffer
    mavlink_message_t msg; // initialize the Mavlink message buffer

    // Go to GPS waypoint
    mavlink_msg_set_position_target_global_int_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, 0, TARGET_SYS_ID, TARGET_COMP_ID, MAV_FRAME_GLOBAL_RELATIVE_ALT_INT, (uint16_t)0b111111111000, lat, lon, alt, 0, 0, 0, 0, 0, 0, 0, 0);
    //mavlink_msg_command_int_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, TARGET_SYS_ID, TARGET_COMP_ID, MAV_CMD_DO_SET_MODE, 0, MAV_MODE_FLAG_CUSTOM_MODE_ENABLED, 6, 0, 0, -35.3671 * 1e7, 149.1649 * 1e7, 0);

    offset_buffer(buffer, len, msg);

    write_msg_request(buffer, len);
}