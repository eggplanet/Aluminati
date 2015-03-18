#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S2,     bigBall,        sensorLightActive)
#pragma config(Sensor, S3,     smallBall,      sensorLightActive)
#pragma config(Sensor, S4,     ultrasonic,     sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     FLWheelMotor,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     BLWheelMotor,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     BRWheelMotor,  tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     FRWheelMotor,  tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     shooterMotor,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     armMotor,      tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    rightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    bigGate,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    leftHook,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    rightRamp,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    leftRamp,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    smallGate,            tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*#include "hitechnic-sensormux.h"
#include "lego-light.h"
#include "hitechnic-gyro.h"
#include "hitechnic-irseeker-v2.h"
#include "lego-ultrasound.h"*/
#include "JoystickDriver.c"
/*
#define bigLightSensor           	  msensor_S2_1
#define	someSensor1          			  msensor_S2_2
#define smallLightSensor      	 		msensor_S2_3
#define someSensor2	          		  msensor_S2_4
//sensor MUX
//Port 1: big ball light (right)
//Port 2:
//Port 3: small ball light (left)
//Port 4:
HTGYROstartCal(gyroSensor);
int gyroRotation = HTGYROreadRot(gyroSensor);
//int distanceInCM = USreadDist(sonarSensor);
int irACDirection = HTIRS2readACDir(irSeekerSensor);
//bool limitSWActive = TSreadState(touchSensor);
*/
/*
#define gyroSensor              msensor_S4_1
#define sonarSensor             msensor_S4_2
#define irSeekerSensor          msensor_S4_3
#define touchSensor             msensor_S4_4ssssss
*/

// Constants
#define DEADBAND(x) ((abs(x) >= 10)? x: 0)
#define WAIT_TIME 5
#define BIG_BALL 1
#define SMALL_BALL 2

// Class variables
int bigGateButtonCooldown = 0;
int smallGateButtonCooldown = 0;
int shooterCooldown = 0;
//int armCooldown = 0;
//int rampPosition = 128;

int motorScale(float x)
{
	x = ((x / 128) * 100);
	if (x > 100)
		x = 100;
	return x;
}

int scaleAndyMarkMotor(int x)
{
	return ((x/100) * 78);
}

void drive(int x, int y, int r)
{
	float k = 1.0;
	float kR = 1.0;

	int xPower, yPower, rPower, FLPower, BLPower, BRPower, FRPower;

	xPower = k 	* motorScale(DEADBAND(x));
	yPower = k 	* motorScale(DEADBAND(y));
	rPower = kR	* motorScale(DEADBAND(r));

	FLPower = motorScale(		xPower	+	yPower	+	rPower);
	BLPower = motorScale( -	xPower 	+	yPower	+	rPower);
	BRPower = motorScale(		xPower	+	yPower	-	rPower);
	FRPower = motorScale( -	xPower	+	yPower	-	rPower);

	motor[FLWheelMotor] = FLPower;
	motor[BLWheelMotor] = BLPower;
	motor[BRWheelMotor] = BRPower;
	motor[FRWheelMotor] = FRPower;
}

void arm(int x)
{
	float k = .4999999999;
	motor[armMotor] = k * motorScale(x);
}

void armUp(int x) // needs to be tested
{
		motor[armMotor] = 50 * x;
}

void armDown(int x)
{
		motor[armMotor] = -50 * x;
}

void shooter(int x)
{
	int k = 100;
	motor[shooterMotor] = x * k;
}

void moveArm(int x, int y)
{
	motor[armMotor] = 50 * (x - y);
}

int servo_in = 150;
int servo_in_l = 105;
void ramp_in (int btn_x)
{
	if (btn_x == 1)
	{
		servo[rightRamp] = servo_in;
		servo[leftRamp] = servo_in_l;
	}
}

int servo_middle = 255;
int servo_middle_l = 50;
void ramp_middle (int btn_x)
{
	if (btn_x == 1)
	{
		servo[rightRamp] = servo_middle;
		servo[leftRamp] = servo_middle_l;
	}
}

int servo_out = 150;
int servo_out_l = 105;
void ramp_out (int btn_x)
{
	if (btn_x == 1)
	{
		servo[rightRamp] = servo_out;
		servo[leftHook] = servo_out_l;
	}
}

int hookUpRight = 150;	// smaller value is more up
int hookUp = 250 - hookUpRight;

void servo_up (int btn_x)
{
	if (btn_x == 1)
	{
		servo[leftHook] = hookUp;
		servo[rightHook] = hookUpRight;
	}
}

