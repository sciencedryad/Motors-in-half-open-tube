//================================================================
//================================================================
// SUBROUTINES FOR MOTOR SIMULATION
//================================================================
//================================================================

//================================================================
//DESTROY Motor
//================================================================
// destroys motor with arrayNumber motorNumber
void destroyMotor(const int& motorNumber)
{
#ifdef DEBUG2
	cout<<"  DESTROY MOTOR!"
		<<" totalNumberOfParticles = "<<Particle::totalNumberOfParticles
		<<", motor to be destroyed: "<<motorNumber<<endl;
#endif
ASSERT(Particle::destroyParticle==1);
ASSERT((motorNumber>=0)&&(motorNumber<Particle::totalNumberOfParticles));
#ifdef DEBUG
	int actualLocationNumber=pMotor[motorNumber]->GetLocationNumber();
	ASSERT((Lattice.GetOccupation(actualLocationNumber)==OCCUPIEDPLUS)
		||(Lattice.GetOccupation(actualLocationNumber)==OCCUPIEDMINUS));
#endif
delete pMotor[motorNumber];
	// destroys motor, decreases totalNumberOfParticles by 1
ASSERT(Lattice.GetOccupation(actualLocationNumber)==FREE);
pMotor[motorNumber]=pMotor[(Particle::totalNumberOfParticles)];
	// makes pointer of destoyed motor point to last motor
pMotor[Particle::totalNumberOfParticles]=NULL;
	// sets pointer of last motor to null
Particle::destroyParticle=0;
//if(Particle::totalNumberOfParticles==0)
//	{cout<<"ERROR! No more particles!"<<endl;ASSERTperm(0);}
#ifdef DEBUG2
	cout<<"  now totalNumberOfParticles = "<<Particle::totalNumberOfParticles<<endl;
#endif
return;
}//end subroutine destroyMotor

//================================================================
// CREATE motor
//================================================================
// creates motor at locationNumber loc with direction dir and internalClock=0
void createMotor(const int& loc, const DIRECTIONS& dir)
{
int actualNumberOfParticles = Particle::totalNumberOfParticles;
#ifdef DEBUG2
	cout<<"  CREATE MOTOR!";
	cout<<" totalNumberOfParticles = "
		<<Particle::totalNumberOfParticles
		<<", motor to be created at location: "<<loc<<endl;
#endif
ASSERTperm(actualNumberOfParticles<numberOfMotorPointers);
#ifdef DEBUG
	ASSERT((loc>=0)&&(loc<squareTotalVolume));
	if (interaction==HardCore){ASSERT(Lattice.GetOccupation(loc)==FREE);}
	ASSERT((Lattice.GetLocation(loc)==OnFilament)||(Lattice.GetLocation(loc)==InSpace));
	ASSERT(pMotor[actualNumberOfParticles]==NULL);
#endif
pMotor[actualNumberOfParticles] = new Particle(dir,loc,0);
	//creates new motor at location loc with direction dir, internal clock 0
	//increases TotalNumberOfParticles by 1, sets loc OCCUPIED
if (pMotor[actualNumberOfParticles]==NULL)
		{cout<<"ERROR! No memory!"<<endl;ASSERTperm(0);}
ASSERT((Lattice.GetOccupation(loc)==OCCUPIEDPLUS)
	||(Lattice.GetOccupation(loc)==OCCUPIEDMINUS));
ASSERT(Particle::totalNumberOfParticles==actualNumberOfParticles+1);
#ifdef DEBUG2
	cout<<"  created motor no "<<actualNumberOfParticles<<" with ";
	pMotor[actualNumberOfParticles]->DisplaySettings();
	cout<<"  ocupation "; DisplayOccupation(Lattice.GetOccupation(loc));cout<<endl;
	//cout<<"  now totalNumberOfParticles = "<<Particle::totalNumberOfParticles;
#endif
return;
}//end subroutine createMotor

