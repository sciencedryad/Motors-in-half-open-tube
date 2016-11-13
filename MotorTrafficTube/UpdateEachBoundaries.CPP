//*******************************************************************
// updates boundary layers for tube geometry
//*******************************************************************
//#ifdef DEBUG2
	//cout<<"BOUNDARY UPDATE";
//#endif
//********************************************************************
// update left boundary
//*******************************************************************
if ((boundaryChoice==RhoInRhoEx)||(boundaryChoice==RhoInWall))
{
	numberOfMotorsToUpdate = squareSliceVolume;
	for (i=0;i<squareSliceVolume;i++)
	{
		motorsToUpdate[i] = i;
	}//end for
	while (numberOfMotorsToUpdate>0)
	{
		//cout<<"numberOfMotorsToUpdate "<<numberOfMotorsToUpdate<<endl;
		//for(countMotors=0;countMotors<numberOfMotorsToUpdate;countMotors++)
		//	{cout<<"  "<<motorsToUpdate[countMotors];}
		//cout<<endl;
		randomInt = randomInteger(numberOfMotorsToUpdate);
		actualLocationNumber = motorsToUpdate[randomInt];
			//location on left boundary
		newLocationNumber = actualLocationNumber + Lattice.GetPlusXOffset();
			//neighbour location in tube
		//if (newLocationNumber==793){cout<<"793 in boundaryUpdate!"<<endl;}
		actualLocation = Lattice.GetLocation(actualLocationNumber);
		numberOfMotorsToUpdate = numberOfMotorsToUpdate - 1;
		motorsToUpdate[randomInt]=motorsToUpdate[numberOfMotorsToUpdate];
		if (Lattice.GetOccupation(newLocationNumber)==FREE)
		{
//*******************************************************************
			if (actualLocation==OnLeftBoundaryInSpace)
			{
				randomDouble = randomDouble01();
				if (randomDouble<=rhoInUnbound)
				{
					randomDouble = randomDouble01();
					if (randomDouble<=pdiff)
						{
							createMotor(newLocationNumber,PLUS);
							ASSERT(Lattice.GetLocation(newLocationNumber)==InSpace);
						}
				}//end if randomDouble<=rhoInUnbound
			}//end if actualLocation==OnLeftBoundaryInSpace
//*******************************************************************
			else if (actualLocation==OnLeftBoundaryOnFilament)
			{
				randomDouble = randomDouble01();
				if (randomDouble<=rhoIn)
				{
					randomDouble = randomDouble01();
					if (randomDouble<=alpha)
						{
							createMotor(newLocationNumber,PLUS);
							ASSERT(Lattice.GetLocation(newLocationNumber)==OnFilament);
						}
				}//end if randomDouble<=rhoIn
			}//end else if actualLocation==OnLeftBoundaryOnFilament
//*******************************************************************
			#ifdef DEBUG
			else if  (actualLocation==OnWall) {}
			else {cout<<"ERROR in boundaryUpdate"<<endl;ASSERTperm(0);}
			#endif
		}//end if newLocation FREE
	}// end while
} //end if update for left boundary

//*******************************************************************
// update right boundary
//*******************************************************************
if ((boundaryChoice==RhoInRhoEx)||(boundaryChoice==WallRhoEx))
{
	numberOfMotorsToUpdate = squareSliceVolume;
	for (i=0;i<squareSliceVolume;i++)
	{
		motorsToUpdate[i] = i;
	}//end for
	while (numberOfMotorsToUpdate>0)
	{
		//cout<<"numberOfMotorsToUpdate "<<numberOfMotorsToUpdate<<endl;
		//for(countMotors=0;countMotors<numberOfMotorsToUpdate;countMotors++)
		//	{cout<<"  "<<motorsToUpdate[countMotors];}
		//cout<<endl;
		randomInt = randomInteger(numberOfMotorsToUpdate);
		actualLocationNumber = motorsToUpdate[randomInt];
		actualLocationNumber = squareTotalVolume - actualLocationNumber - 1;
			//location on right boundary
		newLocationNumber = actualLocationNumber + Lattice.GetMinusXOffset();
			//neighbour location in tube
		actualLocation = Lattice.GetLocation(actualLocationNumber);
		numberOfMotorsToUpdate = numberOfMotorsToUpdate - 1;
		motorsToUpdate[randomInt]=motorsToUpdate[numberOfMotorsToUpdate];
		if (Lattice.GetOccupation(newLocationNumber)==FREE)
		{
//*******************************************************************
			if (actualLocation==OnRightBoundaryInSpace)
			{
				randomDouble = randomDouble01();
				if (randomDouble<=rhoExUnbound)
				{
					randomDouble = randomDouble01();
					if (randomDouble<=pdiff)
						{
							createMotor(newLocationNumber,PLUS);
							ASSERT(Lattice.GetLocation(newLocationNumber)==InSpace);
						}
				}//end if randomDouble<=rhoExUnbound
			}//end if actualLocation==OnRightBoundarynSpace
//*******************************************************************
			else if (actualLocation==OnRightBoundaryOnFilament)
			{
				randomDouble = randomDouble01();
				if (randomDouble<=beta)
				{
					randomDouble = randomDouble01();
					if (randomDouble<=rhoEx)
						{
							createMotor(newLocationNumber,PLUS);
							ASSERT(Lattice.GetLocation(newLocationNumber)==OnFilament);
						}
				}//end if randomDouble<=beta
			}//ens else if actualLocation==OnRightBoundaryOnFilament
//*******************************************************************
			#ifdef DEBUG
			else if  (actualLocation==OnWall) {}
			else {cout<<"ERROR in boundaryUpdate"<<endl;ASSERTperm(0);}
			#endif
		}//end if newLocation FREE
	}//end for arrayNumbers i
} //end if update for right boundary

#ifdef DEBUG2
	cout<<endl;
#endif
