#ifndef MAVLINK_COMMAND_HANDLER_H
#define MAVLINK_COMMAND_HANDLER_H

#include "standard_libs.h"
#include "serial_port_handler.h"

extern const uint8_t SENDER_SYS_ID;
extern const uint8_t SENDER_COMP_ID;
extern const uint8_t TARGET_SYS_ID;
extern const uint8_t TARGET_COMP_ID;
extern const int32_t MESSAGE_INTERVAL; // microseconds

void startup_sequence(void);
void landing_sequence(void);
void go_to_waypoint(int32_t lat, int32_t lon, float alt);

#endif // MAVLINK_COMMAND_HANDLER_H