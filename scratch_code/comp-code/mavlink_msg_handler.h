#ifndef MAVLINK_MSG_HANDLER_H
#define MAVLINK_MSG_HANDLER_H

#include "standard_libs.h"
#include "mavlink_print_info.h"
#include "serial_port_handler.h"

extern const uint8_t SENDER_SYS_ID;
extern const uint8_t SENDER_COMP_ID;
extern const uint8_t TARGET_SYS_ID;
extern const uint8_t TARGET_COMP_ID;
extern const int32_t MESSAGE_INTERVAL;

extern int32_t lat;
extern int32_t lon;
extern int32_t alt;
extern int32_t relative_alt;
extern int16_t vx;
extern int16_t vy;
extern int16_t vz;
extern uint16_t hdg;
extern float roll;
extern float pitch;
extern float yaw;
extern float rollspeed;
extern float pitchspeed;
extern float yawspeed;
extern int16_t xacc;
extern int16_t yacc;
extern int16_t zacc;
extern int16_t xgyro;
extern int16_t ygyro;
extern int16_t zgyro;
extern int16_t xmag;
extern int16_t ymag;
extern int16_t zmag;

void set_message_rates(void);
void request_messages(void);
void parse_serial_data(void);

#endif // MAVLINK_MSG_HANDLER_H