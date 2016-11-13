//****************************************************************
// MISCELLANEOUS PARAMETERS
//****************************************************************

// for every simulation
const int numberOfMCSteps = 1; // between measurements! has to be >=1!
const int equilibrationSteps = 10000000;//100000000;//10000000;//can be 0

// for "normal" simulation (stationary average of 1 Markov chain)
unsigned long int seed = 310; // random number generator seed
const int numberOfMeasurements = 10000000;//000000;
const int measureInterval = 100000;
	// write data to files each measureInterval measurement
	// has to be >=1, <=numberOfMeasurements
const int totalNumberOfMCSteps = numberOfMeasurements * numberOfMCSteps;

//for time siumlation (average over Markov chains for each time step)
const int numberOfSeeds = 10; //  for time MC
const int totalTime = 10; // time for time measurement
const int every = 0; //write time config. only for every every time
const int initialNoMotorsOnFilament = 1; //=0 for random initialize, =1 if initially no motors on filament

// for start configuration
const int readConf = 0; //=1 read conf from ConfigFileIn,=0 random initialize
// for film
const int writeConf = 0; // writes configuration for film if 1, nothing if 0


//****************************************************************
// GEOMETRY PARAMETERS
//****************************************************************

// name of class that defines chosen Geometry
#define GlobalGeometry TubeGlobals
	// finite tube with open or closed boundaries

//BOUNDARIES boundaryChoice = RhoInRhoEx;
//BOUNDARIES boundaryChoice = WallRhoEx;
BOUNDARIES boundaryChoice = RhoInWall;
//BOUNDARIES boundaryChoice = WallWall;
//BOUNDARIES boundaryChoice = Periodic;

const int tubeLength = 600;
const int tubeRadiusY = 1;
const int tubeRadiusZ = tubeRadiusY;

// "square" = square geometry containing original geometry
// 						+ extra surrounding walls
//						+ square completing edges
const int squareLengthX = tubeLength + 2;
	// tube length + two boundary layers (x-direction)
const int squareTransverseLengthY = 2*tubeRadiusY + 3;
const int squareTransverseLengthZ = 2*tubeRadiusZ + 3;
  // diameter + center + walls (y-, z-directions)
const int squareSliceVolume	= squareTransverseLengthY
		* squareTransverseLengthZ; // y-z-area
const int squareTotalVolume = squareLengthX*squareSliceVolume;

//****************************************************************
// MOTOR PARAMETERS
//****************************************************************

const int numberOfMotorsPlus = 0;
const int numberOfMotorsMinus =10;
const int numberOfMotorPointers = squareTotalVolume;
const int tau_b =1;//= 1341; // time scale for bound motors, must be >=1

INTERACTIONS interaction = HardCore;

// hopping probabilities
const int numberOfNeighbours = 6;
const double pdiff = 1.0/numberOfNeighbours;
		// diffusion rate
const double epsilon = 0.01;//0.00746;//0.01;//0.0001;
		// detachment rate
const double pi_det = epsilon/6;
		// reduced ("real") detachment rate
const double pi_ad = 1;
		// attachment rate
const double beta = 0;//(1 - gammaC - (numberOfNeighbours-2)*pi_det)/2;
		// backward step rate
const double alpha = 0.1;//1 - beta - gammaC - (numberOfNeighbours-2)*pi_det;
		// forward step rate
const double gammaC =  1 - beta - alpha - (numberOfNeighbours-2)*pi_det;
	//0;//1-(numberOfNeighbours-2)*pi_det;//0.99;// 0.4987;//=0;
		// stay rate

// in and out densities
const double rhoBInPlus	= 0;
const double rhoBInMinus 	= 0.8;
const double rhoBExPlus 	= 0;
const double rhoBExMinus 	= 0;
const double rhoBInTot = rhoBInPlus + rhoBInMinus;
const double rhoBExTot = rhoBExPlus + rhoBExMinus;
double rhoUbFromRadialEquilibrium(const double rhoB)
	{return epsilon*rhoB/((epsilon-pi_ad)*rhoB+pi_ad);}
const double rhoUbInPlus 	= rhoUbFromRadialEquilibrium(rhoBInPlus);
const double rhoUbInMinus	= rhoUbFromRadialEquilibrium(rhoBInMinus);;
const double rhoUbExPlus	= rhoUbFromRadialEquilibrium(rhoBExPlus);
const double rhoUbExMinus = rhoUbFromRadialEquilibrium(rhoBExMinus);
const double rhoUbInTot = rhoUbInPlus +rhoUbInMinus;
const double rhoUbExTot = rhoUbExPlus +rhoUbExMinus;

//****************************************************************
// FILE NAMES
//****************************************************************

