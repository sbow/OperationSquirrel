#define _POSIX_C_SOURCE 200809L // enable certain POSIX-specific functionality

#include <mavlink.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void open_socket(void);
void configure_socket(void);
void write_msg_request(uint8_t* buffer, uint16_t len);
uint8_t read_serial_port(void);
void offset_buffer(uint8_t* buffer, uint16_t &len, mavlink_message_t &msg);
void clear_buffer(uint8_t* buffer, uint16_t len);
void close_serial_port(void);
void connect_to_sitl(void);