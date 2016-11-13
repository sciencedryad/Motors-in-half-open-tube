//********************************************************************
// Particle (Motor) class
// needs geometry "Lattice", tau_b
// needs GlobalsDynamics
//********************************************************************
class Particle
{
private:
	int itsLocationNumber;
	DIRECTIONS itsDirection;
	int itsInternalClock;
//********************************************************************
public:
	static int totalNumberOfParticles;
	static int numberOfPlusParticles;
	static int numberOfMinusParticles;
	static int destroyParticle;
		//=0 standard, =1 if motor has to be destroyed
	static int makeParticle;
		// =0 standard, =1 if motor has to be created
	Particle(const DIRECTIONS& dir, const int& locationNumber,
		const int& clockTime)
	{
		#ifdef DEBUG
			if (interaction==HardCore)
				{ASSERT(Lattice.GetOccupation(locationNumber)==FREE);}
			ASSERT(clockTime>=0);
		#endif
		totalNumberOfParticles = totalNumberOfParticles + 1;
		itsLocationNumber = locationNumber;
		itsDirection = dir;
		itsInternalClock=clockTime;
		if(dir==PLUS)
		{
			numberOfPlusParticles = numberOfPlusParticles + 1;
			Lattice.SetOccupation(itsLocationNumber,OCCUPIEDPLUS);
		}
		else
		{
			numberOfMinusParticles = numberOfMinusParticles + 1;
			Lattice.SetOccupation(itsLocationNumber,OCCUPIEDMINUS);
		}
		//cout<<"Particle constructor for motor no "
		//	<<Particle::totalNumberOfParticles<<endl; DisplaySettings();
	}//end constructor with arguments
	Particle()
	{
		cout<<"called undefined constructor! "; ASSERT(0);exit(8);
		totalNumberOfParticles = totalNumberOfParticles + 1;
		itsLocationNumber = 0;
		itsDirection = PLUS;
		numberOfPlusParticles = numberOfPlusParticles + 1;
		itsInternalClock=0;
	}//end constructor without arguments
	~Particle()
	{
		ASSERT((Lattice.GetOccupation(itsLocationNumber)==OCCUPIEDPLUS)
			||(Lattice.GetOccupation(itsLocationNumber)==OCCUPIEDMINUS));
		Lattice.SetOccupation(itsLocationNumber,FREE);
		totalNumberOfParticles = totalNumberOfParticles-1;
		if(itsDirection==PLUS)
			{numberOfPlusParticles = numberOfPlusParticles - 1;};
		if(itsDirection==MINUS)
			{numberOfMinusParticles = numberOfMinusParticles - 1;};
#ifdef DEBUG2
		cout<<"  Particle destructor"<<endl;
#endif
	}//end destructor
//********************************************************************
public:
int GetLocationNumber()const {return itsLocationNumber;};
void SetLocationNumber(const int& locationNumber)
	{
		#ifdef DEBUG
			ASSERT((locationNumber>=0)&&(locationNumber<squareTotalVolume));
			ASSERT((Lattice.GetLocation(locationNumber)==InSpace)
				||(Lattice.GetLocation(locationNumber)==OnFilament));
			if(interaction==HardCore)
				{ASSERT(Lattice.GetOccupation(locationNumber)==FREE);};
		#endif
		itsLocationNumber = locationNumber;
		if (itsDirection==PLUS)
		{
			Lattice.SetOccupation(locationNumber,OCCUPIEDPLUS);
		}
		else
		{
			Lattice.SetOccupation(locationNumber,OCCUPIEDMINUS);
			ASSERT(itsDirection==MINUS)
		};
	};//end SetLocationNumber
DIRECTIONS GetDirection()const {return itsDirection;};
void SetDirection(const DIRECTIONS& direction){itsDirection = direction;};
int GetInternalClock()const {return itsInternalClock;};
void SetInternalClock(const int clockTime){itsInternalClock = clockTime;};
void hop()
	{
		LOCATIONS location = Lattice.GetLocation(itsLocationNumber);
		if (location==InSpace)
		{
			diffuse();
		}
		else
		{
			ASSERT(location==OnFilament);
			walk();
		}
	#ifdef DEBUG2
		cout<<endl;
	#endif
	};//end hop
  void DisplaySettings()const;
//********************************************************************
private:
//********************************************************************
// walking types
//********************************************************************
// diffuse
//********************************************************************
void diffuse()	// diffuse InSpace
{
#ifdef DEBUG2
	cout<<"  DIFFUSE";
	cout<<"!!!  sliceVolume = "<<Lattice.GetSliceVolume()
		<<"; totalVolume = "<<Lattice.GetTotalVolume()
		<<"; numberOfFilamentSites = "<<Lattice.GetNumberOfFilamentSites()
		<<"; numberOfSpaceSites = "<<Lattice.GetNumberOfSpaceSites()<<endl;
#endif
ASSERT(Lattice.GetLocation(itsLocationNumber)==InSpace);
double randomNumber = randomDouble01();
ASSERT((randomNumber>=0)&&(randomNumber<=1));
//cout<<",  randomNumber = "<<randomNumber<<endl;
double probability;
int newLocationNumber;
int stayTest;
int movedRightLeft = 0;
// find new site location
probability = pdiff;
if (randomNumber<=probability)
{
	newLocationNumber = movePlusX(itsLocationNumber);
	movedRightLeft = 1;
}
else//don't move PlusX
{
	probability = probability + pdiff;
	if (randomNumber<=probability)
	{
		newLocationNumber = moveMinusX(itsLocationNumber);
		movedRightLeft = -1;
	}
	else //don't move PlusX,MinusX
	{
		probability = probability + pdiff;
		if (randomNumber<=probability)
			{newLocationNumber = movePlusY(itsLocationNumber);}
		else//don't move PlusX,MinusX,PlusY
		{
			probability = probability + pdiff;
			if (randomNumber<=probability)
				{newLocationNumber = moveMinusY(itsLocationNumber);}
			else//don't move PlusX,MinusX,PlusY,MinusY
			{
				probability = probability + pdiff;
				if (randomNumber<=probability)
					{newLocationNumber = movePlusZ(itsLocationNumber);}
				else
					{newLocationNumber = moveMinusZ(itsLocationNumber);}
			}//end don't move PlusX,MinusX,PlusY,MinusY
		}//end else don't move PlusX,MinusX,PlusY
	}//end else don't move PlusX,MinusX
}//end else don't move PlusX
//ASSERT((probability+pdiff)<=1.0001);
ASSERT((probability+pdiff)<=1.);
stayTest=testForStay(newLocationNumber);
if (stayTest==0){} 												// stay!
else if (stayTest==1)												// move!
	{
		measureEvents(itsLocationNumber,
			newLocationNumber,movedRightLeft,InSpace,itsDirection);
		move(newLocationNumber);
		if (Lattice.GetLocation(newLocationNumber)==OnFilament)
			{itsInternalClock = 0;}
	}//end else if stayTest==1
else if (stayTest==2)												// boundary!
	{
		stayTest=checkBoundary(newLocationNumber);
		if (stayTest==0){}	//stay
		else if (stayTest==-1){destroyParticle=1;}//move out
		else //move!
		{
			move(newLocationNumber);
			if (Lattice.GetLocation(newLocationNumber)==OnFilament)
				{itsInternalClock = 0;}
		}//end else
	}//end else if stayTest==2
else
	{cout<<"ERROR in stayTestCheck!"<<endl;ASSERT(0);}

};//end diffuse
//********************************************************************
// walk
//********************************************************************
void walk()		// walk OnFilament
{
#ifdef DEBUG2
	cout<<"  WALK";
#endif
double randomNumber = randomDouble01();
ASSERT((randomNumber>=0)&&(randomNumber<=1));
//cout<<",  randomNumber = "<<randomNumber<<endl;
double probability;
int newLocationNumber;
int stayTest;
int movedRightLeft=0;
int actualSlice;
itsInternalClock = itsInternalClock + 1;
if (itsInternalClock >= tau_b)
{
	itsInternalClock = 0;
// find new site location
	probability = alpha;
	if (randomNumber<=probability)
	{
		if (itsDirection==PLUS)
			{
				newLocationNumber = movePlusX(itsLocationNumber);
				movedRightLeft = 1;
			}
		else // MINUS end motor
			{
				newLocationNumber = moveMinusX(itsLocationNumber);
				movedRightLeft = -1;
			}
	}
	else//not forward
	{
		probability = probability + pi_det;
		if (randomNumber<=probability)
			{newLocationNumber = movePlusY(itsLocationNumber);}
		else//don' detach PlusY
		{
			probability = probability + pi_det;
			if (randomNumber<=probability)
				{newLocationNumber = moveMinusY(itsLocationNumber);}
			else//don't detach MinusY
			{
			probability = probability + pi_det;
				if (randomNumber<=probability)
					{newLocationNumber = movePlusZ(itsLocationNumber);}
				else//don' detach PlusZ
				{
					probability = probability + pi_det;
					if (randomNumber<=probability)
						{newLocationNumber = moveMinusZ(itsLocationNumber);}
					else//don't detach MinusZ
					{
						probability = probability + beta;
						if (randomNumber<=probability)
						{
							if (itsDirection==PLUS)
								{
									newLocationNumber = moveMinusX(itsLocationNumber);
									movedRightLeft = -1;
								}
							else // MINUS end motor
								{
									newLocationNumber = movePlusX(itsLocationNumber);
									movedRightLeft = 1;
								}
						}
						else
						{
							return;// stay (meaning gammaC!=0)
						}
					}//end don't detach MinusZ
				}//end don't detach PlusZ
			}//end don't detach MinusY
		}//end don't detach PlusY
	}//end else not forward
	stayTest=testForStay(newLocationNumber);
	if (stayTest==0){} 										// stay!
	else if (stayTest==1)										// move!
		{
			measureEvents(itsLocationNumber,newLocationNumber,
				movedRightLeft,OnFilament,itsDirection);//measure bound current by events
			move(newLocationNumber);
		}
	else if (stayTest==2)										// boundary!
		{
			stayTest=checkBoundary(newLocationNumber);
			if (stayTest==0){}
			else if (stayTest==-1){destroyParticle=1;}
			else
			{
				ASSERT(stayTest==1);
				move(newLocationNumber);
			}
		}
	else
		{cout<<"ERROR in stayTestCheck!"<<endl;ASSERT(0);}
}//end if itsInternalClock>=tau_b
};//end walk
//********************************************************************
// find locationNumber of nearest neighbour
//********************************************************************
		int movePlusX(const int& oldLocation)
			{return (oldLocation + Lattice.GetPlusXOffset());};
		int moveMinusX(const int& oldLocation)
			{return (oldLocation + Lattice.GetMinusXOffset());};
		int movePlusY(const int& oldLocation)
			{return (oldLocation + Lattice.GetPlusYOffset());};
		int moveMinusY(const int& oldLocation)
			{return (oldLocation + Lattice.GetMinusYOffset());};
		int movePlusZ(const int& oldLocation)
			{return (oldLocation + Lattice.GetPlusZOffset());};
		int moveMinusZ(const int& oldLocation)
			{return (oldLocation + Lattice.GetMinusZOffset());};
//********************************************************************
// move help routines
//********************************************************************
// test newLocation for staying
//********************************************************************
	int testForStay(const int& newLocationNumber)
		// returns 0 if particle should stay
		// returns 1 if particle should move to newLocationNumber
		// returns 2 if particle moves on boundary
	{
		OCCUPATIONS newSiteOccupation
				= Lattice.GetOccupation(newLocationNumber);
		LOCATIONS newSiteLocation
				= Lattice.GetLocation(newLocationNumber);;
#ifdef DEBUG2
		cout<<"  newLocationNumber "<<newLocationNumber
			<<", newSiteLocation "<<newSiteLocation
			<<", newSiteOccupation "<<newSiteOccupation;//<<endl;
#endif
		if ((interaction==HardCore)&&
			((newSiteOccupation==OCCUPIEDPLUS)||(newSiteOccupation==OCCUPIEDMINUS) ))
			// if HardCoreInteraction: stay if new site is occupied
			//		(no matter where it is, also includes wall sites)
			{return 0;}
		if (newSiteLocation==OnWall)
			// stay if new site is on wall
			{return 0;}
		if ((pi_ad<1)&&(newSiteLocation==OnFilament))
			// stay if new site is on filament and motor does not stick
		{
			double randomNumber = randomDouble01();
			ASSERT((randomNumber>=0)&&(randomNumber<=1));
			if (randomNumber>pi_ad){return 0;}
		}
		else if ((newSiteLocation==OnLeftBoundaryInSpace)
			||(newSiteLocation==OnRightBoundaryInSpace)
			||(newSiteLocation==OnLeftBoundaryOnFilament)
			||(newSiteLocation==OnRightBoundaryOnFilament)	)
			{return 2;}
		// else move!
		ASSERT((newSiteLocation==InSpace)
			||(newSiteLocation==OnFilament));
		return 1;
	};//end testForStay
//********************************************************************
// implement boundary conditions from boundaryChoice
//********************************************************************
	int checkBoundary(int& newLocationNumber)
		// implements boundary conditions (except wall)
		// returns 0 if particle should not move
		// returs -1 if particle should leave tube
		// else returns 1 and sets newLocationNumber to newLocationNumber
	{
#ifdef DEBUG2
		cout<<"  checkBoundary!";
#endif
		LOCATIONS newSiteLocation
				= Lattice.GetLocation(newLocationNumber);
		ASSERT((newSiteLocation==OnRightBoundaryInSpace)
				||(newSiteLocation==OnRightBoundaryOnFilament)
				||(newSiteLocation==OnLeftBoundaryInSpace)
				||(newSiteLocation==OnLeftBoundaryOnFilament)	)
		if (newSiteLocation==OnRightBoundaryInSpace)
		{
			if(	(boundaryChoice==RhoInRhoEx)
				||(boundaryChoice==WallRhoEx) )
			{
				double randomNumber = randomDouble01();
				if (randomNumber<=rhoUbExTot) {return 0;}
				else {return -1;}
			}
			else if (boundaryChoice==Periodic)
			{
				newLocationNumber = (newLocationNumber+2*squareSliceVolume)
					- squareTotalVolume;
				if(	(interaction==HardCore)&&
					((Lattice.GetOccupation(newLocationNumber)==OCCUPIEDPLUS)
					||(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDMINUS)))
					{return 0;}
				else
					{return 1;}
			}
			else
			{
				cout<<"ERROR! Boundary conditions unknown!";
				ASSERTperm(0); return 100;
			}
		}//end if newSiteLocation=OnRightBoundaryInSpace
		else if (newSiteLocation==OnRightBoundaryOnFilament)
		{
			if(	(boundaryChoice==RhoInRhoEx)
				||(boundaryChoice==WallRhoEx) )
			{
				double randomNumber = randomDouble01();
				if (randomNumber<=rhoBExTot) {return 0;}
				else {return -1;}
			}
			else if (boundaryChoice==Periodic)
			{
				newLocationNumber = (newLocationNumber+2*squareSliceVolume)
					- squareTotalVolume;
				if(	(interaction==HardCore)&&
					((Lattice.GetOccupation(newLocationNumber)==OCCUPIEDPLUS)
					||(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDMINUS)))
					{return 0;}
				else
					{return 1;}
			}
			else
			{
				cout<<"ERROR! Boundary conditions unknown!";
				ASSERTperm(0); return 100;
			}
		}//end else if newSiteLocation=OnRightBoundaryInSpace
		else if (newSiteLocation==OnLeftBoundaryInSpace)
		{
			if(	(boundaryChoice==RhoInRhoEx)
				||(boundaryChoice==RhoInWall) )
			{
				double randomNumber = randomDouble01();
				if (randomNumber<=rhoUbInTot) {return 0;}
				else {return -1;}
			}
			else if (boundaryChoice==Periodic)
			{
				newLocationNumber = (newLocationNumber-2*squareSliceVolume)
						+ squareTotalVolume;
				if(	(interaction==HardCore)&&
					((Lattice.GetOccupation(newLocationNumber)==OCCUPIEDPLUS)
					||(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDMINUS)))
					{return 0;}
				else
					{return 1;}
			}
			else
			{
				cout<<" ERROR! Boundary conditions unknown!";
				ASSERTperm(0); return 100;
			}
		}//end else if newSiteLocation=OnLeftBoundaryInSpace
		else if (newSiteLocation==OnLeftBoundaryOnFilament)
		{
			if(	(boundaryChoice==RhoInRhoEx)
				||(boundaryChoice==RhoInWall) )
			{
				double randomNumber = randomDouble01();
				if (randomNumber<=rhoBInTot) {return 0;}
				else {return -1;}
			}
			else if (boundaryChoice==Periodic)
			{
				newLocationNumber = (newLocationNumber-2*squareSliceVolume)
						+ squareTotalVolume;
				if(	(interaction==HardCore)&&
					((Lattice.GetOccupation(newLocationNumber)==OCCUPIEDPLUS)
					||(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDMINUS)))
					{return 0;}
				else
					{return 1;}
			}//end else if newSiteLocation=OnLeftBoundaryOnFilament
			else
			{
				cout<<"ERROR! Boundary conditions unknown!";
				ASSERTperm(0); return 100;
			}
		}
		else
		{
			cout<<"ERROR in checkBoundary: Location not on boundary!";
			ASSERTperm(0);return 100;
		}
	};//end checkBoundary
//********************************************************************
// simple move
//********************************************************************
	void move(const int& newLocationNumber)
		// move when target site is accepted
	{
#ifdef DEBUG2
		cout<<"  move to "<<newLocationNumber;
#endif
		ASSERT((newLocationNumber>=0)
				&&(newLocationNumber<squareTotalVolume));
		ASSERT(	(Lattice.GetLocation(newLocationNumber)==OnFilament)
					||(Lattice.GetLocation(newLocationNumber)==InSpace));
#ifdef DEBUG
		if(interaction==HardCore)
			{ASSERT(Lattice.GetOccupation(newLocationNumber)==FREE);}
#endif
		Lattice.SetOccupation(itsLocationNumber,FREE);
		itsLocationNumber=newLocationNumber;
		if (itsDirection==PLUS)
		{
			Lattice.SetOccupation(itsLocationNumber,OCCUPIEDPLUS);
		}
		else
		{
			ASSERT(itsDirection==MINUS);
			Lattice.SetOccupation(itsLocationNumber,OCCUPIEDMINUS);
		}
	return;
	};//end move
}; // end class declaration
//**************************************************************
//**************************************************************

//**************************************************************
// statics
//**************************************************************

int Particle::totalNumberOfParticles = 0;
int Particle::numberOfPlusParticles = 0;
int Particle::numberOfMinusParticles = 0;
int Particle::destroyParticle = 0;
		// = 1 if motor has to be destroyed
int Particle::makeParticle = 0;
		// = 1 if motor has to be created
//**************************************************************
//**************************************************************

//**************************************************************
// Miscellaneous
//**************************************************************
void Particle::DisplaySettings()const
{
//cout<<"PARTICLE SETTINGS"<<endl;
cout<<"  arrayNumber: "<<itsLocationNumber
		<<", location: "<<Lattice.GetLocation(itsLocationNumber)
		<<", direction: "<<itsDirection<<endl;
return;
}//end Particle::DisplaySettings
