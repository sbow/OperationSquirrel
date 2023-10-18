#include "standard_libs.h"
#include "mavlink_msg_handler.h"
#include "mavlink_command_handler.h"

const float dt = 0.025;

float timerVal = 0;
int stage = 0;

void countupTimer(void)
{
    timerVal = timerVal + dt; // printf("Timer: %.3f\n", timerVal);
}

void resetTimer(void)
{
    timerVal = 0;
}

void test_flight(void)
{
    countupTimer();

    // parameters for set_attitude_target command
    uint8_t type_mask = 0; //ATTITUDE_TARGET_TYPEMASK_BODY_ROLL_RATE_IGNORE | ATTITUDE_TARGET_TYPEMASK_BODY_PITCH_RATE_IGNORE;
    float body_yaw_rate = 0.0;  // Specify the desired yaw angle in radians
    float q[4];
    q[0] = cos(body_yaw_rate / 2.0);  // Real part of the quaternion
    q[1] = 0.0;  // Imaginary part (i)
    q[2] = 0.0;  // Imaginary part (j)
    q[3] = sin(body_yaw_rate / 2.0);  // Imaginary part (k)
    float body_roll_rate = 0.0;
    float body_pitch_rate = 0.0;
    float thrust = (float)0.5;  // Define the desired thrust magnitude (adjust as needed), Range: 0.0 (no thrust) to 1.0 (full thrust)
    const float thrust_body[3] = {(float)1.0, (float)0.0, (float)0.0};  // Define the desired thrust direction, Positive X-axis (forward)

    if (timerVal > 5.0)
    {
        send_cmd_set_attitude_target(type_mask, q, body_roll_rate, body_pitch_rate, body_yaw_rate, thrust, thrust_body);
    }
}