int HookDownRight = 245; // greater value is more down
int HookDown = 253 - HookDownRight;
void servo_down (int btn_x)
{
	if (btn_x == 1)
	{
		servo[leftHook] = HookDown;
		servo[rightHook] = HookDownRight;
	}
}

void openBigGate ()
{
	servo[bigGate] = 175;
	wait1Msec(260);
	servo[bigGate] = 225;
}

void openSmallGate ()
{
	servo[smallGate] = 60;
	wait1Msec(150);
	servo[smallGate] = 20;
}

void moveRampUp ()
{
	servo[leftRamp] = ServoValue[leftRamp] + 2;
	servo[rightRamp] = 256 - ServoValue[leftRamp];
}

void moveRampDown ()
{
	servo[leftRamp] = ServoValue[leftRamp] - 2;
	servo[rightRamp] = 256 - ServoValue[leftRamp];
}

// Needs to be implemented
void setRamp(int ballSize) {
	switch (ballSize) {
		case BIG_BALL:
			// SET RAMP ADJUSTMENT TO BIG BALL MODE
			break;
		case SMALL_BALL:
			// SET RAMP ADJUSTMENT TO SMALL BALL MODE
			break;
	}
}

// Needs to be tested
void primeShooter()
{
	//nMotorEncoder[armMotor] = 0;
	nMotorEncoderTarget[shooterMotor] = 1080;
	motor[shooterMotor] = scaleAndyMarkMotor(50);
	while (nMotorRunState[shooterMotor] != runStateIdle) {} // wait while motor is running
	motor[shooterMotor] = 0;
}

// needs to be tested
void autoShoot()
{
	if (SensorValue(bigBall) > 30)
	{
		setRamp(BIG_BALL);
		openBigGate();
		wait1Msec(10);
		primeShooter();
		wait1Msec(1000);
	}
	/*else if (SensorValue(smallBall) == 1)
	{
		setRamp(SMALL_BALL);
		openSmallGate();
		wait1Msec(10);
		primeShooter();
		wait1Msec(1000);
	}*/
}

void initRobot()
{
	nMotorEncoder[armMotor] = 0;
}

task main()
{
	initRobot();
	while(true)
	{
		wait1Msec(5); // interval between each main loop
		getJoystickSettings(joystick);

		drive(joystick.joy1_x1, joystick.joy1_y1, joystick.joy1_x2); // normal drive

		/*if (armCooldown <= 0) {
			if (joy1Btn(8)){
				chompArm();
				armCooldown = 75;
			}
		} else {
			armCooldown--;
		}
		*/
		//arm(joystick.joy2_y1);

		if (shooterCooldown <= 0) {
			if (joy2Btn(8)){
				primeShooter();
				shooterCooldown = 150;
			}
		} else {
			shooterCooldown--;
		}

		// Autoshoot

		// Cruise Control
		/*
		while (joy1Btn(8)) // cruise control
		{
			arm(0);
			shooter(0);
			wait1Msec(1);
		}
		*/

		/*
		// Ramp
		if (joy2Btn(6))
			moveRampUp();
		if (joy2Btn(5))
			moveRampDown();
		*/

		ramp_middle(joy2Btn(6));
		ramp_in(joy2Btn(5));

		// Hook
		servo_up(joy2Btn(4)); //raise hook
		servo_down(joy2Btn(1)); //lower hook

		moveArm(joy1Btn(6), joy1Btn(5));

		// Gate
		if (bigGateButtonCooldown <= 0) {
			if (joy2Btn(3)) {
				openBigGate();
				bigGateButtonCooldown = 150;
			}
		} else {
			bigGateButtonCooldown--;
		}

		if (smallGateButtonCooldown <= 0) {
			if (joy2Btn(2)) {
				openSmallGate();
				smallGateButtonCooldown = 150;
			}
		} else {
			smallGateButtonCooldown--;
		}
		/*
		{
      if(SensorValue(light_big) > 40)  					// If the big ball (right side) Light Sensor reads a value less than 40:
      {
        servo[bigGate] = 200;                  // gate_big (servo) is open
      }
      else                           	    			// If the Light Sensor reads a value greater than or equal to 45:
      {
        servo[smallGate] = 120;                  // gate_big (servo) is closed.
        while(true)
        {
        	if(SensorValue(light_small) > 40)  		// If the small ball (left side) Light Sensor reads a value less than 40:
        	{
        		servo[smallGate] = 200;
        	}
        	else
        	{
        		servo[smallGate] = 120;
        	}
      }
			}
}
*/
	}
}