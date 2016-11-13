//================================================
//================================================
// MEASURE
//================================================
//================================================

//================================================
//number of measurements and particles
//================================================
actualNumberOfMeasurements = actualNumberOfMeasurements + 1;
meanNumberOfMotors = meanNumberOfMotors
		+ Particle::totalNumberOfParticles;
meanNumberOfPlusMotors = meanNumberOfPlusMotors
		+ Particle::numberOfPlusParticles;
meanNumberOfMinusMotors = meanNumberOfMinusMotors
		+ Particle::numberOfMinusParticles;
meanNumberOfParticles = meanNumberOfParticles
		+ Particle::totalNumberOfParticles;
#ifdef DEBUG2
	cout<<"MEASUREMENT No"<<actualNumberOfMeasurements
		<<",  motorNumber "<<Particle::totalNumberOfParticles
		<<", plus "<<Particle::numberOfPlusParticles
		<<", minus "<<Particle::numberOfMinusParticles<<endl;
	for (countMotors=0;countMotors<Particle::totalNumberOfParticles;countMotors++)
	{
		actualLocationNumber = pMotor[countMotors]->GetLocationNumber();
		cout<<"Motor number "<<countMotors
			<<" with dir "<<pMotor[countMotors]->GetDirection()
			<<" is at "<<actualLocationNumber<<" on xSlice "
			<<Lattice.GetXSlice(actualLocationNumber)<<" ";
		DisplayLocations(Lattice.GetLocation(actualLocationNumber));cout<<endl;
	}
#endif

//================================================
//densities and currents
//================================================
actualNumberOfMotors = Particle::totalNumberOfParticles;
for(countMotors=0;countMotors<actualNumberOfMotors;countMotors++)
{
	actualLocationNumber = pMotor[countMotors]->GetLocationNumber();
	actualDirection = pMotor[countMotors]->GetDirection();
	actualLocation = Lattice.GetLocation(actualLocationNumber);
	actualSlice = Lattice.GetXSlice(actualLocationNumber) - 1;
	actualRadius = Lattice.GetRadius(actualLocationNumber);
	ASSERT((actualSlice>=0)&&(actualSlice<tubeLength));
//================================================
// in space
//================================================
	if (actualLocation==InSpace)
	{
		//================================================
		// unbound densities
		//================================================
		rho_ub[actualSlice] = rho_ub[actualSlice] + 1;
		rho_ub_tot = rho_ub_tot + 1;
		rho_ub_radius[actualSlice][actualRadius]
			= rho_ub_radius[actualSlice][actualRadius] + 1;
		if (actualDirection==PLUS)
		{
			rho_ub_plus[actualSlice]=rho_ub_plus[actualSlice]+1;
			rho_ub_plus_radius[actualSlice][actualRadius]
				= rho_ub_plus_radius[actualSlice][actualRadius] + 1;
		}
		else
		{
			ASSERT(actualDirection==MINUS)
			rho_ub_minus[actualSlice]=rho_ub_minus[actualSlice]+1;
			rho_ub_minus_radius[actualSlice][actualRadius]
			= rho_ub_minus_radius[actualSlice][actualRadius] + 1;
		}
		ASSERT(rho_ub[actualSlice]>0);
/*
		//================================================
		// unbound currents (correlation)
		//================================================
		newLocationNumber = actualLocationNumber + Lattice.GetPlusXOffset();
		if (Lattice.GetOccupation(newLocationNumber)==FREE)
		{
			if (Lattice.GetLocation(newLocationNumber)==InSpace)
			{
				ASSERT((actualSlice>=0)&&(actualSlice<(tubeLength-1)));
				j_ub[actualSlice] = j_ub[actualSlice] + (1.0/6);
				j_tot[actualSlice] = j_tot[actualSlice] + (1.0/6);
				j_ub_tot = j_ub_tot + 1 ;
			}
		}//end if newLocationNumber==FREE
		newLocationNumber = actualLocationNumber + Lattice.GetMinusXOffset();
		if (Lattice.GetOccupation(newLocationNumber)==FREE)
		{
			if (Lattice.GetLocation(newLocationNumber)==InSpace)
			{
				ASSERT(((actualSlice-1)>=0)&&((actualSlice-1)<(tubeLength-1)));
				j_ub[actualSlice-1] = j_ub[actualSlice-1] - (1.0/6);
				j_tot[actualSlice-1] = j_tot[actualSlice-1] - (1.0/6);
				j_ub_tot = j_ub_tot -1;
			}
		}//end if newLocationNumber==FREE
*/
	}//end if InSpace
//================================================
// on filament
//================================================
	else if(actualLocation==OnFilament)
	{
		//================================================
		// bound densities
		//================================================
		rho_b[actualSlice] = rho_b[actualSlice] + 1;
		rho_b_tot = rho_b_tot + 1;
		if (actualDirection==PLUS)
		{
			rho_b_plus[actualSlice]=rho_b_plus[actualSlice]+1;
		}
		else
		{
			ASSERT(actualDirection==MINUS)
			rho_b_minus[actualSlice]=rho_b_minus[actualSlice]+1;
		}
		ASSERT(rho_b[actualSlice]>0)
		ASSERT(rho_b[actualSlice]<=actualNumberOfMeasurements);
/*
		//================================================
		// bound currents
		//================================================
		newLocationNumber = actualLocationNumber + Lattice.GetPlusXOffset();
		if (Lattice.GetOccupation(newLocationNumber)==FREE)
		{
			if(Lattice.GetLocation(newLocationNumber)==OnFilament)
			{
				j_b[actualSlice] = j_b[actualSlice] + alpha;
				j_tot[actualSlice] = j_tot[actualSlice] + alpha;
				j_b_tot = j_b_tot + alpha;
			}
		}//end if newLocationNumber==FREE
		if (beta!=0)
		{
			newLocationNumber = actualLocationNumber + Lattice.GetMinusXOffset();
			if (Lattice.GetOccupation(newLocationNumber)==FREE)
			{
				if(Lattice.GetLocation(newLocationNumber)==OnFilament)
				{
					j_b[actualSlice-1] = j_b[actualSlice-1] - beta;
					j_tot[actualSlice-1] = j_tot[actualSlice-1] - beta;
					j_b_tot = j_b_tot - beta;
				}
			}//end if newLocationNumber==FREE
		}//end if beta!=0
*/
	}//end else if OnFilament
}//end for countMotors