//================================================================
// UPDATE LEFT BOUNDARY
//================================================================
void updateLeftBoundary(const int& actualLocationNumber)
{
LOCATIONS actualLocation = Lattice.GetLocation(actualLocationNumber);
int newLocationNumber = actualLocationNumber + Lattice.GetPlusXOffset();
	//neighbour location in tube
double randomDouble;
#ifdef DEBUG
	ASSERT(actualLocationNumber>=0);ASSERT(actualLocationNumber<squareSliceVolume);
	ASSERT((actualLocation==OnLeftBoundaryOnFilament)
		||(actualLocation==OnLeftBoundaryInSpace)
		||(actualLocation==OnWall));
	ASSERT(newLocationNumber>=squareSliceVolume);
	ASSERT(newLocationNumber<squareTotalVolume);
	ASSERT((boundaryChoice==RhoInWall)||(boundaryChoice==RhoInRhoEx));
#endif
if (Lattice.GetOccupation(newLocationNumber)==FREE)
{
//*******************************************************************
	if (actualLocation==OnLeftBoundaryInSpace)
	{
		randomDouble = randomDouble01();
		if (randomDouble<=rhoUbInPlus)
		{
			randomDouble = randomDouble01();
			if (randomDouble<=pdiff)
				{
					createMotor(newLocationNumber,PLUS);
					ASSERT(Lattice.GetLocation(newLocationNumber)==InSpace);
					ASSERT(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDPLUS);
				}
		}//end if randomDouble<=rhoUbInPlus
		else if (randomDouble<=rhoUbInTot)
		{
			randomDouble = randomDouble01();
			if (randomDouble<=pdiff)
				{
					createMotor(newLocationNumber,MINUS);
					ASSERT(Lattice.GetLocation(newLocationNumber)==InSpace);
					ASSERT(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDMINUS);
				}
		}//end else if randomDouble<=rhoUbInTot
	}//end if actualLocation==OnLeftBoundaryInSpace
//*******************************************************************
	else if (actualLocation==OnLeftBoundaryOnFilament)
	{
		randomDouble = randomDouble01();
		if (randomDouble<=rhoBInPlus)
		{
			randomDouble = randomDouble01();
			if (randomDouble<=alpha)
			{
				createMotor(newLocationNumber,PLUS);
				ASSERT(Lattice.GetLocation(newLocationNumber)==OnFilament);
				ASSERT(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDPLUS)
			}
		}//end if randomDouble<=rhoBInPlus
		else if (randomDouble<=rhoBInTot)
		{
			randomDouble = randomDouble01();
			if (randomDouble<=beta)
			{
				createMotor(newLocationNumber,MINUS);
				ASSERT(Lattice.GetLocation(newLocationNumber)==OnFilament);
				ASSERT(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDMINUS)
			}
		}//ens else if randomDouble<=rhoBInTot
	}//end else if actualLocation==OnLeftBoundaryOnFilament
//*******************************************************************
	#ifdef DEBUG
	else {ASSERT(actualLocation==OnWall);}
	#endif
}//end if newLocation FREE
}//end updateLeftBoundary

//================================================================
// UPDATE RIGHT BOUNDARY
//================================================================
void updateRightBoundary(const int& actualLocationNumber)
{
LOCATIONS actualLocation = Lattice.GetLocation(actualLocationNumber);
int newLocationNumber = actualLocationNumber + Lattice.GetMinusXOffset();
	//neighbour location in tube
double randomDouble;
#ifdef DEBUG
	ASSERT(actualLocationNumber>=squareTotalVolume - squareSliceVolume - 1);
	ASSERT(actualLocationNumber<squareTotalVolume);
	ASSERT((actualLocation==OnRightBoundaryOnFilament)
		||(actualLocation==OnRightBoundaryInSpace)
		||(actualLocation==OnWall));
	ASSERT(newLocationNumber>=0);ASSERT(newLocationNumber<squareTotalVolume);
	ASSERT((boundaryChoice==WallRhoEx)||(boundaryChoice==RhoInRhoEx));
#endif
if (Lattice.GetOccupation(newLocationNumber)==FREE)
{
//*******************************************************************
	if (actualLocation==OnRightBoundaryInSpace)
	{
		randomDouble = randomDouble01();
		if (randomDouble<=rhoUbExPlus)
		{
			randomDouble = randomDouble01();
			if (randomDouble<=pdiff)
			{
				createMotor(newLocationNumber,PLUS);
				ASSERT(Lattice.GetLocation(newLocationNumber)==InSpace);
				ASSERT(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDPLUS);
			}
		}//end if randomDouble<=rhoExUnbound
		else if (randomDouble<=rhoUbExTot)
		{
			randomDouble = randomDouble01();
			if (randomDouble<=pdiff)
			{
				createMotor(newLocationNumber,MINUS);
				ASSERT(Lattice.GetLocation(newLocationNumber)==InSpace);
				ASSERT(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDMINUS);
			}
		}
	}//end if actualLocation==OnRightBoundarynSpace
//*******************************************************************
	else if (actualLocation==OnRightBoundaryOnFilament)
	{
		randomDouble = randomDouble01();
		if (randomDouble<=rhoBExMinus)
		{
			randomDouble = randomDouble01();
			if (randomDouble<=alpha)
			{
				createMotor(newLocationNumber,MINUS);
				ASSERT(Lattice.GetLocation(newLocationNumber)==OnFilament);
				ASSERT(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDMINUS)
			}
		}//end if randomDouble<=rhoBExPlus
		else if (randomDouble<=rhoBInTot)
		{
			randomDouble = randomDouble01();
			if (randomDouble<=beta)
			{
				createMotor(newLocationNumber,PLUS);
				ASSERT(Lattice.GetLocation(newLocationNumber)==OnFilament);
				ASSERT(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDPLUS)
			}
		}//ens else if randomDouble<=rhoBExTot
	}//ens else if actualLocation==OnRightBoundaryOnFilament
//*******************************************************************
	#ifdef DEBUG
	else {ASSERT(actualLocation==OnWall);}
	#endif
}//end if newLocation FREE
}//end update right boundary

