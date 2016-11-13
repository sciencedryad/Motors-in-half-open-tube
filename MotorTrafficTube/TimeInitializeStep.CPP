//******************************************************************
// initialize random number generator
//******************************************************************
randomInitialize(countSeed); 

//******************************************************************
// iINITIALIZE MOTORS
//******************************************************************
if (readConf==0)
{
	if(numberOfMotorsPlus+numberOfMotorsMinus>0.8*squareTotalVolume)
		{cout<<"ERROR! Too many motors in too small volume!"<<endl;ASSERTperm(0);}
// initialize plus motors
	for(countMotors=0;countMotors<numberOfMotorsPlus;countMotors++)
	{
		initialized=0;
		while(!initialized)
		{
			randomInt = randomInteger(squareTotalVolume);
			if (Lattice.GetOccupation(randomInt)==FREE)
			{
				actualLocation=Lattice.GetLocation(randomInt);
				if (initialNoMotorsOnFilament==0) //random update
				{
					if ((actualLocation==InSpace)||(actualLocation==OnFilament) )
					{
						pMotor[countMotors]=new Particle(PLUS,randomInt,0);
							//creates plus motor at randomInt with internal clock 0
						if (pMotor[countMotors]==NULL)
							{cout<<"ERROR! No memory!"<<endl;ASSERTperm(0);}
						initialized=1;
					}//end if actualLocation
				}//end if initialNoMotorsOnFilament==0
				else //random update, but no motors on filament
					ASSERT(initialNoMotorsOnFilament==1);
					if (actualLocation==InSpace)
					{
						pMotor[countMotors]=new Particle(PLUS,randomInt,0);
							//creates plus motor at randomInt with internal clock 0
						if (pMotor[countMotors]==NULL)
							{cout<<"ERROR! No memory!"<<endl;ASSERTperm(0);}
						initialized=1;
					}//end if actualLocation
			}//end if Lattice.GetOccupation
		}//end while !initialized
		#ifdef DEBUG2
			pMotor[countMotors]->DisplaySettings();
		#endif
		ASSERT((Lattice.GetOccupation(pMotor[countMotors]->GetLocationNumber())==OCCUPIEDPLUS)
			||(Lattice.GetOccupation(pMotor[countMotors]->GetLocationNumber())==OCCUPIEDMINUS));
	}//end for countMotors
// initialize minus motors
	for(countMotors=numberOfMotorsPlus;
		countMotors<numberOfMotorsPlus+numberOfMotorsMinus;countMotors++)
	{
		initialized=0;
		while(!initialized)
		{
			randomInt = randomInteger(squareTotalVolume);
			if (Lattice.GetOccupation(randomInt)==FREE)
			{
				actualLocation=Lattice.GetLocation(randomInt);
				if (initialNoMotorsOnFilament==0) //random update
				{
					if ((actualLocation==InSpace)||(actualLocation==OnFilament) )
					{
						pMotor[countMotors]=new Particle(MINUS,randomInt,0);
							//creates plus motor at randomInt with internal clock 0
						if (pMotor[countMotors]==NULL)
							{cout<<"ERROR! No memory!"<<endl;ASSERTperm(0);}
						initialized=1;
					}//end if actualLocation
				}//end if initialNoMotorsOnFilament==0
				else //random update, but no motors on filament
					if (actualLocation==InSpace)
					{
						pMotor[countMotors]=new Particle(MINUS,randomInt,0);
							//creates plus motor at randomInt with internal clock 0
						if (pMotor[countMotors]==NULL)
							{cout<<"ERROR! No memory!"<<endl;ASSERTperm(0);}
						initialized=1;
					}//end if actualLocation
			}//end if Lattice.GetOccupation
		}//end while !initialized
		#ifdef DEBUG2
			pMotor[countMotors]->DisplaySettings();
		#endif
		ASSERT((Lattice.GetOccupation(pMotor[countMotors]->GetLocationNumber())==OCCUPIEDPLUS)
			||(Lattice.GetOccupation(pMotor[countMotors]->GetLocationNumber())==OCCUPIEDMINUS));
	}//end for countMotors
// set rest motor pointers to NULL
	for(countMotors=Particle::totalNumberOfParticles;countMotors<numberOfMotorPointers;countMotors++)
		{pMotor[countMotors] = NULL;} //set all other motor pointers to NULL
}//end if readConf
else //(readConf!=0)
{
	//cout<<"read motor conf"<<endl;
	readMotorConf(MakeFileNames::ConfigFileIn);
}//end else (readConf!=0)