//================================================
//density and current at special point
//================================================
if((Lattice.GetOccupation(chosenPoint)==OCCUPIEDPLUS)
	||(Lattice.GetOccupation(chosenPoint)==OCCUPIEDMINUS))
{
	densityAtChosenPoint = densityAtChosenPoint + 1;
	newLocationNumber = chosenPoint + Lattice.GetPlusXOffset();
	if(Lattice.GetOccupation(newLocationNumber)==FREE)
	{
		if(Lattice.GetLocation(newLocationNumber)==OnFilament)
		{
			currentAtChosenPoint = currentAtChosenPoint + alpha;
		}
	}//end if newLocationNumber==FREE
}//end if Occupation at ChosenPoint
else if (beta!=0)//ans chosenPoint FREE
{
	newLocationNumber = chosenPoint + Lattice.GetPlusXOffset();
	if ((Lattice.GetOccupation(newLocationNumber)==OCCUPIEDPLUS)
		||(Lattice.GetOccupation(newLocationNumber)==OCCUPIEDMINUS))
		{
			if(Lattice.GetLocation(newLocationNumber)==OnFilament)
			{
				currentAtChosenPoint = currentAtChosenPoint - beta;
			}
	}//end if newLocationNumber==OCCUPIED
}//end else if beta!=0

#ifdef DEBUG2
	cout<<"rho_b  ";
	for(i=0;i<tubeLength;i++)
		{cout<<rho_b[i]<<"  ";}
	cout<<endl;
	cout<<"rho_ub ";
	for(i=0;i<tubeLength;i++)
		{ cout<<rho_ub[i]<<"  ";}
	cout<<endl;
#endif

//******************************************************************
// WRITE to file each measureInterval measurement
//******************************************************************

if ((actualNumberOfMeasurements%measureInterval)==0)
{
// normalizations
/*	cout<<"WRITING measure number "<<actualNumberOfMeasurements<<endl;
	cout<<"  densityAtChosenPoint = "<<densityAtChosenPoint
			<<"; rho_b_tot = "<<rho_b_tot
			<<"; rho_ub_tot = "<<rho_ub_tot
			<<"; j_b_tot = "<<j_b_tot<<endl;
	cout<<"  measureInterval = "<<measureInterval
			<<"; SpaceSites = "<<Lattice.GetNumberOfSpaceSites()
			<<"; product = "
			<<measureInterval*Lattice.GetNumberOfSpaceSites()<<endl;*/
	densityAtChosenPoint = densityAtChosenPoint/(1.0*measureInterval);
	currentAtChosenPoint = currentAtChosenPoint/measureInterval;
	rho_b_tot = rho_b_tot/measureInterval/(Lattice.GetNumberOfFilamentSites());
	rho_ub_tot = rho_ub_tot/measureInterval/(Lattice.GetNumberOfSpaceSites());
	j_b_tot = j_b_tot/measureInterval/(Lattice.GetNumberOfFilamentSites()-1);
	meanNumberOfParticles = meanNumberOfParticles/measureInterval;
/*	cout<<"  densityAtChosenPoint = "<<densityAtChosenPoint
			<<"; rho_b_tot = "<<rho_b_tot
			<<"; rho_ub_tot = "<<rho_ub_tot
			<<"; j_b_tot = "<<j_b_tot<<endl;
*/
// assert
	ASSERT(densityAtChosenPoint>=0);ASSERT(densityAtChosenPoint<=1.00000000001);
	ASSERT((rho_b_tot>=0)&&(rho_b_tot<=1));
	ASSERT((rho_ub_tot>=0)&&(rho_ub_tot<=1));
	ASSERT(meanNumberOfParticles>=0);

// WRITE ASCI-FILES
/*
	foutCorrRho_b<<densityAtChosenPoint<<endl;
	foutCorrRho_b_tot<<rho_b_tot<<endl;
	foutCorrRho_ub_tot<<rho_ub_tot<<endl;
	foutCorrN<<meanNumberOfParticles<<endl;
*/

// WRITE BINARY FILES

	foutCorrRho_b.write((char*)& densityAtChosenPoint,sizeof(double));
	foutCorrJ_b.write((char*)& currentAtChosenPoint,sizeof(double));
	foutCorrRho_b_tot.write((char*)& rho_b_tot,sizeof(double));
	foutCorrRho_ub_tot.write((char*)& rho_ub_tot,sizeof(double));
	foutCorrJ_b_tot.write((char*)& j_b_tot,sizeof(double));
	foutCorrN.write((char*)& meanNumberOfParticles,sizeof(double));

// set back to zero
	densityAtChosenPoint=0;
	currentAtChosenPoint=0;
	rho_b_tot=0;
	rho_ub_tot=0;
	j_b_tot = 0;
	j_ub_tot = 0;
	meanNumberOfParticles=0;

// WRITE CONFIGURATION
	if (writeConf==1)
		{writeConfig(actualNumberOfMeasurements);}

}// end if measureInterval




