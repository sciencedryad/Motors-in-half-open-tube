//******************************************************************
//******************************************************************
// INITIALIZATION
//******************************************************************
//******************************************************************

//******************************************************************
// test parameters
//******************************************************************
ASSERTperm(numberOfMeasurements>=1);
ASSERTperm(numberOfMCSteps>=1);
ASSERTperm(totalNumberOfMCSteps>=1);
ASSERTperm(numberOfMCSteps<=numberOfMeasurements);
ASSERTperm(measureInterval>=1);
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

ASSERTperm(totalTime>0);
ASSERTperm(numberOfSeeds>0);
ASSERTperm(every>0);

//******************************************************************
// initialize filenames
//******************************************************************
MakeFileNames FileNames;
FileNames.makeNames();

//******************************************************************
// initialize globals
//******************************************************************
for(countTime=0;countTime<totalTime;countTime++)
{
	for(i=0;i<tubeLength;i++)
	{
		rho_b_Time[i][countTime]=0;
		rho_ub_Time[i][countTime]=0;
	}
	for(i=0;i<tubeLength-1;i++)
	{
		j_b_Time[i][countTime]=0;
		j_ub_Time[i][countTime]=0;
	}
	for(i=0;i<tubeRadiusY;i++)
	{
		rho_ub_radius_Time[i][countTime]=0;
	}
	rho_b_tot_Time[countTime]=0;
	rho_ub_tot_Time[countTime]=0;
	j_b_tot_Time[countTime]=0;
	j_ub_tot_Time[countTime]=0;
	motorN[countTime]=0;
	jamLength[countTime]=0;
}//end for countTime

//------------------------------------------------------------------
// initialize time measurement
//------------------------------------------------------------------
time (&time1); // set time1 to current time (in sec since 1970)

//******************************************************************
// WRITE PARAMETERS on screen
//******************************************************************
	cout<<"Time Motor Simulation"<<endl;
	cout<<"  number of random number seeds = "<<numberOfSeeds
			<<"; totalTime = "<<totalTime<<endl;
	cout<<"  GlobalGeometry TUBE"<<"; every = "<<every<<endl;
	cout<<"  tubeLength = "<<tubeLength
			<<"; tubeRadius = "<<tubeRadiusY
			<<"; boundaryChoice = "<<boundaryChoice
			<<"; squareTotalVolume = "<<squareTotalVolume<<";"<<endl;
	cout<<"  sliceVolume = "<<Lattice.GetSliceVolume()
			<<"; totalVolume = "<<Lattice.GetTotalVolume()
			<<"; numberOfFilamentSites = "<<Lattice.GetNumberOfFilamentSites()
			<<"; numerOfSpaceSites = "<<Lattice.GetNumberOfSpaceSites()<<endl;
	cout<<"  numberOfMCSteps = "<<numberOfMCSteps
			<<"; randomNumberSeedNumber = "<<numberOfSeeds<<endl;
	cout<<"  numberOfMotorsPlus = "<<numberOfMotorsPlus
			<<"; numberOfMotorsMinus = "<<numberOfMotorsMinus
			<<"; numberOfMotorPointers = "<<numberOfMotorPointers
			<<"; total number of motors = "
			<<numberOfMotorsPlus+numberOfMotorsMinus<<endl;
	cout<<"  interaction = "<<interaction
			<<"; numberOfNeighbours = "<<numberOfNeighbours<<";"<<endl;
	cout<<"  pdiff = "<<pdiff
			<<"; epsilon = "<<epsilon
			<<"; pi_det = "<<pi_det
			<<"; pi_ad = "<<pi_ad
			<<"; beta = "<<beta
			<<"; gammaC = "<<gammaC
			<<"; alpha = "<<alpha<<";"<<endl;
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
// WRITE PARAMETERS to parameterFile
//******************************************************************

ofstream foutPara(MakeFileNames::parameterFile);
	if(!foutPara) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutPara<<"Time Simulation totalTime = "<<totalTime<<endl;
	foutPara<<"  number of random number seeds = "<<numberOfSeeds
					<<"; write every configuration = "<<every<<endl;
	foutPara<<"  GlobalGeometry TUBE"<<";"<<endl;
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
			<<"; randomNumberSeeds = "<<numberOfSeeds<<";"<<endl;
	foutPara<<"  pdiff = "<<pdiff
			<<"; epsilon = "<<epsilon
			<<"; pi_det = "<<pi_det
			<<"; pi_ad = "<<pi_ad
			<<"; beta = "<<beta
			<<"; gammaC = "<<gammaC
			<<"; alpha = "<<alpha<<";"<<endl;
	foutPara<<"  rhoBInPlus = "<<rhoBInPlus
			<<", RhoBInMinus = "<<rhoBInMinus
			<<", rhoBInTot = "<<rhoBInTot
			<<", rhoBExPlus = "<<rhoBExPlus
			<<", rhoBExMinus = "<<rhoBExMinus
			<<", rhoBExTot = "<<rhoBExTot<<";"<<endl;
	foutPara<<"; rhoUbInPlus = "<<rhoUbInPlus
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
