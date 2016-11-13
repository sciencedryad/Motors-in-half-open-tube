#include "Definitions.CPP"

int main()
{
//******************************************************************
// VARIABLES
//******************************************************************

int countMeasure; 		// count measurement steps
int countMC;			// counts MC steps between measurements
int countMotors;			// counts motors
int i,r;				// loop variable
time_t time1, time2;		//time measurement variables
double timeUsed=0;		//time difference
int randomInt;			// random integer
double randomDouble;		// random double
bool initialized;			// bool for motor initialization
LOCATIONS actualLocation;//actual loaction variable
DIRECTIONS actualDirection;
int actualNumberOfMotors;
int actualLocationNumber,newLocationNumber;
int actualSlice;
double actualRho_b,actualRho_ub;
int actualRadius;
double absorptionEqui;

// VARIABLES FOR MODULES UpdateEachMotor and UpdateEachBoundary
//int motorsToUpdate[numberOfMotorPointers];	// list of motors with motorNumbers that still have to be updated
//int numberOfMotorsToUpdate;		// number of motors that still have to be updated
//int actualMotorNumber;

//******************************************************************
// INITIALIZATION
//******************************************************************
cout<<"INITIALIZE"<<endl;
#include "Initialize.CPP"
	// initializes random number generator, file names
	// initializes global variables
	// initializes motors
	// writes parameter file

//******************************************************************
// EQUILIBRATION LOOP
//******************************************************************
cout<<"EQUILIBRATION"<<endl;
for (countMC=1;countMC<=equilibrationSteps;countMC++)
{
	#include "UpdateMotorsAndBoundaries.CPP"
//	#include "UpdateMotors.CPP"	// random motor update
//	#include "UpdateBoundaries.CPP"			// random boundary update
//	#include "UpdateEachMotor.CPP" // random motor update, but of EACH motor
//	#include "UpdateEachBoundaries.CPP"		// random boundary update, but of EACH boundary site
//	#include "UpdateBoundariesSequential.CPP"	// sequential boundary update
}
#include "ReInitialize.CPP" // reInitialize dynamic globals

cout<<"MEASUREMENT"<<endl;

//******************************************************************
// MEASUREMENT LOOP
//******************************************************************
for(countMeasure=1;countMeasure<=numberOfMeasurements;countMeasure++)
{
//cout<<"measurement no "<<countMeasure
//	<<", numberOfMinusMotors = "<<Particle::numberOfMinusParticles
//	<<", numberOfPlusMotors = "<<Particle::numberOfPlusParticles
//	<<", totalNumberOfMotors = "<<Particle::totalNumberOfParticles<<endl;
//******************************************************************
// MC STEPS
//******************************************************************
	for (countMC=1;countMC<=numberOfMCSteps;countMC++)
	{
	#include "UpdateMotorsAndBoundaries.CPP"
//	#include "UpdateBoundaries.CPP"			// random boundary update
//	#include "UpdateMotors.CPP"	// random motor update
//	#include "UpdateEachMotor.CPP" // random motor update, but of EACH motor
//	#include "UpdateEachBoundaries.CPP"		// random boundary update, but of EACH boundary site
//	#include "UpdateBoundariesSequential.CPP"	// sequential boundary update
	}// end countMC-loop

//******************************************************************
// measure
//******************************************************************
	#include "Measure.CPP"

//******************************************************************
} //end measure loop

//Lattice.DisplayOccupations();

//******************************************************************
//******************************************************************
cout<<"FINAL MEASURE"<<endl;
#include "FinalMeasure.CPP"
	// free motor memory
	// normalize densities, calculate current
	// write to files, close files

return 0;
}// end main()
