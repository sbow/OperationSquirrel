#include "handle_serial_port.h"

#define SIM_IP "127.0.0.1" // IP address of SITL simulation
#define SIM_PORT 5762      // Port number used by SITL simulation
struct sockaddr_in sim_addr;

int sock;

void open_socket(void)
{
    // Create a socket for the TCP connection
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        fprintf(stderr,"Error creating socket\n");
    }
}

void configure_socket(void)
{
    // Configure the address for the TCP connection
    sim_addr.sin_family = AF_INET;
    sim_addr.sin_addr.s_addr = inet_addr(SIM_IP);
    sim_addr.sin_port = htons(SIM_PORT);
}

void connect_to_sitl(void)
{
    // Connect to the SITL simulation
    if (connect(sock, (struct sockaddr *)&sim_addr, sizeof(sim_addr)) < 0)
    {
        fprintf(stderr,"Error connecting to sitl\n");
    }

    // Set the socket to non-blocking mode
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

void write_msg_request(uint8_t* buffer, uint16_t len)
{
    // Write to serial port
    uint16_t n = sendto(sock, buffer, len, 0, (struct sockaddr*)&sim_addr, sizeof(sim_addr));

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
    ssize_t n = recv(sock, &byte, sizeof(byte), 0);
    if (n < 0) 
    {
        //fprintf(stderr, "Error reading from port\n");
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
    close(sock);
}
/*
// Set the timeout to 5 seconds (5000 milliseconds)
struct timeval timeout;
timeout.tv_sec = 5;
timeout.tv_usec = 0;
setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
*/