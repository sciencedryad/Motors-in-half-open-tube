//******************************************************************
// FINAL MEASUREMENT
//******************************************************************
for(countTime=0;countTime<totalTime;countTime++)
{
// normalize densities
	for(i=0;i<tubeLength;i++)
	{
		rho_b_Time[i][countTime] = rho_b_Time[i][countTime]/numberOfSeeds;
		ASSERT((rho_b_Time[i][countTime]>=0)&&(rho_b_Time[i][countTime]<=1));
		if(Lattice.GetSliceVolume()>1)
		{
			rho_ub_Time[i][countTime] = rho_ub_Time[i][countTime]
				/(numberOfSeeds*(Lattice.GetSliceVolume()-1));
			ASSERT((rho_ub_Time[i][countTime]>=0)&&(rho_ub_Time[i][countTime]<=1));
		}
		else {rho_ub_Time[i][countTime] = 0;}
	}//end for i
//normalize currents
	for(i=0;i<(tubeLength-1);i++)
	{
		j_b_Time[i][countTime] = j_b_Time[i][countTime]/numberOfSeeds;
	}//end for i
//normalize total densities, currents
	rho_b_tot_Time[countTime] = rho_b_tot_Time[countTime]
			/(numberOfSeeds*Lattice.GetNumberOfFilamentSites());
	ASSERT((rho_b_tot_Time[countTime]>=0)&&(rho_b_tot_Time[countTime]<=1));
	j_b_tot_Time[countTime] = j_b_tot_Time[countTime]
			/(numberOfSeeds*(Lattice.GetNumberOfFilamentSites()-1));
	if(Lattice.GetSliceVolume()>1)
		{
			rho_ub_tot_Time[countTime] = rho_ub_tot_Time[countTime]
				/(numberOfSeeds*Lattice.GetNumberOfSpaceSites());
			ASSERT((rho_ub_tot_Time[countTime]>=0)
				&&(rho_ub_tot_Time[countTime]<=1));
			j_ub_tot_Time[countTime] = j_ub_tot_Time[countTime]/(numberOfSeeds
				*(Lattice.GetNumberOfSpaceSites()-Lattice.GetSliceVolume()+1));
		}
	else
		{
			rho_ub_tot_Time[countTime] = 0;
			j_ub_tot_Time[countTime] = 0;
		}
// normalize radial variables
	for (i=0;i<tubeRadiusY;i++)
	{
		actualSegmentVol = Lattice.NumberOfPointsInCircle(i+1)
			- Lattice.NumberOfPointsInCircle(i);
		rho_ub_radius_Time[i][countTime]
			= rho_ub_radius_Time[i][countTime]/actualSegmentVol/numberOfSeeds;
	}
}//end for countTime

// measure traffic jam length
for(countTime=0;countTime<totalTime;countTime++)
{
	i=tubeLength-1; j=0;
	while ((rho_b_Time[i][countTime]>0.5)&&(i>0)) {i=i-1;j=j+1;} 
	jamLength[countTime] = j;
}//end for countTime
for(countTime=0;countTime<totalTime;countTime++)
{
	i=0;
	while ((rho_b_Time[i][countTime]<0.5)&&(i<tubeLength)) {i=i+1;} 
	jamLength2[countTime] = tubeLength - i;
}//end for countTime

//******************************************************************
// open result files
//******************************************************************

ofstream foutCorrRho_b(MakeFileNames::CorrRho_b);
	if(!foutCorrRho_b) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrRho_ub(MakeFileNames::CorrRho_ub);
	if(!foutCorrRho_ub) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrJ_b(MakeFileNames::CorrJ_b);
	if(!foutCorrJ_b) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrJ_ub(MakeFileNames::CorrJ_ub);
	if(!foutCorrJ_ub) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrRho_b_tot(MakeFileNames::CorrRho_b_tot);
	if(!foutCorrRho_b_tot) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrRho_ub_tot(MakeFileNames::CorrRho_ub_tot);
	if(!foutCorrRho_ub_tot) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrJ_b_tot(MakeFileNames::CorrJ_b_tot);
	if(!foutCorrJ_b_tot) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrJ_ub_tot(MakeFileNames::CorrJ_ub_tot);
	if(!foutCorrJ_ub_tot) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrN(MakeFileNames::CorrN);
	if(!foutCorrN) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrJam(MakeFileNames::CorrJam);
	if(!foutCorrJam) {cout<<"Unable to open file! ";ASSERTperm(0);}

ofstream foutCorrRhoRadius(MakeFileNames::CorrRhoRadius);
	if(!foutCorrRhoRadius) {cout<<"Unable to open file! ";ASSERTperm(0);}

