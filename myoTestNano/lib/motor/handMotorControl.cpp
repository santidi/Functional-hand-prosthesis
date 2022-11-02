/*!
 *  @file handMotors.cpp
 */
#ifndef _HAND_MOTOR_CONTROL_C
#define _HAND_MOTOR_CONTROL_C

#include <handMotorControl.h>

handControl::handControl(){
}

void handControl::initServo(void){
	pwm.begin();
	pwm.setPWMFreq(FREQUENCY);
}

void handControl::setServo(uint8_t n_servo, int angulo){
	int duty;
	duty = map(angulo, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
	pwm.setPWM(n_servo, 0, duty);
}

void handControl::rest(){
	setServo(SERVO_THUMB, 90);
	setServo(SERVO_INDEX, 90);
	setServo(SERVO_MIDDLE, 90);
	setServo(SERVO_RING, 90);
	setServo(SERVO_PINKY, 90);
}

void handControl::fist(){
	setServo(SERVO_THUMB, 180);
	setServo(SERVO_INDEX, 180);
	setServo(SERVO_MIDDLE, 180);
	setServo(SERVO_RING, 0);
	setServo(SERVO_PINKY, 0);
}

void handControl::spread(){
	setServo(SERVO_THUMB, 0);
	setServo(SERVO_INDEX, 0);
	setServo(SERVO_MIDDLE, 0);
	setServo(SERVO_RING, 180);
	setServo(SERVO_PINKY, 180);	
}

void handControl::pick(){
	setServo(SERVO_THUMB, 180);
	setServo(SERVO_INDEX, 180);
	setServo(SERVO_MIDDLE, 0);
	setServo(SERVO_RING, 180);
	setServo(SERVO_PINKY, 180);
}

void handControl::setWristAngle(int angle){
	setServo(SERVO_WRIST, angle);
}
#endif