//******************************************************************
//******************************************************************
// INITIALIZATION
//******************************************************************
//******************************************************************

//******************************************************************
// test parameters
//******************************************************************
//cout<<"PARAMETER-CHECK"<<endl;
//ASSERTperm(seed>=0);
ASSERTperm(numberOfMeasurements>=1);
ASSERTperm(numberOfMCSteps>=1);
ASSERTperm(totalNumberOfMCSteps>=1);
ASSERTperm(numberOfMCSteps<=numberOfMeasurements);
ASSERTperm(measureInterval>=1);
ASSERTperm(measureInterval<=numberOfMeasurements);
ASSERTperm(tubeLength>=0);
ASSERTperm(tubeRadiusY>=0);
ASSERTperm(tubeRadiusZ>=0);
ASSERTperm(squareLengthX>=0);
ASSERTperm(squareTransverseLengthY>=0);
ASSERTperm(squareTransverseLengthZ>=0);
ASSERTperm(squareSliceVolume>=0);
ASSERTperm(squareTotalVolume>=0);
ASSERTperm(numberOfMotorsPlus>=0);
ASSERTperm(numberOfMotorsMinus>=0);
ASSERTperm((numberOfMotorsPlus+numberOfMotorsMinus)
	<=(0.8*Lattice.GetTotalVolume()));
ASSERTperm(numberOfMotorPointers
	>=(numberOfMotorsPlus+numberOfMotorsMinus));
ASSERTperm(numberOfNeighbours==6);
ASSERTperm((epsilon>=0)&&(epsilon<=1));
ASSERTperm((pi_det>=0)&&(pi_det<=1));
ASSERTperm((pi_ad>=0)&&(pi_ad<=1));
ASSERTperm((beta>=0)&&(beta<=1));
ASSERTperm((gammaC>=0)&&(gammaC<=1));
ASSERTperm((alpha>=0)&&(alpha<=1));
ASSERTperm((numberOfNeighbours*pdiff<=1.001)
				&&(numberOfNeighbours*pdiff>=0.999));
ASSERTperm((alpha+beta+gammaC+(numberOfNeighbours-2)*pi_det<=1.001)
				&&(alpha+beta+gammaC+(numberOfNeighbours-2)*pi_det>=0.999));
//ASSERTperm((rhoIn>=0)&&(rhoEx<=1));
ASSERTperm((rhoBInPlus>=0)&&(rhoBInPlus<=1));
ASSERTperm((rhoBInMinus>=0)&&(rhoBInMinus<=1));
ASSERTperm((rhoBExPlus>=0)&&(rhoBExPlus<=1));
ASSERTperm((rhoBExMinus>=0)&&(rhoBExMinus<=1));
ASSERTperm((rhoBInTot>=0)&&(rhoBInTot<=1));
ASSERTperm(tau_b>0);

//******************************************************************
// initialize random number generator
//******************************************************************
randomInitialize(seed);

//******************************************************************
// initialize filenames
//******************************************************************
MakeFileNames FileNames;
FileNames.makeNames();

//******************************************************************
// initialize globals
//******************************************************************
for(i=0;i<tubeLength;i++)
{
	rho_b[i]=0;
	rho_ub[i]=0;
	rho_b_plus[i]=0;
	rho_ub_plus[i]=0;
	rho_b_minus[i]=0;
	rho_ub_minus[i]=0;
	for (r=0;r<tubeRadiusY;r++)
	{
		rho_ub_radius[i][r]=0;
		rho_ub_plus_radius[i][r]=0;
		rho_ub_minus_radius[i][r]=0;
	}
}
for(i=0;i<tubeLength-1;i++)
{
	j_b[i]=0;
	j_ub[i]=0;
	j_tot[i]=0;
	j_bEvents[i]=0;
	j_ubEvents[i]=0;
	j_totEvents[i]=0;
	j_b_plusEvents[i]=0;
	j_ub_plusEvents[i]=0;
	j_tot_plusEvents[i]=0;
	j_b_minusEvents[i]=0;
	j_ub_minusEvents[i]=0;
	j_tot_minusEvents[i]=0;
	for (r=0;r<tubeRadiusY;r++)
	{
		j_ub_radiusEvents[i][r]=0;
		j_ub_plus_radiusEvents[i][r]=0;
		j_ub_minus_radiusEvents[i][r]=0;
	}
}

