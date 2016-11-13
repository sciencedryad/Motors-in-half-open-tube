#include "Definitions.CPP"

int countSeed;

int main()
{
int countTime;
int countSeed;
int countMC;
int i,j;	
time_t time1,time2;		//time measurement variables
double timeUsed=0;		//time difference
int countMotors;			// counts motors
int randomInt;			// random integer
double randomDouble;		// random double
bool initialized;			// bool for motor initialization
LOCATIONS actualLocation;
int actualNumberOfMotors;
int actualLocationNumber,newLocationNumber;
int actualSlice;
int actualRadius;
int actualSegmentVol;

cout<<"INITIALIZE"<<endl;
#include "TimeInitialize.CPP"

// SEED LOOP
cout<<"SEED LOOP"<<endl;
for(countSeed=1;countSeed<=numberOfSeeds;countSeed++)
{

	#include "TimeInitializeStep.CPP"

// EQUILIBRATION LOOP
	for (countMC=1;countMC<=equilibrationSteps;countMC++)
	{
		//#include "UpdateMotors.CPP"
		//#include "UpdateBoundaries.CPP"
		#include "UpdateMotorsAndBoundaries.CPP"
	}// end for countMC equilibration

// MEASUREMENT LOOP
	for (countTime=0;countTime<totalTime;countTime++)
	{
	//measure
		#include "TimeMeasure.CPP"
	//MC steps
		for (countMC=1;countMC<=numberOfMCSteps;countMC++)
		{
			#include "UpdateMotorsAndBoundaries.CPP"
			//#include "UpdateMotors.CPP"
			//#include "UpdateBoundaries.CPP"
		}//end for countMC
	}//end for countTime simulation

	#include "TimeFinalStep.CPP"

}//end for countSeed

cout<<"FINAL MEASUREMENT"<<endl;
#include "TimeFinalMeasure.CPP"

return 0;
}// end main