//================================================================
//WRITE MOTOR CONFIGURATION (end configuration)
//================================================================
// writes data of motor configuration for restart
void writeMotorConf(char* fileName)
{
int countMotors;
ofstream foutConf(fileName);
	if(!foutConf) {cout<<"Unable to open file! ";ASSERTperm(0);}
foutConf<<tubeLength<<endl;
foutConf<<tubeRadiusY<<endl;
foutConf<<tubeRadiusZ<<endl;
foutConf<<Particle::numberOfPlusParticles<<endl;
foutConf<<Particle::numberOfMinusParticles<<endl;
for(countMotors=0;countMotors<Particle::totalNumberOfParticles;countMotors++)
{
	foutConf<<pMotor[countMotors]->GetLocationNumber()<<endl;
	foutConf<<pMotor[countMotors]->GetDirection()<<endl;
}//end for countMotors
foutConf.close();
return;
}//end subroutine writeMotorConf

//================================================================
// READ MOTOR CONFIGURATION (start configuration)
//================================================================
// reads motor configuration from file fileName
void readMotorConf(char* fileName)
{
int countMotors;
int tubeLengthIn,tubeRadiusYIn,tubeRadiusZIn;
int numberPlus,numberMinus;
int loc, intDir;
DIRECTIONS dir;
ifstream finConf(fileName);
	if(!finConf) {cout<<"Unable to open file! ";ASSERTperm(0);}
finConf>>tubeLengthIn;
finConf>>tubeRadiusYIn;
finConf>>tubeRadiusZIn;
finConf>>numberPlus;
finConf>>numberMinus;
ASSERTperm(tubeLengthIn==tubeLength);
ASSERTperm(tubeRadiusYIn==tubeRadiusY);
ASSERTperm(tubeRadiusZIn==tubeRadiusZ);
ASSERT(numberPlus>=0);ASSERT(numberMinus>=0);
for(countMotors=0;countMotors<(numberPlus+numberMinus);countMotors++)
{
	finConf>>loc;
	finConf>>intDir;
	if (intDir==1){dir=PLUS;}
	else {dir=MINUS;ASSERT(intDir==2);}
	pMotor[countMotors]=new Particle(dir,loc,0);
		if (pMotor[countMotors]==NULL){cout<<"ERROR! No memory!"<<endl;ASSERTperm(0);}
}//end for countMotors
for (countMotors=Particle::totalNumberOfParticles;
			countMotors<numberOfMotorPointers;countMotors++)
	{pMotor[countMotors]=NULL;}
/*
cout<<"INITIALIZE"<<endl;
cout<<tubeLengthIn<<endl;
cout<<tubeRadiusYIn<<endl;
cout<<tubeRadiusZIn<<endl;
cout<<numberPlus<<endl;
cout<<numberMinus<<endl;
for(countMotors=0;countMotors<Particle::totalNumberOfParticles;countMotors++)
{
	pMotor[countMotors]->DisplaySettings();
}
*/
finConf.close();
return;
}//end subroutine readMotorConf

//================================================================
//WRITE CONFIGURATION for film
//================================================================
//writes actual configuration to file
//needs: folder, Particle::totalNumberOfParticles
void writeConfig(const int& fileNumber)
{
char configFile[80]; //file for configuration output
int countMotors;
int locNumber;
LOCATIONS loc;
int x,y,z;
//sprintf(configFile,"%s%s%04i%s",MakeFileNames::folder,"config",fileNumber,".pov");
sprintf(configFile,"%s%s%04i%s","/tmp/Film/","config",fileNumber,".pov");
ofstream foutConfig(configFile);
if(!foutConfig) {cout<<"Unable to open file! ";ASSERTperm(0);}
foutConfig<<"#include \"/usr/people/fornax/mmueller/Povray/povDef.inc\""<<endl;
for(countMotors=0;countMotors<Particle::totalNumberOfParticles;countMotors++)
{
locNumber = pMotor[countMotors]->GetLocationNumber();
loc = Lattice.GetLocation(locNumber);
Lattice.GetCoordinates(locNumber,x,y,z);
if (loc==OnFilament)
	{
		foutConfig<<"object { motorPlusOnFilament translate <"
			<<x<<", "<<y<<", "<<z<<"> }"<<endl;
	}
else
	{
		foutConfig<<"object { motorPlus translate           <"
			<<x<<", "<<y<<", "<<z<<"> }"<<endl;
	}
}//end for countMotors
foutConfig.close();
return;
}//end subroutine writeConfig