//******************************************************************
// write tot files
//******************************************************************
for (countTime=0;countTime<totalTime;countTime++)
{
if ((countTime%every)==0)
{
	for(i=0;i<tubeLength;i++)
		{
// write bound density
			foutCorrRho_b.width(6);
			foutCorrRho_b.setf(ios::left);
			foutCorrRho_b<<i;
			foutCorrRho_b.precision(6);
			foutCorrRho_b.setf(ios::showpoint|ios::fixed);
			foutCorrRho_b<<rho_b_Time[i][countTime]<<endl;
// write unbound density
			foutCorrRho_ub.width(6);
			foutCorrRho_ub.setf(ios::left);
			foutCorrRho_ub<<i;
			foutCorrRho_ub.precision(6);
			foutCorrRho_ub.setf(ios::showpoint|ios::fixed);
			foutCorrRho_ub<<rho_ub_Time[i][countTime]<<endl;
		}//end for i
		foutCorrRho_b<<endl;
		foutCorrRho_ub<<endl;
	for(i=0;i<(tubeLength-1);i++)
		{
// write bound current
			foutCorrJ_b.width(6);
			foutCorrJ_b.setf(ios::left);
			foutCorrJ_b<<i;
			foutCorrJ_b.precision(3);
			foutCorrJ_b.setf(ios::showpoint|ios::fixed);
			foutCorrJ_b<<j_b_Time[i][countTime]<<endl;
// write unbound current
			foutCorrJ_ub.width(6);
			foutCorrJ_ub.setf(ios::left);
			foutCorrJ_ub<<i;
			foutCorrJ_ub.precision(3);
			foutCorrJ_ub.setf(ios::showpoint|ios::fixed);
			foutCorrJ_ub<<j_ub_Time[i][countTime]<<endl;
		}//end for i
		foutCorrJ_b<<endl;
		foutCorrJ_ub<<endl;
	for(i=0;i<tubeRadiusY;i++)
		{
// write radial unbound density
			foutCorrRhoRadius.width(6);
			foutCorrRhoRadius.setf(ios::left);
			foutCorrRhoRadius<<i;
			foutCorrRhoRadius.precision(6);
			foutCorrRhoRadius.setf(ios::showpoint|ios::fixed);
			foutCorrRhoRadius<<rho_ub_radius_Time[i][countTime]<<endl;
		}
		foutCorrRhoRadius<<endl;
}//end if countTime%every
//write total bound and unbound density
	foutCorrRho_b_tot.width(6);
	foutCorrRho_b_tot.setf(ios::left);
	foutCorrRho_b_tot<<countTime*numberOfMCSteps;
	foutCorrRho_b_tot.precision(6);
	foutCorrRho_b_tot.setf(ios::showpoint|ios::fixed);
	foutCorrRho_b_tot<<rho_b_tot_Time[countTime];
	foutCorrRho_b_tot<<"  ";
	foutCorrRho_b_tot.precision(6);
	foutCorrRho_b_tot.setf(ios::showpoint|ios::fixed);
	foutCorrRho_b_tot<<rho_ub_tot_Time[countTime]<<endl;
//write total bound and unbound current
	foutCorrJ_b_tot.width(6);
	foutCorrJ_b_tot.setf(ios::left);
	foutCorrJ_b_tot<<countTime*numberOfMCSteps;
	foutCorrJ_b_tot.precision(6);
	foutCorrJ_b_tot.setf(ios::showpoint|ios::fixed);
	foutCorrJ_b_tot<<j_b_tot_Time[countTime];
	foutCorrJ_b_tot<<"  ";
	foutCorrJ_b_tot.precision(6);
	foutCorrJ_b_tot.setf(ios::showpoint|ios::fixed);
	foutCorrJ_b_tot<<j_ub_tot_Time[countTime]<<endl;
//write jam length
	foutCorrJam.width(6);
	foutCorrJam.setf(ios::left);
	foutCorrJam<<countTime*numberOfMCSteps;
	foutCorrJam<<jamLength[countTime];
	foutCorrJam<<"  ";
	foutCorrJam<<jamLength2[countTime]<<endl;
}//end for countTime

//******************************************************************
// close result files
//******************************************************************
foutCorrRho_b.close();
foutCorrRho_ub.close();
foutCorrJ_b.close();
foutCorrJ_ub.close();
foutCorrRho_b_tot.close();
foutCorrRho_ub_tot.close();
foutCorrJ_b_tot.close();
foutCorrJ_ub_tot.close();
foutCorrN.close();
foutCorrJam.close();
foutCorrRhoRadius.close();

//******************************************************************
// measure time
//******************************************************************
cout<<"output written to "<<MakeFileNames::folder<<endl;
time (&time2); // set time2 to current time (in sec since 1970)
timeUsed = difftime(time2,time1);
cout<<"used time: "<<timeUsed<<" sec"
		<<" = "<<timeUsed/60<<" min"
		<<" = "<<timeUsed/3600<<" h"<<endl;
foutPara.open(MakeFileNames::parameterFile,ios::app);
	foutPara<<"used time: 		"<<timeUsed<<" sec"
		<<" = "<<timeUsed/60<<" min"
		<<" = "<<timeUsed/3600<<" h"<<endl;
foutPara.close();
