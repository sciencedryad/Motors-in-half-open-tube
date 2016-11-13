//******************************************************************
// write motor configuration
//******************************************************************
writeMotorConf(MakeFileNames::ConfigFileOut);

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
// FINAL MEASUREMENT
//******************************************************************
ASSERTperm(actualNumberOfMeasurements>0);
ASSERTperm(totalNumberOfMCSteps==numberOfMeasurements*numberOfMCSteps);
ASSERTperm(actualNumberOfMeasurements==numberOfMeasurements);

#ifdef DEBUG2
	cout<<endl;
	cout<<"FINAL MEASUREMENT numberOfMeasurements = "
			<<actualNumberOfMeasurements<<endl;
	cout<<"rho_b  ";
	for(i=0;i<tubeLength;i++)
		{cout<<rho_b[i]<<"  ";}
	cout<<endl;
	cout<<"rho_ub ";
	for(i=0;i<tubeLength;i++)
		{ cout<<rho_ub[i]<<"  ";}
	cout<<endl;
#endif

// normalize densities
for(i=0;i<tubeLength;i++)
{
	rho_b[i] = rho_b[i]/actualNumberOfMeasurements;
	rho_b_plus[i] = rho_b_plus[i]/actualNumberOfMeasurements;
	rho_b_minus[i] = rho_b_minus[i]/actualNumberOfMeasurements;
	ASSERT((rho_b[i]>=0)&&(rho_b[i]<=1));
	ASSERT((rho_b_plus[i]>=0)&&(rho_b_plus[i]<=1));
	ASSERT((rho_b_minus[i]>=0)&&(rho_b_minus[i]<=1));
	if(Lattice.GetSliceVolume()-1>0)
	{
		rho_ub[i] = rho_ub[i]
			/actualNumberOfMeasurements;
		rho_ub_plus[i] = rho_ub_plus[i]
			/actualNumberOfMeasurements;
		rho_ub_minus[i] = rho_ub_minus[i]
			/actualNumberOfMeasurements;
/*		rho_ub[i] = rho_ub[i]
			/actualNumberOfMeasurements/(Lattice.GetSliceVolume()-1);
		rho_ub_plus[i] = rho_ub_plus[i]
			/actualNumberOfMeasurements/(Lattice.GetSliceVolume()-1);
		rho_ub_minus[i] = rho_ub_minus[i]
			/actualNumberOfMeasurements/(Lattice.GetSliceVolume()-1);
		ASSERT((rho_ub[i]>=0)&&(rho_ub[i]<=1));*/
	}
	else
	{
		rho_ub[i] = 0;
		rho_ub_plus[i] = 0;
		rho_ub_minus[i] = 0;
	}
	for (r=0;r<tubeRadiusY;r++)
	{
		rho_ub_radius[i][r] = rho_ub_radius[i][r]/actualNumberOfMeasurements;
		rho_ub_plus_radius[i][r] = rho_ub_plus_radius[i][r]/actualNumberOfMeasurements;
		rho_ub_minus_radius[i][r] = rho_ub_minus_radius[i][r]/actualNumberOfMeasurements;
	}
}// end for i

//normalize currents
for(i=0;i<(tubeLength-1);i++)
{
	j_b[i] = j_b[i]/actualNumberOfMeasurements;
	j_bEvents[i] = j_bEvents[i]/totalNumberOfMCSteps;
	j_tot[i] = j_tot[i]/actualNumberOfMeasurements/Lattice.GetSliceVolume();
	j_totEvents[i] = j_totEvents[i]/totalNumberOfMCSteps/(Lattice.GetSliceVolume());
	j_b_plusEvents[i] = j_b_plusEvents[i]/totalNumberOfMCSteps;
	j_b_minusEvents[i] = j_b_minusEvents[i]/totalNumberOfMCSteps;
	if(Lattice.GetSliceVolume()>1)
	{
		j_ub[i] = j_ub[i]/actualNumberOfMeasurements;///(Lattice.GetSliceVolume()-1);
		j_ubEvents[i] = j_ubEvents[i]/totalNumberOfMCSteps;///(Lattice.GetSliceVolume()-1);
		j_ub_plusEvents[i] = j_ub_plusEvents[i]/totalNumberOfMCSteps;///(Lattice.GetSliceVolume()-1);
		j_ub_minusEvents[i] = j_ub_minusEvents[i]/totalNumberOfMCSteps;///(Lattice.GetSliceVolume()-1);
	}
	else
	{
		j_ub[i] = 0;
		j_ubEvents[i] =0;
		j_ub_plusEvents[i] =0;
		j_ub_minusEvents[i] =0;
	}
}// end for i

