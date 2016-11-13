//******************************************************************
// MEASURE
//******************************************************************

//densities and currents
actualNumberOfMotors = Particle::totalNumberOfParticles;
for(countMotors=0;countMotors<actualNumberOfMotors;countMotors++)
{
	actualLocationNumber = pMotor[countMotors]->GetLocationNumber();
	actualLocation = Lattice.GetLocation(actualLocationNumber);
	actualSlice = Lattice.GetXSlice(actualLocationNumber) - 1;
	actualRadius = Lattice.GetRadius(actualLocationNumber);
	ASSERT((actualSlice>=0)&&(actualSlice<tubeLength));
	if (actualLocation==InSpace)
	{
		rho_ub_Time[actualSlice][countTime]
			= rho_ub_Time[actualSlice][countTime] + 1;//unbound density
		rho_ub_tot_Time[countTime] = rho_ub_tot_Time[countTime] + 1;
		actualRadius = Lattice.GetRadius(actualLocationNumber);
		rho_ub_radius_Time[actualRadius][countTime]
			= rho_ub_radius_Time[actualRadius][countTime] + 1;
		ASSERT(rho_ub_Time[actualSlice][countTime]>0);
		ASSERT(rho_ub_tot_Time[countTime]>0);
	}//end if InSpace
	else if(actualLocation==OnFilament)
	{
		rho_b_Time[actualSlice][countTime] 
			= rho_b_Time[actualSlice][countTime] + 1; // bound density
		rho_b_tot_Time[countTime] = rho_b_tot_Time[countTime] + 1;
		ASSERT(rho_b_Time[actualSlice][countTime]>0)
		newLocationNumber = actualLocationNumber + Lattice.GetPlusXOffset();
		if (Lattice.GetOccupation(newLocationNumber)==FREE)
		{
			if(Lattice.GetLocation(newLocationNumber)==OnFilament)
			{
				j_b_Time[actualSlice][countTime] 
					= j_b_Time[actualSlice][countTime] + alpha;
				j_b_tot_Time[countTime] = j_b_tot_Time[countTime] + alpha;
			}
		}//end if newLocationNumber==FREE	
		if (beta!=0)
		{
			newLocationNumber = actualLocationNumber + Lattice.GetMinusXOffset();
			if (Lattice.GetOccupation(newLocationNumber)==FREE)
			{
				if(Lattice.GetLocation(newLocationNumber)==OnFilament)
				{
					j_b_Time[actualSlice-1][countTime] 
						= j_b_Time[actualSlice-1][countTime] - beta;
					j_b_tot_Time[countTime] = j_b_tot_Time[countTime] - beta;
				}
			}//end if newLocationNumber==FREE
		}//end if beta!=0
	}//end else if OnFilament
}//end for countMotors
