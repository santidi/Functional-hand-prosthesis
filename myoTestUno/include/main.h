/**
 * @file   main.c
 * @author Jeremias Baez
 * @date   Diciembre 2019
 * @brief  Main tesis code, translate pose detected from Myo Bridge to Robotic Arm
 */

#define MIN_PULSE_WIDTH       110
#define MAX_PULSE_WIDTH       510
#define FREQUENCY             50


#define SERVO_THUMB     8
#define SERVO_INDEX     9
#define SERVO_MIDDLE    10
#define SERVO_RING      11
#define SERVO_PINKY     12