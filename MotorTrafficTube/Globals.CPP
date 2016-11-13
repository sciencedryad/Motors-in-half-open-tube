//================================================
// GLOBAL VARIABLES
//================================================

int actualNumberOfMeasurements=0;

// profiles of density and current (plus and minus)
	double rho_b[tubeLength];	// bound density
	double rho_ub[tubeLength];	// unbound density
	double j_b[tubeLength-1];	// bound current, measured by correlations
	double j_ub[tubeLength-1];	// unbound current (correlations)
	double j_tot[tubeLength-1]; 	// total current (correlations)

// variables for correlation measurement
int chosenPoint = Lattice.GetMiddleOfFilament();
		// point for measurements at each measurement (correlations)
double densityAtChosenPoint=0;
double currentAtChosenPoint=0;
double meanNumberOfParticles=0;

// variables for total densities, currents, motor numbers
double rho_b_tot=0;
double rho_ub_tot=0;
double j_b_tot=0;
double j_ub_tot=0;

double meanNumberOfMotors = 0;
double meanNumberOfPlusMotors = 0;
double meanNumberOfMinusMotors = 0;

// variables for plus and minus motors
double rho_b_plus[tubeLength];
double rho_b_minus[tubeLength];
double rho_ub_plus[tubeLength];
double rho_ub_minus[tubeLength];

double rho_b_tot_plus=0;
double rho_ub_tot_plus=0;
double rho_b_tot_minus=0;
double rho_ub_tot_minus=0;

// radiual densities
double rho_ub_radius[tubeLength][tubeRadiusY];
double rho_ub_plus_radius[tubeLength][tubeRadiusY];
double rho_ub_minus_radius[tubeLength][tubeRadiusY];


Particle* pMotor[numberOfMotorPointers];
	// array of motor pointers

//-------------------------------------------------------------------
// Globals for time measurements

double rho_b_Time[tubeLength][totalTime]; 	//bound density
double rho_ub_Time[tubeLength][totalTime];	// unbound density
double j_b_Time[tubeLength-1][totalTime];	// bound current
double j_ub_Time[tubeLength-1][totalTime];	// unbound current
double rho_b_tot_Time[totalTime];			// total bound density
double rho_ub_tot_Time[totalTime];		// total unbound density
double j_b_tot_Time[totalTime];			// total bound current
double j_ub_tot_Time[totalTime];			// total unbound current
int motorN[totalTime];					// total motor number
double jamLength[totalTime];
double jamLength2[totalTime];
double rho_ub_radius_Time[tubeRadiusY][totalTime];
