//******************************************************************
// update motors
//******************************************************************
//actualNumberOfMotors = Particle::totalNumberOfParticles;
//for (countMotors=0;countMotors<actualNumberOfMotors;countMotors++)


for (countMotors=0;countMotors<Particle::totalNumberOfParticles;countMotors++)
{
	randomInt=randomInteger(Particle::totalNumberOfParticles);
	actualLocationNumber = pMotor[randomInt]->GetLocationNumber();
	ASSERT((randomInt>=0)&&(randomInt<Particle::totalNumberOfParticles));
#ifdef DEBUG2
	cout<<"  Motor No "<<randomInt
		<<" at Location "<<pMotor[randomInt]->GetLocationNumber()<<endl;
#endif
	pMotor[randomInt]->hop();
	if(actualLocationNumber==793)
	{
		firstUpdated++;
		if (Lattice.GetOccupation(actualLocationNumber)==FREE){firstMoved++;}
	}
	if (Particle::destroyParticle)
		{
			//if (pMotor[actualMotorNumber]->GetLocationNumber()==finalPoint){destroyedFinals = destroyedFinals + 1;}
			destroyMotor(randomInt);
		}
} //end for motor loop
