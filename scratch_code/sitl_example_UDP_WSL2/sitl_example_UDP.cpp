#define _POSIX_C_SOURCE 200809L // enable certain POSIX-specific functionality
#include <iostream>
#include <mavlink.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>

#define SIM_IP "127.0.0.1" // IP address of SITL simulation
#define SIM_PORT 14555     // Port number used by SITL simulation

// Function prototypes
void print_heartbeat(mavlink_heartbeat_t heartbeat);
void print_sys_status(mavlink_sys_status_t sys_status);
void print_gps_raw_int(mavlink_gps_raw_int_t gps_raw_int);
void print_attitude(mavlink_attitude_t attitude);
void print_global_position_int(mavlink_global_position_int_t global_pos_int);
void print_request_data_stream(mavlink_request_data_stream_t request);

// Function definitions
void print_heartbeat(mavlink_heartbeat_t heartbeat)
{
    printf("Heartbeat:\n");
    printf("\tType: %d\n", heartbeat.type);
    printf("\tAutopilot: %d\n", heartbeat.autopilot);
    printf("\tBase mode: %d\n", heartbeat.base_mode);
    printf("\tCustom mode: %d\n", heartbeat.custom_mode);
    printf("\tSystem status: %d\n", heartbeat.system_status);
    printf("\tMavlink version: %d\n", heartbeat.mavlink_version);
}

void print_command_ack(mavlink_command_ack_t command_ack) 
{
    printf("Command ACK received:\n");
    printf("\tCommand: %u\n", command_ack.command);
    printf("\tResult: %u\n", command_ack.result);
}

void print_request_data_stream(mavlink_request_data_stream_t request)
{
    printf("Request Data Stream:\n");
    printf("\tTarget System ID: %d\n", request.target_system);
    printf("\tTarget Component ID: %d\n", request.target_component);
    printf("\tRequest Stream ID: %d\n", request.req_stream_id);
    printf("\tRequested Message Rate: %d\n", request.req_message_rate);
    printf("\tStart/Stop Stream: %d\n", request.start_stop);
}

int main()
{
    // Create a socket for the UDP connection
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Configure the address for the UDP connection
    struct sockaddr_in sim_addr;
    sim_addr.sin_family = AF_INET;
    sim_addr.sin_addr.s_addr = inet_addr(SIM_IP);
    sim_addr.sin_port = htons(SIM_PORT);

    // Bind the socket to a local address
    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_port = htons(0);

    if (bind(sock, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0)
    {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    // Set the socket to non-blocking mode
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);

    // Initialize the Mavlink message buffer
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    // Initialize the Mavlink status
    mavlink_status_t status = {};

    /*** scratch code
    // Subscribe to HEARTBEAT message
    // sysid, compid, msg pointer, type, autopilot, base_mode, custom_mode, system_status
    //mavlink_msg_heartbeat_pack(0, MAV_COMP_ID_ALL, &msg, 0, 0, 0, 0, MAV_STATE_STANDBY);
    
    // Request MAVLINK messages at X Hz
    //mavlink_msg_command_long_pack(0, MAV_COMP_ID_ALL, &msg, 0, 0, MAV_CMD_REQUEST_MESSAGE, 0, MAVLINK_MSG_ID_RAW_IMU, 0, 0, 0, 0, 0, 0);
    ***/

    // define system and component ID for companion computer
    uint8_t SENDER_SYS_ID = 1;
    uint8_t SENDER_COMP_ID = 1;
    
    // Send a heartbeat message to the SITL simulation
    mavlink_msg_heartbeat_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, MAV_TYPE_ONBOARD_CONTROLLER, MAV_AUTOPILOT_INVALID, 0, 0, MAV_STATE_STANDBY);
    
    uint16_t len = mavlink_msg_to_send_buffer(&buffer[0], &msg);
    /*
    // Set the message rate for MAVLINK message to X Hz
    // system_id, component_id, msg pointer, target_system, target_component, command, 0, param1, param2, param3, param4, param5, param6, param7
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, 1, 1, MAV_CMD_SET_MESSAGE_INTERVAL, 0, MAVLINK_MSG_ID_RAW_IMU, 10000, 0, 0, 0, 0, 0);

    len = len + mavlink_msg_to_send_buffer(&buffer[len], &msg);

    // Request MAVLINK messages at X Hz
    mavlink_msg_command_long_pack(SENDER_SYS_ID, SENDER_COMP_ID, &msg, 1, 1, MAV_CMD_REQUEST_MESSAGE, 0, MAVLINK_MSG_ID_RAW_IMU, 0, 0, 0, 0, 0, 0);

    len = len + mavlink_msg_to_send_buffer(&buffer[len], &msg);
    */
    printf("\tbuffer: %d\n", buffer);
    if (sendto(sock, buffer, len, 0, (struct sockaddr*)&sim_addr, sizeof(sim_addr)) < 0)
    {
        std::cerr << "Error sending commands" << std::endl;
    }
    
    // Receive and handle Mavlink messages
    while (true) 
    {   
        /*
        // Send a heartbeat message to the SITL simulation
        mavlink_msg_heartbeat_pack(1, 0, &msg, MAV_TYPE_ONBOARD_CONTROLLER, MAV_AUTOPILOT_INVALID, 0, 0, MAV_STATE_STANDBY);
        
        uint16_t len = mavlink_msg_to_send_buffer(&buffer[0], &msg);
        if (sendto(sock, buffer, len, 0, (struct sockaddr*)&sim_addr, sizeof(sim_addr)) < 0) 
        {
            std::cerr << "Error sending commands" << std::endl;
        }*/

        // Receive MAVLink messages from the SITL simulation
        ssize_t n = recv(sock, buffer, sizeof(buffer), 0);
        if (n < 0) 
        {
            if (errno == EWOULDBLOCK) 
            {
                // No data available yet, continue to send heartbeat messages
                continue;
            }
            else 
            {
                std::cerr << "Error receiving MAVLink messages" << std::endl;
                break;
            }
        }

        // Parse the byte and check if a message has been received
        uint8_t byte;
        mavlink_status_t lastStatus;
        for (unsigned int i = 0; i < n; ++i)
        {
            byte = buffer[i];
            lastStatus = status;
            if (mavlink_parse_char(MAVLINK_COMM_0, byte, &msg, &status)) 
            {
                // Handle the message based on its type
                switch (msg.msgid) 
                {
                    case MAVLINK_MSG_ID_HEARTBEAT:
                        mavlink_heartbeat_t heartbeat;
                        mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                        print_heartbeat(heartbeat);
                        break;
                    case MAVLINK_MSG_ID_COMMAND_ACK:
                        mavlink_command_ack_t command_ack;
                        mavlink_msg_command_ack_decode(&msg, &command_ack);
                        print_command_ack(command_ack);
                        break;
                    case MAVLINK_MSG_ID_REQUEST_DATA_STREAM:
                        mavlink_request_data_stream_t request;
                        mavlink_msg_request_data_stream_decode(&msg, &request);
                        print_request_data_stream(request);
                        break;
                    default:
                        // Handle other message types here
                        std::cout << "Received message with ID " << (int)msg.msgid << std::endl;
                        break;
                }
            }
            // If a message has not been completely received yet, continue to receive bytes
            else if (lastStatus.packet_rx_drop_count != status.packet_rx_drop_count)
            {
                // There was an error parsing the message, but we can keep trying to receive bytes
                break;
            }
        }
    }

    // Close the socket
    close(sock);

    return 0;
}

