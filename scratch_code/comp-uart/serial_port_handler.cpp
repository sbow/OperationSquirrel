#include "serial_port_handler.h"

#define SERIAL_PORT "/dev/ttyTHS1"
#define BAUD_RATE B115200

int serial_port = 0;

void open_serial_port(void)
{
    // Open thea serial port for reading and writing
    serial_port = open(SERIAL_PORT, O_RDWR);
    if (serial_port < 0) 
    {
        fprintf(stderr,"Error opening serial port\n");
    }
}

void configure_serial_port(void)
{
    // Configure the serial port
    struct termios serial_config;
    tcgetattr(serial_port, &serial_config);
    serial_config.c_cflag = BAUD_RATE | CS8 | CLOCAL | CREAD;
    serial_config.c_iflag = IGNPAR;
    serial_config.c_oflag = 0;
    serial_config.c_lflag = 0;
    tcflush(serial_port, TCIFLUSH);
    tcsetattr(serial_port, TCSANOW, &serial_config);
}

void write_msg_request(uint8_t* buffer, uint16_t len)
{
    // Write to serial port
    uint16_t n = write(serial_port, buffer, len);

    if (MAVLINK_MAX_PACKET_LEN < len)
    {
        fprintf(stderr,"Buffer too large\n");
    }

    if (n < 0) 
    {
        fprintf(stderr,"Error writing to serial port\n");
    }

    clear_buffer(buffer, len);
}

uint8_t read_serial_port(void) 
{
    // Read a byte from the serial port
    uint8_t byte;
    if (read(serial_port, &byte, 1) == -1) 
    {
        fprintf(stderr,"Error reading from serial port\n");
    }

    return byte;
}

void offset_buffer(uint8_t* buffer, uint16_t &len, mavlink_message_t &msg)
{
    len = len + mavlink_msg_to_send_buffer(&buffer[len], &msg);
}

void clear_buffer(uint8_t* buffer, uint16_t len)
{
    memset(buffer, 0, len);
}

void close_serial_port(void)
{
    // Close the serial port
    close(serial_port);
}