class MakeFileNames
{
public:
// folder name
	static char folder[80];
// general files
	static char parameterFile[80];
	static char MeasureInfo[80];
// files for measurement in each MCstep
	static char CorrRho_b[80];
	static char CorrRho_ub[80];
	static char CorrJ_b[80];
	static char CorrJ_ub[80];
	static char CorrRho_b_tot[80];
	static char CorrRho_ub_tot[80];
	static char CorrJ_b_tot[80];
	static char CorrJ_ub_tot[80];
	static char CorrN[80];
	static char CorrJam[80];
// files for final measurement
	static char ResRho[80];
//	static char ResRho_ub[80];
	static char ResJ[80];
//	static char ResJ_ub[80];
//	static char ResJ_tot[80];
	static char ResRhoRadius[80];
	static char ResJRadius[80];
	static char ResJ_Events[80];
	static char CorrRhoRadius[80];
// configuration file
	static char ConfigFileOut[80];
	static char ConfigFileIn[80];
public:
	void makeNames()
	{
//		sprintf(folder,"%s%s%i%s%i",folder,
//				"L",tubeLength,"R",tubeRadiusY);
		sprintf(parameterFile,"%s%s",
				folder,"Parameters.dat");
		sprintf(MeasureInfo,"%s%s",
				folder,"MeasureInfo.dat");
		sprintf(CorrRho_b,"%s%s",
				folder,"CorrRho_b.dat");
		sprintf(CorrRho_ub,"%s%s",
				folder,"CorrRho_ub.dat");
		sprintf(CorrJ_b,"%s%s",
				folder,"CorrJ_b.dat");
		sprintf(CorrJ_ub,"%s%s",
				folder,"CorrJ_ub.dat");
		sprintf(CorrRho_b_tot,"%s%s",
				folder,"CorrRho_b_tot.dat");
		sprintf(CorrRho_ub_tot,"%s%s",
				folder,"CorrRho_ub_tot.dat");
		sprintf(CorrJ_b_tot,"%s%s",
				folder,"CorrJ_b_tot.dat");
		sprintf(CorrJ_ub_tot,"%s%s",
				folder,"CorrJ_ub_tot.dat");
		sprintf(CorrN,"%s%s",
				folder,"CorrN.dat");
		sprintf(ResRho,"%s%s",
				folder,"ResRho.dat");
//		sprintf(ResRho_ub,"%s%s",
//				folder,"ResRho_ub.dat");
		sprintf(ResJ,"%s%s",
				folder,"ResJ.dat");
//		sprintf(ResJ_ub,"%s%s",
//				folder,"ResJ_ub.dat");
//		sprintf(ResJ_tot,"%s%s",
//				folder,"ResJ_tot.dat");
		sprintf(ResRhoRadius,"%s%s",
				folder,"ResRhoRadius.dat");
		sprintf(ResJRadius,"%s%s",
				folder,"ResJRadius.dat");
		sprintf(CorrJam,"%s%s",
				folder,"CorrJam.dat");
		sprintf(ConfigFileOut,"%s%s",
				folder,"ConfigOut");
		sprintf(ConfigFileIn,"%s%s",
				folder,"ConfigIn");
		sprintf(ResJ_Events,"%s%s",
				folder,"ResJEvents.dat");
		sprintf(CorrRhoRadius,"%s%s",
				folder,"CorrRhoRadius.dat");
	}
	void makeParameterFileName()
		{sprintf(parameterFile,"%s%i%s%i%s",
						"ParamL",tubeLength,"R",tubeRadiusY,".dat");};
};//end class makeFiles
char MakeFileNames::folder[80]="RhoInWallMinusAlph01R01/";  // include
char MakeFileNames::parameterFile[80]="Parameters.dat";
char MakeFileNames::MeasureInfo[80]="MeasureInfo.dat";
char MakeFileNames::CorrRho_b[80]="CorrRho_b.dat";
char MakeFileNames::CorrRho_ub[80]="CorrRho_b.dat";
char MakeFileNames::CorrJ_b[80]="CorrJ_b.dat";
char MakeFileNames::CorrJ_ub[80]="CorrJ_b.dat";
char MakeFileNames::CorrRho_b_tot[80]="CorrRho_b_tot.dat";
char MakeFileNames::CorrRho_ub_tot[80]="CorrRho_ub_tot.dat";
char MakeFileNames::CorrJ_b_tot[80]="CorrJ_b_tot.dat";
char MakeFileNames::CorrJ_ub_tot[80]="CorrJ_b_tot.dat";
char MakeFileNames::CorrN[80]="CorrN.dat";
char MakeFileNames::ResRho[80]="ResRho.dat";
//char MakeFileNames::ResRho_ub[80]="ResRho_ub.dat";
char MakeFileNames::ResJ[80]="ResJ.dat";
//char MakeFileNames::ResJ_ub[80]="ResJ_ub.dat";
//char MakeFileNames::ResJ_tot[80]="ResJ_tot.dat";
char MakeFileNames::ResRhoRadius[80]="ResRhoRadius.dat";
char MakeFileNames::ResJRadius[80]="ResJRadius.dat";
char MakeFileNames::CorrJam[80]="CorrJam.dat";
char MakeFileNames::ConfigFileOut[80]="ConfigOut";
char MakeFileNames::ConfigFileIn[80]="ConfigIn";
char MakeFileNames::ResJ_Events[80]="ResJEvents.dat";
char MakeFileNames::CorrRhoRadius[80]="CorrRhoRadius.dat";

