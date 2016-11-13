//=======================================================================================
//=======================================================================================
// UPDATE MOTORS AND BOUNDARIES
// Monte Carlo update of motors and boundaries on equal footing (1 MC step)
//=======================================================================================
//=======================================================================================

//determine actualNumberOfMotors to be updated (including boundary motors)
	if ((boundaryChoice==WallWall)||(boundaryChoice==Periodic))
		// for non-open boundary conditions, i.e. no boundaries to be updated
		{actualNumberOfMotors = Particle::totalNumberOfParticles;}
	else if ((boundaryChoice==RhoInWall)||(boundaryChoice==WallRhoEx))
		// one boundary
		{actualNumberOfMotors = Particle::totalNumberOfParticles + squareSliceVolume;}
	else	//two boundaries
	{
		ASSERT(boundaryChoice==RhoInRhoEx);
		actualNumberOfMotors = Particle::totalNumberOfParticles + squareSliceVolume + squareSliceVolume;
	}
	//cout<<"actualNumberOfMotors = "<<actualNumberOfMotors<<endl;

//=======================================================================================
// LOOP OVER MOTORS
//=======================================================================================
for (countMotors=0;countMotors<actualNumberOfMotors;countMotors++)
{
//determine actualNumberOfMotors to be updated (including boundary motors)
	if ((boundaryChoice==RhoInWall)||(boundaryChoice==WallRhoEx))
		{actualNumberOfMotors = Particle::totalNumberOfParticles + squareSliceVolume;}
	else if (boundaryChoice==RhoInRhoEx)
		{actualNumberOfMotors = Particle::totalNumberOfParticles + squareSliceVolume + squareSliceVolume;}
	#ifdef DEBUG
	else
	{
		ASSERT((boundaryChoice==WallWall)||(boundaryChoice==Periodic));
		ASSERT(actualNumberOfMotors==Particle::totalNumberOfParticles)
		//motor number does not change for these boundary conditions, and there are not boundaries to update
	}
	#endif
	// now (countMotors=0;countMotors<actualNumberOfMotors;countMotors++) represents:
	//	countMotors=0 ... countMotors<Particle::totalNumberOfParticles:
	//		motors in tube
	//	countMotors=Particle::totalNumberOfParticles
	//		... Particle::totalNumberOfParticles+SquareSliceVolume:
	//		motors on left boundary if RhoInRhoEx or RhoInWall,
	//		motors on right boundary if WallRhoEx
	//	countMotors=Particle::totalNumberOfParticles+squareSliceVolume
	//		... Particle::totalNumberOfParticles+2*squareSliceVolume:
	//		motors on right boundary if RhoInRhoEx
//draw random number
	randomInt = randomInteger(actualNumberOfMotors);
	#ifdef DEBUG
		ASSERT(randomInt>=0);ASSERT(randomInt<actualNumberOfMotors);
		if((boundaryChoice==Periodic)||(boundaryChoice==WallWall))
			{ASSERT(actualNumberOfMotors==Particle::totalNumberOfParticles);}
	#endif
//=======================================================================================
// UPDATE TUBE MOTORS
//=======================================================================================
if (randomInt<Particle::totalNumberOfParticles) // tube motors
{
	ASSERT((randomInt>=0)&&(randomInt<Particle::totalNumberOfParticles));
	actualLocationNumber = pMotor[randomInt]->GetLocationNumber();
	#ifdef DEBUG2
		cout<<"  Motor No "<<randomInt
			<<" at Location "<<pMotor[randomInt]->GetLocationNumber()<<endl;
	#endif
	pMotor[randomInt]->hop();
	if (Particle::destroyParticle)
	{
		destroyMotor(randomInt);
	}
}//end if randomInt<Particle::totalNumberOfParticles
//=======================================================================================
// UPDATE FIRST BOUNDARY
//=======================================================================================
else  if (randomInt<Particle::totalNumberOfParticles+squareSliceVolume)
{
	ASSERT(randomInt>=Particle::totalNumberOfParticles);
	ASSERT(randomInt<Particle::totalNumberOfParticles+squareSliceVolume);
	if ((boundaryChoice==RhoInRhoEx)||(boundaryChoice==RhoInWall))
	{
		actualLocationNumber = randomInt - Particle::totalNumberOfParticles;
			//location on left boundary
		updateLeftBoundary(actualLocationNumber);
	}//end if boundaryChoice==RhoInRhoEx
	else
	{
		ASSERT(boundaryChoice==WallRhoEx);
		actualLocationNumber = squareTotalVolume - (randomInt-Particle::totalNumberOfParticles) - 1;
		updateRightBoundary(actualLocationNumber);
	}//end else
}//end else if
//=======================================================================================
// UPDATE SECOND BOUNDARY
//=======================================================================================
else
{
	ASSERT(randomInt>=Particle::totalNumberOfParticles+squareSliceVolume);
	ASSERT(randomInt<(Particle::totalNumberOfParticles+squareSliceVolume+squareSliceVolume));
	ASSERT(boundaryChoice==RhoInRhoEx);
	actualLocationNumber = squareTotalVolume
		- (randomInt-Particle::totalNumberOfParticles-squareSliceVolume) - 1;
			//location on right boundary
	updateRightBoundary(actualLocationNumber);
}//end else
} //end for countMotors loop