//******************************************************************
// initialize time measurement
//******************************************************************
time (&time1); // set time1 to current time (in sec since 1970)

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
				if ( (actualLocation==InSpace)
					||(actualLocation==OnFilament) )
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
			cout<<"  motor no "<<countMotors;
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
				if ( (actualLocation==InSpace)
					||(actualLocation==OnFilament) )
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
			cout<<"  motor no "<<countMotors;
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

//******************************************************************

//******************************************************************
// WRITE PARAMETERS to parameterFile
//******************************************************************

ofstream foutPara(MakeFileNames::parameterFile);
	if(!foutPara) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutPara<<"//GlobalGeometry TUBE"<<";"<<endl;
	foutPara<<"  tubeLength = "<<tubeLength
			<<"; tubeRadius = "<<tubeRadiusY
			<<"; boundaryChoice = "<<boundaryChoice
			<<"; squareTotalVolume = "<<squareTotalVolume<<";"<<endl;
	foutPara<<"  sliceVolume = "<<Lattice.GetSliceVolume()
			<<"; totalVolume = "<<Lattice.GetTotalVolume()<<";"<<endl;
	foutPara<<"  numberOfMotorsPlus = "<<numberOfMotorsPlus
			<<"; numberOfMotorsMinus = "<<numberOfMotorsMinus
			<<"; numberOfMotorPointers = "<<numberOfMotorPointers
			<<"; total number of motors = "
			<<numberOfMotorsPlus+numberOfMotorsMinus<<endl;
	foutPara<<"  interaction = "<<interaction
			<<"; numberOfNeighbours = "<<numberOfNeighbours<<";"
			<<"; randomNumberSeed = "<<seed<<";"<<endl;
	foutPara<<"  pdiff = "<<pdiff
			<<"; epsilon = "<<epsilon
			<<"; pi_det = "<<pi_det
			<<"; pi_ad = "<<pi_ad
			<<"; beta = "<<beta
			<<"; gammaC = "<<gammaC
			<<"; alpha = "<<alpha<<";"<<endl;
	foutPara<<"  tau_b = "<<tau_b<<endl;
	foutPara<<"  start configuration: ";
	if (readConf){foutPara<<"from configIn"<<endl;}else{foutPara<<" random"<<endl;}
	foutPara<<"  rhoBInPlus = "<<rhoBInPlus
			<<", RhoBInMinus = "<<rhoBInMinus
			<<", rhoBInTot = "<<rhoBInTot
			<<", rhoBExPlus = "<<rhoBExPlus
			<<", rhoBExMinus = "<<rhoBExMinus
			<<", rhoBExTot = "<<rhoBExTot<<";"<<endl;
	foutPara<<"  rhoUbInPlus = "<<rhoUbInPlus
			<<", rhoUbInMinus = "<<rhoUbInMinus
			<<", rhoUbInTot = "<<rhoUbInTot
			<<"; rhoUbExPlus = "<<rhoUbExPlus
			<<", rhoUbExMinus = "<<rhoUbExMinus
			<<", rhoUbExTot = "<<rhoUbExTot<<";"<<endl;
	foutPara<<"equilibrationSteps = "<<equilibrationSteps
			<<"; totalNumberOfMCSteps = "<<totalNumberOfMCSteps<<endl;
	foutPara<<"numberOfMeasurements = "<<numberOfMeasurements
			<<"; numberOfMCSteps = "<<numberOfMCSteps
			<<"; measureInterval = "<<measureInterval<<endl;
foutPara.close();

