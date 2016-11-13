//******************************************************************
// write motor configuration
//******************************************************************
if (countSeed==numberOfSeeds)
{writeMotorConf(MakeFileNames::ConfigFileOut);}

//******************************************************************
// free memory
//******************************************************************
actualNumberOfMotors=Particle::totalNumberOfParticles;
for(countMotors=0;countMotors<actualNumberOfMotors;
		countMotors++)
{
	delete pMotor[countMotors];
	pMotor[countMotors]=NULL;
}
ASSERT(Particle::totalNumberOfParticles==0);
for(countMotors=0;countMotors<numberOfMotorPointers;countMotors++)
	{ASSERT(pMotor[countMotors]==NULL);}

//******************************************************************
// time measurement
//******************************************************************
/*
time (&time2); // set time2 to current time (in sec since 1970)
timeUsed = difftime(time2,time1);
cout<<"time used: "<<timeUsed<<" sec = "<<timeUsed/60<<" min"<<endl;
*/
