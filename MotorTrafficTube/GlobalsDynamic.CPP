//------------------------------------------------------------------------------------
// global variables for dynamic measurements
//------------------------------------------------------------------------------------
double j_bEvents[tubeLength-1];	//bound current, measured by events
double j_ubEvents[tubeLength-1]; //unbound current, measured by events
double j_totEvents[tubeLength-1]; //total current, measured by events

double j_b_plusEvents[tubeLength-1];
double j_ub_plusEvents[tubeLength-1];
double j_tot_plusEvents[tubeLength-1];
double j_b_minusEvents[tubeLength-1];
double j_ub_minusEvents[tubeLength-1];
double j_tot_minusEvents[tubeLength-1];

double j_ub_radiusEvents[tubeLength-1][tubeRadiusY];
double j_ub_plus_radiusEvents[tubeLength-1][tubeRadiusY];
double j_ub_minus_radiusEvents[tubeLength-1][tubeRadiusY];


//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
// SUBROUTINES FOR DYNAMIC MEASUREMENTS
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

//===================================================
//===================================================
// measure events
//===================================================
//===================================================
// measures events of motor hopping (-> currents)
void measureEvents(const int& oldLocationNumber, const int & newLocationNumber,
	const int& movedLeftRight, const LOCATIONS& state,
	const DIRECTIONS motorDir)
{
int xSlice;
//===================================================
// no move
//===================================================
if (movedLeftRight==0)
{}
//===================================================
// moved to the right
//===================================================
else if (movedLeftRight==1)
{
	xSlice=Lattice.GetXSlice(oldLocationNumber) - 1;
	j_totEvents[xSlice] = j_totEvents[xSlice] + 1;
	if(state==OnFilament)	// bound
	{
		ASSERT((Lattice.GetLocation(oldLocationNumber)==OnFilament));
		ASSERT((Lattice.GetLocation(newLocationNumber)==OnFilament)
			||(Lattice.GetLocation(newLocationNumber)==OnRightBoundaryOnFilament));
		ASSERT(xSlice>=0);ASSERT(xSlice<(tubeLength-1));
		j_bEvents[xSlice] = j_bEvents[xSlice] + 1;
		if (motorDir==PLUS)
		{
			j_b_plusEvents[xSlice] = j_b_plusEvents[xSlice] + 1;
		}
		else
		{
			ASSERT(motorDir==MINUS);
			j_b_minusEvents[xSlice] = j_b_minusEvents[xSlice] + 1;
		}
	}
	else				// unbound
	{
		ASSERT(state==InSpace);
		ASSERT((Lattice.GetLocation(oldLocationNumber)==InSpace));
		ASSERT((Lattice.GetLocation(newLocationNumber)==InSpace)
			||(Lattice.GetLocation(newLocationNumber)==OnRightBoundaryInSpace));
		ASSERT(xSlice>=0);ASSERT(xSlice<(tubeLength-1));
		j_ubEvents[xSlice] = j_ubEvents[xSlice] + 1;
		if (motorDir==PLUS)
		{
			j_ub_plusEvents[xSlice] = j_ub_plusEvents[xSlice] + 1;
		}
		else
		{
			ASSERT(motorDir==MINUS);
			j_ub_minusEvents[xSlice] = j_ub_minusEvents[xSlice] + 1;
		}
	}
}//end else if movedLeftRight==1
//===================================================
// moved to the left
//===================================================
else
{
	ASSERT(movedLeftRight==-1);
	xSlice=Lattice.GetXSlice(newLocationNumber) - 1;
	j_totEvents[xSlice] = j_totEvents[xSlice] -1;
	if(state==OnFilament)	// bound
	{
		ASSERT((Lattice.GetLocation(oldLocationNumber)==OnFilament));
		ASSERT((Lattice.GetLocation(newLocationNumber)==OnFilament)
			||(Lattice.GetLocation(newLocationNumber)==OnLeftBoundaryOnFilament));
		ASSERT(xSlice>=0);ASSERT(xSlice<tubeLength-1);
		j_bEvents[xSlice] = j_bEvents[xSlice] - 1;
		if (motorDir==PLUS)
		{
			j_b_plusEvents[xSlice] = j_b_plusEvents[xSlice] - 1;
		}
		else
		{
			ASSERT(motorDir==MINUS);
			j_b_minusEvents[xSlice] = j_b_minusEvents[xSlice] - 1;
		}

	}
	else				// unbound
	{
		ASSERT(state==InSpace);
		ASSERT((Lattice.GetLocation(oldLocationNumber)==InSpace));
		ASSERT((Lattice.GetLocation(newLocationNumber)==InSpace)
			||(Lattice.GetLocation(newLocationNumber)==OnLeftBoundaryInSpace));
		ASSERT(xSlice>=0);ASSERT(xSlice<(tubeLength-1));
		j_ubEvents[xSlice] = j_ubEvents[xSlice] - 1;
		if (motorDir==PLUS)
		{
			j_ub_plusEvents[xSlice] = j_ub_plusEvents[xSlice] - 1;
		}
		else
		{
			ASSERT(motorDir==MINUS);
			j_ub_minusEvents[xSlice] = j_ub_minusEvents[xSlice] - 1;
		}

	}
}//end else movedLeftRight==-1
return;
}//end subroutine measureEvents