//calculate mean number of particles
meanNumberOfMotors = meanNumberOfMotors/actualNumberOfMeasurements;
meanNumberOfPlusMotors = meanNumberOfPlusMotors/actualNumberOfMeasurements;
meanNumberOfMinusMotors = meanNumberOfMinusMotors/actualNumberOfMeasurements;

#ifdef DEBUG2
	cout<<"normalized"<<endl;
	cout<<"rho_b  ";
	for(i=0;i<tubeLength;i++)
		{cout.precision(3);cout.width(6);cout.setf(ios::showpoint|ios::fixed);
			cout<<rho_b[i];}
	cout<<endl;
	cout<<"rho_ub ";
	for(i=0;i<tubeLength;i++)
		{cout.precision(3);cout.width(6);cout.setf(ios::showpoint|ios::fixed);
			cout<<rho_ub[i];}
	cout<<endl;
	cout<<"j_b    ";
	for(i=0;i<tubeLength-1;i++)
		{cout.precision(3);cout.width(6);cout.setf(ios::showpoint|ios::fixed);
			cout<<j_b[i];}
	cout<<endl;
	cout<<"j_ub   ";
	for(i=0;i<tubeLength-1;i++)
		{cout.precision(3);cout.width(6);cout.setf(ios::showpoint|ios::fixed);
			cout<<j_ub[i];}
	cout<<endl;
	cout<<"J_tot  ";
	for(i=0;i<tubeLength-1;i++)
		{cout.precision(3);cout.width(6);cout.setf(ios::showpoint|ios::fixed);
			cout<<(j_tot[i]);}
	cout<<endl;
#endif

//******************************************************************
// measure time & output
//******************************************************************
actualSlice=Lattice.GetXSlice(chosenPoint);
ASSERT((actualSlice>=0)&&(actualSlice<tubeLength));
actualRho_b = rho_b[actualSlice];
actualRho_ub = rho_ub[actualSlice]/(Lattice.GetSliceVolume()-1);
if ((actualRho_b!=0)&&(actualRho_ub!=1))
	{absorptionEqui = actualRho_ub*(1-actualRho_b)/(actualRho_b)*(1-actualRho_ub);}
else  {absorptionEqui = 0;}
cout<<"  densities at chosen Point: rho_b = "<<actualRho_b
		<<", rho_ub = "<<actualRho_ub<<endl;
cout<<"  adsorption equilibrium: rho_ub(1-rho_b)/(rho_b)(1-rho_ub) = "
		<<absorptionEqui
		<<", epsilon/pi_ad = "<<epsilon/pi_ad<<endl;
cout<<"  mean number of motors = "<<meanNumberOfMotors
	<<", mean number of plus motors = "<<meanNumberOfPlusMotors
	<<", mean number of minus motors = "<<meanNumberOfMinusMotors
	<<", end number of motors = "<<actualNumberOfMotors<<endl;
cout<<"output files written to directory "
		<<MakeFileNames::folder<<endl;
time (&time2); // set time2 to current time (in sec since 1970)
timeUsed = difftime(time2,time1);
cout<<"used time: "<<timeUsed<<" sec"
		<<" = "<<timeUsed/60<<" min"
		<<" = "<<timeUsed/3600<<" h"<<endl;

//******************************************************************
// WRITE TO FILES
//******************************************************************