//******************************************************************
// WRITE PARAMETERS on screen
//******************************************************************

	cout<<"//GlobalGeometry TUBE"<<";"<<endl;
	cout<<"  tubeLength = "<<tubeLength
		<<"; tubeRadius = "<<tubeRadiusY
		<<"; boundaryChoice = ";DisplayBoundaries(boundaryChoice);
	cout<<"("<<boundaryChoice<<")"
		<<"; squareTotalVolume = "<<squareTotalVolume<<";"<<endl;
	cout<<"  sliceVolume = "<<Lattice.GetSliceVolume()
		<<"; totalVolume = "<<Lattice.GetTotalVolume()
		<<"; numberOfFilamentSites = "<<Lattice.GetNumberOfFilamentSites()
		<<"; numberOfSpaceSites = "<<Lattice.GetNumberOfSpaceSites()<<endl;
	cout<<"  numberOfMCSteps = "<<numberOfMCSteps
		<<"; randomNumberSeed = "<<seed<<endl;
	cout<<"  numberOfMotorsPlus = "<<numberOfMotorsPlus
		<<"; numberOfMotorsMinus = "<<numberOfMotorsMinus
		<<"; numberOfMotorPointers = "<<numberOfMotorPointers
		<<"; total number of motors = "<<numberOfMotorsPlus+numberOfMotorsMinus<<endl;
	cout<<"  interaction = ";DisplayInteractions(interaction); cout<<"("<<interaction<<")"
		<<"; numberOfNeighbours = "<<numberOfNeighbours<<";"<<endl;
	cout<<"  pdiff = "<<pdiff
		<<"; epsilon = "<<epsilon
		<<"; pi_det = "<<pi_det
		<<"; pi_ad = "<<pi_ad
		<<"; beta = "<<beta
		<<"; gammaC = "<<gammaC
		<<"; alpha = "<<alpha<<";"<<endl;
	cout<<"  tau_b = "<<tau_b<<endl;
	cout<<"  start configuration: ";
	if (readConf){cout<<"from configIn"<<endl;}else{cout<<" random"<<endl;}
	cout<<"  rhoBInPlus = "<<rhoBInPlus
		<<"; rhoBInMinus = "<<rhoBInMinus
		<<", rhoBInTot = "<<rhoBInTot
		<<", RhoBExPlus = "<<rhoBExPlus
		<<", rhoBExMinus = "<<rhoBExMinus
		<<", rhoBExTot = "<<rhoBExTot<<";"<<endl;
	cout<<"  rhoUbInPlus = "<<rhoUbInPlus
		<<", rhoUbInMinus = "<<rhoUbInMinus
		<<", rhoUbInTot = "<<rhoUbInTot
		<<"; rhoUbExPlus = "<<rhoUbExPlus
		<<", rhoUbExMinus = "<<rhoUbExMinus
		<<", rhoUbExTot = "<<rhoUbExTot<<";"<<endl;
	cout<<"equilibrationSteps = "<<equilibrationSteps
		<<"; totalNumberOfMCSteps = "<<totalNumberOfMCSteps<<endl;
	cout<<"numberOfMeasurements = "<<numberOfMeasurements
		<<"; numberOfMCSteps = "<<numberOfMCSteps
		<<"; measureInterval = "<<measureInterval<<endl;

//******************************************************************
// OPEN RESULT FILES
//******************************************************************

ofstream foutCorrRho_b(MakeFileNames::CorrRho_b);
	if(!foutCorrRho_b) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrJ_b(MakeFileNames::CorrJ_b);
	if(!foutCorrJ_b) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrJ_b_tot(MakeFileNames::CorrJ_b_tot);
	if(!foutCorrJ_b_tot) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrRho_b_tot(MakeFileNames::CorrRho_b_tot);
	if(!foutCorrRho_b_tot) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrRho_ub_tot(MakeFileNames::CorrRho_ub_tot);
	if(!foutCorrRho_ub_tot) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrN(MakeFileNames::CorrN);
	if(!foutCorrN) {cout<<"Unable to open file! ";ASSERTperm(0);}

//******************************************************************