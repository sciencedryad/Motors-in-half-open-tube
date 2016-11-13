//*******************************************************************
// libraries
//*******************************************************************
#include<iostream.h>
#include<fstream.h>
#include<time.h>
#include<stdlib.h>
//#include<malloc.h>
#include<math.h>

//*******************************************************************
// RANDOM NUMBERS
//*******************************************************************
#include "RandomMTImproved.CPP"
// Mersenne Twister Random Number Generator
// improved initialization and speed
// provides routines
// - to initialize: void init_genrand(unsigned long seed)
// - to call: double genrand_real1(void)
#define randomInitialize init_genrand
#define randomDouble01 genrand_real1
#define randomInteger genrand_int

//*******************************************************************
// types
//*******************************************************************
enum LOCATIONS { InSpace=1, OnFilament=2, OnLeftBoundaryOnFilament=3,
		OnLeftBoundaryInSpace=4, OnRightBoundaryOnFilament=5,
 		OnRightBoundaryInSpace=6, OnWall=7,
		NotValid=0};

enum OCCUPATIONS { FREE=0, //OCCUPIED=1,
		OCCUPIEDPLUS=2, OCCUPIEDMINUS=3};

enum DIRECTIONS { PLUS=1, MINUS=2};

enum INTERACTIONS { NoInteraction=1, HardCore = 2};
//ATTENTION: NoInteraction does not work!!!

enum BOUNDARIES { RhoInRhoEx=1, RhoInWall=2,
			WallRhoEx=3, WallWall=4, Periodic=5 };

//*******************************************************************
//display types
//*******************************************************************

void DisplayLocations(const LOCATIONS& loc)
{
if (loc==InSpace){cout<<"InSpace";}
else if (loc==OnFilament){cout<<"OnFilament";}
else if (loc==OnLeftBoundaryOnFilament){cout<<"OnLeftBoundaryOnFilament";}
else if (loc==OnLeftBoundaryInSpace){cout<<"OnLeftBoundaryInSpace";}
else if (loc==OnRightBoundaryOnFilament){cout<<"OnRightBoundaryOnFilament";}
else if (loc==OnRightBoundaryInSpace){cout<<"OnRightBoundaryInSpace";}
else if (loc==OnWall){cout<<"OnWall";}
else if (loc==NotValid){cout<<"NotValid";}
else {cout<<"Error! Wrong location! ";exit(8);}
return;
}//end DisplayLocations

void DisplayOccupation(const OCCUPATIONS& occ)
{
if (occ==FREE){cout<<"FREE";}
//else if (occ==OCCUPIED){cout<<"OCCUPIED";}
else if (occ==OCCUPIEDPLUS){cout<<"OCCUPIEDPLUS";}
else if (occ==OCCUPIEDMINUS){cout<<"OCCUPIEDMINUS";}
else {cout<<"Error! Wrong occupation! "; exit(8);}
return;
}//end DisplayOccupation

void DisplayDirections(const DIRECTIONS& dir)
{
if (dir==PLUS){cout<<"PLUS";}
else if (dir==MINUS){cout<<"MINUS";}
else {cout<<"Error! Wrong direction!";exit(8);}
return;
}//end DisplayDirections

void DisplayInteractions(const INTERACTIONS& inter)
{
if (inter==NoInteraction){cout<<"NoInteraction";}
else if (inter==HardCore){cout<<"HardCore";}
else {cout<<"Error! Wrong interaction!";exit(8);}
return;
}//end DisplayInteractions

void DisplayBoundaries(const BOUNDARIES bound)
{
if (bound==RhoInRhoEx){cout<<"RhoInRhoEx";}
else if (bound==RhoInWall){cout<<"RhoInWall";}
else if (bound==WallRhoEx){cout<<"WallRhoEx";}
else if(bound==WallWall){cout<<"WallWall";}
else if (bound==Periodic){cout<<"Periodic";}
else {cout<<"Error! Wrong boundary!";exit(8);}
return;
}//end DisplayBoundaries

//*******************************************************************
// debugging
//*******************************************************************
#define DEBUG
#include "Assert.CPP"
//#define DEBUG2 // output motor hopping

//*******************************************************************
// parameters
//*******************************************************************
#include "Parameters.CPP"

//*******************************************************************
// classes
//*******************************************************************
#include "TubeGlobals.CPP" 	// closed or open finite tube
GlobalGeometry Lattice;		// initializes global geometry "Lattice"

#include "GlobalsDynamic.CPP" // global variables for dynamics measurements
#include "Particle.CPP"		// motor class

//*******************************************************************
// globals
//*******************************************************************
#include "Globals.CPP"

//*******************************************************************
// subroutines
//*******************************************************************
#include "MotorSubroutines.CPP"