// write densities
ofstream foutRho(MakeFileNames::ResRho);
	if(!foutRho) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutRho<<"# x   rho_b   rho_b_plus   rho_b_minus   rho_ub   rho_ub_plus   rho_ub_minus"<<endl;
	/*if ((boundaryChoice==RhoInRhoEx)||(boundaryChoice==RhoInWall))\
	{
			foutRho.width(6);
			foutRho.setf(ios::left);
		foutRho<<0;
			foutRho.precision(6);
			foutRho.setf(ios::showpoint|ios::fixed);
		foutRho<<rhoIn;
			foutRho<<"   ";
			foutRho.precision(6);
			foutRho.setf(ios::showpoint|ios::fixed);
		foutRho<<rhoInUnbound<<endl;
	}*/
	for(i=0;i<tubeLength;i++)
		{
			foutRho.width(6);
			foutRho.setf(ios::left);
		foutRho<<i+1;
			foutRho.precision(8);
			foutRho.setf(ios::showpoint|ios::fixed);
		foutRho<<rho_b[i];
			foutRho<<"   ";
			foutRho.precision(8);
			foutRho.setf(ios::showpoint|ios::fixed);
		foutRho<<rho_b_plus[i];
			foutRho<<"   ";
			foutRho.precision(8);
			foutRho.setf(ios::showpoint|ios::fixed);
		foutRho<<rho_b_minus[i];
			foutRho<<"   ";
			foutRho.precision(8);
			foutRho.setf(ios::showpoint|ios::fixed);
		foutRho<<rho_ub[i];
			foutRho<<"   ";
			foutRho.precision(8);
			foutRho.setf(ios::showpoint|ios::fixed);
		foutRho<<rho_ub_plus[i];
			foutRho<<"   ";
			foutRho.precision(8);
			foutRho.setf(ios::showpoint|ios::fixed);
		foutRho<<rho_ub_minus[i]<<endl;
		}//end for i
	/*if ((boundaryChoice==RhoInRhoEx)||(boundaryChoice==WallRhoEx))
	{
			foutRho.width(6);
			foutRho.setf(ios::left);
		foutRho<<i+1;
			foutRho.precision(5);
			foutRho.setf(ios::showpoint|ios::fixed);
		foutRho<<rhoEx;
			foutRho<<"   ";
			foutRho.precision(6);
			foutRho.setf(ios::showpoint|ios::fixed);
		foutRho<<rhoExUnbound<<endl;
	}*/
foutRho.close();

// write radial densities
foutRho.open(MakeFileNames::ResRhoRadius);
	if(!foutRho) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutRho<<"# x   rho_ub[r,x]"<<endl;
	for(i=0;i<tubeLength;i++)
	{
			foutRho.width(6);
			foutRho.setf(ios::left);
		foutRho<<i+1;
		for (r=0;r<tubeRadiusY;r++)
		{
				foutRho.precision(6);
				foutRho.setf(ios::showpoint|ios::fixed);
			foutRho<<rho_ub_radius[i][r];
				foutRho<<"  ";
		}//end for r
		foutRho<<endl;
	}//end for i
foutRho.close();


// write currents
ofstream foutJ(MakeFileNames::ResJ);
	if(!foutJ) {cout<<"Unable to open file! ";ASSERTperm(0);}
//ofstream foutJ_ub(MakeFileNames::ResJ_ub);
//	if(!foutJ_ub) {cout<<"Unable to open file! ";ASSERTperm(0);}
//ofstream foutJ_tot(MakeFileNames::ResJ_tot);
//	if(!foutJ_tot) {cout<<"Unable to open file! ";ASSERTperm(0);}
ofstream foutJ_Events(MakeFileNames::ResJ_Events);
	if(!foutJ_Events) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutJ_Events<<"# x    j_b        j_b_plus   j_b_minus   j_ub      j_ub_plus   j_ub_minus  j_tot"<<endl;
	for(i=0;i<(tubeLength-1);i++)
		{
			foutJ.width(6); foutJ.setf(ios::left);
		foutJ<<i;
			foutJ.precision(4);
			foutJ.setf(ios::showpoint|ios::fixed);
		foutJ<<j_b[i];///(1-gammaC)<<endl;///alpha<<endl;
			foutJ<<"   ";
			foutJ.precision(4);
			foutJ.setf(ios::showpoint|ios::fixed);
		foutJ<<j_ub[i];
			foutJ<<"   ";
			foutJ.precision(4);
			foutJ.setf(ios::showpoint|ios::fixed);
		foutJ<<j_tot[i]<<endl;
			foutJ_Events.width(8);
			foutJ_Events.setf(ios::left);
		foutJ_Events<<i;
			foutJ_Events.precision(8);
			foutJ_Events.setf(ios::showpoint|ios::fixed);
		foutJ_Events<<j_bEvents[i];;
			foutJ_Events<<"   ";
			foutJ_Events.precision(8);
			foutJ_Events.setf(ios::showpoint|ios::fixed);
		foutJ_Events<<j_b_plusEvents[i];
			foutJ_Events<<"   ";
			foutJ_Events.precision(8);
			foutJ_Events.setf(ios::showpoint|ios::fixed);
		foutJ_Events<<j_b_minusEvents[i];
			foutJ_Events<<"   ";
			foutJ_Events.precision(8);
			foutJ_Events.setf(ios::showpoint|ios::fixed);
		foutJ_Events<<j_ubEvents[i];
			foutJ_Events<<"   ";
			foutJ_Events.precision(8);
			foutJ_Events.setf(ios::showpoint|ios::fixed);
		foutJ_Events<<j_ub_plusEvents[i];
			foutJ_Events<<"   ";
			foutJ_Events.precision(8);
			foutJ_Events.setf(ios::showpoint|ios::fixed);
		foutJ_Events<<j_ub_minusEvents[i];
			foutJ_Events<<"   ";
			foutJ_Events.precision(8);
			foutJ_Events.setf(ios::showpoint|ios::fixed);
		foutJ_Events<<j_totEvents[i]<<endl;
		}//end for i
