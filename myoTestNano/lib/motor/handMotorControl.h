/*!
 *  @file motor.h
 */
#ifndef _HAND_MOTOR_CONTROL_H
#define _HAND_MOTOR_CONTROL_H

// Include Adafruit PWM Library
#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH       110
#define MAX_PULSE_WIDTH       510
#define FREQUENCY             50

#define SERVO_THUMB     10
#define SERVO_INDEX     11
#define SERVO_MIDDLE    12
#define SERVO_RING      13
#define SERVO_PINKY     14
#define SERVO_WRIST     15


class handControl {
    public:
        handControl();
    //Poses functions
        void initServo(void);
        void rest(void);
        void fist(void);
        void spread(void);
        void pick(void);
        void setWristAngle(int);
    private:
        Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
        void setServo(uint8_t, int);
};

#endif