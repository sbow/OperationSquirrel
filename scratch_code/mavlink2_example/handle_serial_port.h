#include <mavlink.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

void open_serial_port(void);
void configure_serial_port(void);
void write_msg_request(uint8_t* buffer, uint16_t len);
uint8_t read_serial_port(void);
void offset_buffer(uint8_t* buffer, uint16_t &len, mavlink_message_t &msg);
void clear_buffer(uint8_t* buffer, uint16_t len);
void close_serial_port(void);