foutJ.close();
foutJ_Events.close();

// write radial currents
foutJ.open(MakeFileNames::ResJRadius);
	if(!foutJ) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutJ<<"# x   rho_ub[r,x]"<<endl;
	for(i=0;i<tubeLength-1;i++)
	{
			foutJ.width(6);
			foutJ.setf(ios::left);
		foutJ<<i+1;
		for (r=0;r<tubeRadiusY;r++)
		{
				foutJ.precision(6);
				foutJ.setf(ios::showpoint|ios::fixed);
			foutJ<<j_ub_radiusEvents[i][r];
				foutJ<<"  ";
		}//end for r
		foutJ<<endl;
	}//end for i
foutJ.close();

//write measurement info
ofstream foutMeasureInfo(MakeFileNames::MeasureInfo);
	if(!foutMeasureInfo) {cout<<"Unable to open file! ";ASSERTperm(0);}
	foutMeasureInfo<<actualNumberOfMeasurements<<endl;
	foutMeasureInfo<<numberOfMCSteps<<endl;
	foutMeasureInfo<<measureInterval<<endl;
	foutMeasureInfo<<equilibrationSteps<<endl;
	foutMeasureInfo<<meanNumberOfMotors<<endl;
	foutMeasureInfo<<meanNumberOfPlusMotors<<endl;
	foutMeasureInfo<<meanNumberOfMinusMotors<<endl;
	foutMeasureInfo<<tubeLength<<endl;
	foutMeasureInfo<<tubeRadiusY<<endl;
	foutMeasureInfo<<tubeRadiusZ<<endl;
foutMeasureInfo.close();
foutPara.open(MakeFileNames::parameterFile,ios::app);
	foutPara<<"densities at chosen Point: rho_b = "<<actualRho_b
		<<", rho_ub = "<<actualRho_ub<<endl;
	foutPara<<"  adsorption equilibrium: rho_ub(1-rho_b)/(rho_b)(1-rho_ub) = "
		<<absorptionEqui
		<<", epsilon/pi_ad = "<<epsilon/pi_ad<<endl;
	foutPara<<"  mean motor no = "<<meanNumberOfMotors
		<<", mean plus motors no = "<<meanNumberOfPlusMotors
		<<", mean minus motors no= "<<meanNumberOfMinusMotors
		<<", end motors no = "<<actualNumberOfMotors<<endl;
	foutPara<<"used time: 		"<<timeUsed<<" sec"
		<<" = "<<timeUsed/60<<" min"
		<<" = "<<timeUsed/3600<<" h"<<endl;
foutPara.close();

//******************************************************************
// close correlation files
//******************************************************************
foutCorrRho_b.close();
foutCorrJ_b.close();
foutCorrJ_b_tot.close();
foutCorrRho_b_tot.close();
foutCorrRho_ub_tot.close();
foutCorrN.close();

