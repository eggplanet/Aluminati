#pragma config(Hubs,  S2, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S2_C2_1,     motorIntake,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     motorArm,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C3_1,     motorLeftWs,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C3_2,     motorRightWs,  tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servoHook,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

void hookDown (){
	servo[servoHook] = 255;
}
void hookUp (){
	servo[servoHook] = 0;
}

task main()
{
	while(true)
	{
		getJoystickSettings(joystick);

		if (joy1Btn(4)==1)
			hookDown();

	}
}