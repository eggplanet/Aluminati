#pragma config(Sensor, S3,     IRseekA,        sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     IRseekB,        sensorHiTechnicIRSeeker1200)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment\Sample Programs\NXT\3rd Party Sensor Drivers\drivers\hitechnic-irseeker-v2.h"

int getIntensity(){
	int acS1A, acS2A, acS3A, acS4A, acS5A = 0;
	int acS1B, acS2B, acS3B, acS4B, acS5B = 0;
	int maxSigA = 0;
	int maxSigB = 0;
	int maxSig = 0;
	if(HTIRS2readAllACStrength(IRseekA, acS1A, acS2A, acS3A, acS4A, acS5A)){
		maxSigA = (acS1A > acS2A) ? acS1A : acS2A;
		maxSigA = (maxSigA > acS3A) ? maxSigA : acS3A;
		maxSigA = (maxSigA > acS4A) ? maxSigA : acS4A;
		maxSigA = (maxSigA > acS5A) ? maxSigA : acS5A; //sets maxSig to maximum intensity
	}
	if(HTIRS2readAllACStrength(IRseekB, acS1B, acS2B, acS3B, acS4B, acS5B)){
		maxSigB = (acS1B > acS2B) ? acS1B : acS2B;
		maxSigB = (maxSigB > acS3B) ? maxSigB : acS3B;
		maxSigB = (maxSigB > acS4B) ? maxSigB : acS4B;
		maxSigB = (maxSigB > acS5B) ? maxSigB : acS5B; //sets maxSig to maximum intensity
	}
	maxSig = (maxSigA > maxSigB)? maxSigA : maxSigB;
	return maxSig; //makes getIntensity() return the highest intensity
}

task main()
{
  int nSeekerA;
  int intensity;
	while (true)
  {
    nSeekerA = SensorValue[IRseekA];
    intensity = getIntensity();
    nxtDisplayCenteredBigTextLine(1, "%IR Seek");
    nxtDisplayCenteredBigTextLine(2, "%d", nSeekerA);
    nxtDisplayCenteredBigTextLine(3, "%Intensity");
    nxtDisplayCenteredBigTextLine(4, "%d", intensity);
   }
}
