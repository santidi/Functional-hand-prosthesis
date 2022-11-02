/**
 * @file   main.c
 * @author Jeremias Baez
 * @date   Diciembre 2019
 * @brief  Main tesis code, translate pose detected from Myo Bridge to Robotic Arm
 */

#include <main.h>
#include <Arduino.h>
#include <MyoBridge.h>
#include <SoftwareSerial.h>

// Include Adafruit PWM Library
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();



void setServo(uint8_t n_servo, int angulo) {
  int duty;
  duty=map(angulo,0,180,MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pwm.setPWM(n_servo, 0, duty);  
}

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= FREQUENCY;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

//MYO bridge functions/defines
//SoftwareSerial connection to MyoBridge
SoftwareSerial bridgeSerial(2,3);

//initialize MyoBridge object with software serial connection
MyoBridge bridge(bridgeSerial);

//a function to inform us about the current state and the progess of the connection to the Myo.
void printConnectionStatus(MyoConnectionStatus status) {
	//print the status constant as string
	Serial.println(bridge.connectionStatusToString(status));
}

void handleEMGData(int8_t data[8]) {
  
	//the EMG data is 8bit signed integers. Just print them out:
	/*
	Serial.print(data[0]);
  	Serial.print(" ");
  	Serial.print(data[1]);
  	Serial.print(" ");
  	Serial.print(data[2]);
  	Serial.print(" ");
  	Serial.print(data[3]);
  	Serial.print(" ");
  	Serial.print(data[4]);
  	Serial.print(" ");
  	Serial.print(data[5]);
  	Serial.print(" ");
  	Serial.print(data[6]);
  	Serial.print(" ");
  	Serial.print(data[7]);
  	Serial.println(" ");
	*/

}

//declare a function to handle pose data
void handlePoseData(MyoPoseData& data) {
  
	//convert pose data to MyoPose
	MyoPose pose;
	pose = (MyoPose)data.pose;
	//print the pose
	Serial.println(bridge.poseToString(pose));

	switch (pose)
	{
	case MYO_POSE_REST:
		setServo(SERVO_THUMB, 90); setServo(SERVO_INDEX, 90); setServo(SERVO_MIDDLE, 90); setServo(SERVO_RING, 90); setServo(SERVO_PINKY, 90);
		break;
	case MYO_POSE_FIST:
		setServo(SERVO_THUMB, 180); setServo(SERVO_INDEX, 180); setServo(SERVO_MIDDLE, 180); setServo(SERVO_RING, 180); setServo(SERVO_PINKY, 180);
		break;
	case MYO_POSE_FINGERS_SPREAD:
		setServo(SERVO_THUMB, 0); setServo(SERVO_INDEX, 0); setServo(SERVO_MIDDLE, 0); setServo(SERVO_RING, 0); setServo(SERVO_PINKY, 0);
		break;
	case MYO_POSE_WAVE_IN:
		setServo(SERVO_THUMB, 0); setServo(SERVO_INDEX, 0); setServo(SERVO_MIDDLE, 0); setServo(SERVO_RING, 0); setServo(SERVO_PINKY, 0);
		break;
	case MYO_POSE_WAVE_OUT:
		setServo(SERVO_THUMB, 0); setServo(SERVO_INDEX, 0); setServo(SERVO_MIDDLE, 0); setServo(SERVO_RING, 0); setServo(SERVO_PINKY, 0);
		break;
	
	default:
		break;
	}
	delay(500);
}

void setup() {
  	//initialize both serial connections
  	Serial.begin(9600);
	
  	bridgeSerial.begin(115200);
  	//wait until MyoBridge has found Myo and is connected. Make sure Myo is not connected to anything else and not in standby!
  	Serial.println("Searching for Myo...");
  	//initiate the connection with the status callback function
  	// bridge.begin(printConnectionStatus);
  	Serial.println("connected!");
  	Serial.print("Firmware Version: ");
  	Serial.print(bridge.getFirmwareMajor());
  	Serial.print(".");
  	Serial.print(bridge.getFirmwareMinor());
  	Serial.print(".");
  	Serial.println(bridge.getFirmwarePatch());
  	Serial.print("Hardware Revision: ");
  	Serial.println(bridge.getHardwareRevision());
  	//declare a storage array for the hardware address
  	byte address[6];
  	//get the address and store it in our array
  	bridge.getHardwareAddress(address);
  	//print the hardware address in HEX format
  	Serial.print("Hardware Address: 0x");
  	for (int i=0;i<6;i++) {
    	Serial.print(address[i], HEX);
  	}
  	Serial.println();
  	//get the unlock pose
  	MyoPose unlockPose;
  	unlockPose = bridge.getUnlockPose();
  	//print the name of the unlock pose as string
  	Serial.print("Unlock Pose: ");
  	Serial.println(bridge.poseToString(unlockPose));
  	//get the current battery level and print it
  	// byte batteryLevel = bridge.getBatteryLevel();
  	Serial.print("Battery Level: ");
  	// Serial.println(batteryLevel);
	//short vibration to show we are ready
  	// bridge.vibrate(1);
  	//set the function that handles EMG data
  	// bridge.setEMGDataCallBack(handleEMGData);
  	//tell the Myo we want the filtered EMG data
	//bridge.setEMGMode(EMG_MODE_SEND);	
	//set the function that handles pose events
	// bridge.setPoseEventCallBack(handlePoseData);
	//tell the Myo we want Pose data
	// bridge.enablePoseData();
  	//disable sleep mode, so we get continous data even when not synced 
  	// bridge.disableSleep();
	

	//Initialize pwm
	pwm.begin();
	pwm.setPWMFreq(FREQUENCY);
	
	Serial.print("Moving motor 0");
    setServo(0,0);
	delay(1000);
    setServo(0,180);
	delay(1000);
    setServo(0,0);
	Serial.print("Finish moving motor 0");

}

String angulo = "0",angulo_prev; 

void loop() {
  	//update the connection to MyoBridge
	// bridge.update();
	while(true)
	{
		// Serial.println("Ingrese el angulo al que desea setear el servo");
		// angulo_prev=angulo;
		// do
		// {
		// 	angulo = Serial.readString();/* code */
		// } while (/* condition */);
		
		// setServo(SERVO_THUMB, angulo.toInt());
		// setServo(SERVO_INDEX, angulo.toInt());
		// setServo(SERVO_MIDDLE, angulo.toInt());
		// setServo(SERVO_RING, angulo.toInt());
		// setServo(SERVO_PINKY, angulo.toInt());
  		
		// Drive each servo one at a time using setPWM() - PARA CALIBRACION DE MOTOR INDIVIDUAL
  		// Serial.print("Moving motor ");
  		// Serial.println(SERVO_THUMB);

  		// for (uint16_t pulselen = MIN_PULSE_WIDTH; pulselen < MAX_PULSE_WIDTH; pulselen+=10) {
    	// 	pwm.setPWM(SERVO_THUMB, 0, pulselen);
		// 	Serial.print(pulselen);Serial.print(" - ");
		// 	delay(100);
  		// }	
		// pwm.setPWM(SERVO_THUMB, 0, MAX_PULSE_WIDTH);
  		// delay(500);
  		// Serial.println("Max point");
  		// for (uint16_t pulselen = MAX_PULSE_WIDTH; pulselen > MIN_PULSE_WIDTH; pulselen-=10) {
    	// 	pwm.setPWM(SERVO_THUMB, 0, pulselen);
		// 	Serial.print(pulselen);Serial.print(" - ");
		// 	delay(100);
  		// }
    	// pwm.setPWM(SERVO_THUMB, 0, MIN_PULSE_WIDTH);
		// Serial.println("Min point");
  		// delay(1000);		
		setServo(SERVO_THUMB, 0);
		setServo(SERVO_INDEX, 0);
		setServo(SERVO_MIDDLE, 0);
		setServo(SERVO_RING, 0);
		setServo(SERVO_PINKY, 0);
		delay(3000);
		setServo(SERVO_THUMB, 90);
		setServo(SERVO_INDEX, 90);
		setServo(SERVO_MIDDLE, 90);
		setServo(SERVO_RING, 90);
		setServo(SERVO_PINKY, 90);
		delay(3000);
		setServo(SERVO_THUMB, 180);
		setServo(SERVO_INDEX, 180);
		setServo(SERVO_MIDDLE, 180);
		setServo(SERVO_RING, 180);
		setServo(SERVO_PINKY, 180);
		delay(3000);
	}

}