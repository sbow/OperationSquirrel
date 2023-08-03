#ifndef MAVLINK_MSG_HANDLER_H
#define MAVLINK_MSG_HANDLER_H

#include "standard_libs.h"
#include "mavlink_print_info.h"
#include "serial_port_handler.h"

extern const uint8_t SENDER_SYS_ID;
extern const uint8_t SENDER_COMP_ID;
extern const uint8_t TARGET_SYS_ID;
extern const uint8_t TARGET_COMP_ID;
extern const int32_t MESSAGE_INTERVAL; // microseconds

extern int32_t altitude;
extern int32_t latitude;
extern int32_t longitude;

void set_message_rates(void);
void request_messages(void);
void get_messages(void);

#endif // MAVLINK_MSG_HANDLER_H