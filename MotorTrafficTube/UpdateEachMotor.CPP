//******************************************************************
// update motors
//******************************************************************
// initialize motorsToUpdate
	numberOfMotorsToUpdate=Particle::totalNumberOfParticles;
	for(countMotors=0;countMotors<numberOfMotorsToUpdate;countMotors++)
		{motorsToUpdate[countMotors]=countMotors;}
	//cout<<"update each motor, measurement "<<actualNumberOfMeasurements
	//	<<", no of motorsToUpdate = "<<numberOfMotorsToUpdate<<endl;
//update motors
while (numberOfMotorsToUpdate>0)
{
	//cout<<"numberOfMotorsToUpdate "<<numberOfMotorsToUpdate<<endl;
	//for(countMotors=0;countMotors<numberOfMotorsToUpdate;countMotors++)
	//	{cout<<"  "<<motorsToUpdate[countMotors];}
	//cout<<endl;
	randomInt=randomInteger(numberOfMotorsToUpdate);
	//cout<<"numberOfMotors "<<numberOfMotorsToUpdate<<", randomInt = "
	//	<<randomInt<<", motorNumber "<<motorsToUpdate[randomInt]<<endl;
	ASSERT((randomInt>=0)&&(randomInt<numberOfMotorsToUpdate));
	actualMotorNumber=motorsToUpdate[randomInt];
	//if (pMotor[actualMotorNumber]->GetLocationNumber()==finalPoint){cout<<"  update final motor"<<endl;}
#ifdef DEBUG2
	cout<<"  Motor No "<<randomInt
		<<" at Location "<<pMotor[randomInt]->GetLocationNumber()<<endl;
#endif
	pMotor[actualMotorNumber]->hop();
	if (Particle::destroyParticle)
		{
			//if (pMotor[actualMotorNumber]->GetLocationNumber()==finalPoint){destroyedFinals = destroyedFinals + 1;}
			destroyMotor(actualMotorNumber);
		}
	else
		{
			for (countMotors=randomInt;countMotors<numberOfMotorsToUpdate;countMotors++)
			{
				motorsToUpdate[countMotors]=motorsToUpdate[countMotors+1];
			}
		}
	numberOfMotorsToUpdate = numberOfMotorsToUpdate - 1;
}//end while loop
