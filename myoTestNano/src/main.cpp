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

#include <handMotorControl.h>

/*
//MYO bridge functions/defines
//SoftwareSerial connection to MyoBridge, pins D2-rx, D4-tx
SoftwareSerial bridgeSerial(2, 4);
//initialize MyoBridge object with software serial connection
MyoBridge bridge(bridgeSerial);


//a function to inform us about the current state and the progess of the connection to the Myo.
void printConnectionStatus(MyoConnectionStatus status)
{
	//print the status constant as string
	Serial.println(bridge.connectionStatusToString(status));
}

void handleEMGData(int8_t data[8]){
	//the EMG data is 8bit signed integers. Just print them out:
	Serial.print(data[0]); Serial.print(" "); Serial.print(data[1]); Serial.print(" ");
  	Serial.print(data[2]); Serial.print(" "); Serial.print(data[3]); Serial.print(" ");
  	Serial.print(data[4]); Serial.print(" "); Serial.print(data[5]); Serial.print(" ");
  	Serial.print(data[6]); Serial.print(" "); Serial.print(data[7]); Serial.println(" ");
}

//declare a function to handle pose data
void handlePoseData(MyoPoseData &data){
	//convert pose data to MyoPose
	MyoPose pose;
	pose = (MyoPose)data.pose;
	Serial.print("Pose: ");
	Serial.println(bridge.poseToString(pose));
	switch (pose)
	{
	case MYO_POSE_REST:
		hand.rest();
		break;
	case MYO_POSE_FIST:
		hand.fist();
		break;
	case MYO_POSE_FINGERS_SPREAD:
		hand.spread();
		break;
	case MYO_POSE_WAVE_IN:
		hand.pick();
		break;
	case MYO_POSE_WAVE_OUT:
		hand.pick();
		break;
	default:
		hand.rest();
		break;
	}
	delay(500);
}
*/

handControl hand = handControl();

void setup()
{
	//initialize both serial connections
	Serial.begin(9600);
	Serial.println("Setup enter - Initializing serial connection for myo");
	// bridgeSerial.begin(115200);
	Serial.println("Initializing servos..");
	hand.initServo();
	hand.rest();
	//wait until MyoBridge has found Myo and is connected. Make sure Myo is not connected to anything else and not in standby!
	// Serial.println("Searching for Myo...");
	//initiate the connection with the status callback function
	// bridge.begin(printConnectionStatus);
	// Serial.println("Connected!");
	// Serial.print("Firmware Version: ");
	// Serial.print(bridge.getFirmwareMajor());
	// Serial.print(".");
	// Serial.print(bridge.getFirmwareMinor());
	// Serial.print(".");
	// Serial.println(bridge.getFirmwarePatch());
	// Serial.print("Hardware Revision: ");
	// Serial.println(bridge.getHardwareRevision());
	//declare a storage array for the hardware address
	// byte address[6];
	//get the address and store it in our array
	// bridge.getHardwareAddress(address);
	//print the hardware address in HEX format
	// Serial.print("Hardware Address: 0x");
	// for (int i = 0; i < 6; i++)
	// {
	// 	Serial.print(address[i], HEX);
	// }
	// Serial.println();
	//get the unlock pose
	// MyoPose unlockPose;
	// unlockPose = bridge.getUnlockPose();
	//print the name of the unlock pose as string
	// Serial.print("Unlock Pose: ");
	// Serial.println(bridge.poseToString(unlockPose));
	// get the current battery level and print it
	// byte batteryLevel = bridge.getBatteryLevel();
	// Serial.print("Battery Level: ");
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

	//Enable pin for PCA9685 board D12
	Serial.println("Setting up enable pin output...");
	pinMode(12, OUTPUT);
	digitalWrite(12, LOW);
	delay(1000);
	// pinMode(LED_BUILTIN, OUTPUT);
	// digitalWrite(LED_BUILTIN, LOW);

	Serial.println("Moving wrist");
	hand.setWristAngle(0);
	delay(1000);
	hand.setWristAngle(90);
	delay(1000);
	hand.setWristAngle(180);
	delay(1000);
	hand.setWristAngle(90);
	delay(1000);
	Serial.println("Finish Moving wrist");
}

String angulo = "0", angulo_prev;

void loop()
{
	//update the connection to MyoBridge
	// bridge.update();
	Serial.println("Closing Hand...");
	hand.fist();
	delay(1000);
	Serial.println("Resting Hand...");
	hand.rest();
	delay(1000);
	Serial.println("Open Hand...");
	hand.spread();
	delay(1000);
	Serial.println("Resting Hand...");
	hand.rest();
	delay(3000);
}