//******************************************************************
// TUBE GEOMETRY CLASS
//******************************************************************
class TubeGlobals 
// global variables for tube geometry
// needs global constants tubeLength, tube RadiusY, tubeRadiusZ 
// 	squareLength, squareTransverseLength, squareSliceVolume,
// 	squareTotalVolume 
// outer layer is always OnWall
// OnWall locations are set to Occupied

{
private: 
	int itsSliceVolume;		// volume of y,z-slice
	int itsTotalVolume;  // "real tube volume"
	int itsMinX,itsMaxX,itsMinY,itsMaxY,itsMinZ,itsMaxZ;
			// coordinate range
	int itsOffsetPlusX,itsOffsetMinusX,itsOffsetPlusY,itsOffsetMinusY,
			itsOffsetPlusZ,itsOffsetMinusZ;
			// offset for nearest neighbours
	LOCATIONS itsLocation[squareTotalVolume];
			// location of lattice point (InSpace, OnWall etc.)
	OCCUPATIONS itsOccupation[squareTotalVolume];
			// occupation of point (1 or 0 or motor-type dependent)
	int itsMiddleOfFilament; // number of middle of filament
	int itsNumberOfFilamentSites;
	int itsNumberOfSpaceSites;
	int itsRadius[squareTotalVolume]; // radial position of point
public:
  static int numberOfGeometries; // assure singleton
  TubeGlobals();
public:
  int GetSliceVolume()const{return itsSliceVolume;};
  int GetTotalVolume()const{return itsTotalVolume;};
  void GetCoordinateRange(int& minX,int& maxX,int& minY,int& maxY,
		  int& minZ,int& maxZ)const
		{	minX=itsMinX; maxX=itsMaxX; minY=itsMinY; maxY=itsMaxY;
			minZ=itsMinZ; maxZ=itsMaxZ;};
  int GetPlusXOffset()const {return itsOffsetPlusX;};
  int GetMinusXOffset()const{return itsOffsetMinusX;};
  int GetPlusYOffset()const {return itsOffsetPlusY;};
  int GetMinusYOffset()const{return itsOffsetMinusY;};
  int GetPlusZOffset()const {return itsOffsetPlusZ;};
  int GetMinusZOffset()const{return itsOffsetMinusZ;};
LOCATIONS GetLocation(const int& arrayNumber)const
	{
		ASSERT((arrayNumber>=0)&&(arrayNumber<squareTotalVolume));
		return itsLocation[arrayNumber];
	};
OCCUPATIONS GetOccupation(const int& arrayNumber)const
	{
		ASSERT((arrayNumber>=0)&&(arrayNumber<squareTotalVolume));
		return itsOccupation[arrayNumber];
	};
void SetOccupation
	(const int& arrayNumber, const OCCUPATIONS& occupation)
	{
		ASSERT((arrayNumber>=0)&&(arrayNumber<squareTotalVolume));
		itsOccupation[arrayNumber]=occupation;
	};
void GetCoordinates(const int& arrayNumber, int& x,
		int& y, int& z)const
	{
		ASSERT((arrayNumber>=0)&&(arrayNumber<squareTotalVolume));
		x = (arrayNumber/squareSliceVolume) + itsMinX;
		y = ((arrayNumber%squareSliceVolume)/squareTransverseLengthZ)
				+ itsMinY;
		z = (arrayNumber%squareTransverseLengthZ) + itsMinZ;
		ASSERT((x>=itsMinX)&&(x<=itsMaxX));
		ASSERT((y>=itsMinY)&&(y<=itsMaxY));
		ASSERT((z>=itsMinZ)&&(z<=itsMaxZ));
	};
int GetXSlice(const int& arrayNumber)const
	{
		ASSERT((arrayNumber>=0)&&(arrayNumber<squareTotalVolume));
		return (arrayNumber/squareSliceVolume) + itsMinX;;
	};
int GetRadius(const int& arrayNumber)const
	{
		ASSERT((arrayNumber>=0)&&(arrayNumber<squareTotalVolume));
		return itsRadius[arrayNumber];
	}
int GetMiddleOfFilament()const{return itsMiddleOfFilament;};
int GetNumberOfFilamentSites()const{return itsNumberOfFilamentSites;};
int GetNumberOfSpaceSites()const{return itsNumberOfSpaceSites;};
void DisplayParameters()const;
void DisplayGeometry()const;
void DisplayCoordinates()const;
void DisplayOccupations()const;
void DisplayArrayNumbers()const;
//private:
  int NumberOfPointsInCircle(const int& radius);
  int NumberOfPointsInEllipse(const int& radiusY,const int& radiusZ);
};// end declaration of class TubeGlobals
//***************************************************************************
//***************************************************************************

int TubeGlobals::numberOfGeometries = 0;
// counts number of initialized lattices
// has to be = 1 (singleton), ASSERT in lattice constructor

TubeGlobals::TubeGlobals()
{
numberOfGeometries = numberOfGeometries + 1;
ASSERTperm(numberOfGeometries==1);
ASSERTperm(tubeLength>=0);
ASSERTperm(tubeRadiusY>=0);
ASSERTperm(tubeRadiusZ>=0);
ASSERTperm(squareLengthX>0);
ASSERTperm(squareTransverseLengthY>0);
ASSERTperm(squareTransverseLengthZ>0);
ASSERTperm(squareSliceVolume>0);
ASSERTperm(squareTotalVolume>0);
//if (tubeRadiusY==tubeRadiusZ)
itsSliceVolume = NumberOfPointsInCircle(tubeRadiusY);
//else {itsSliceVolume = NumberOfPointsInEllipse(tubeRadiusY,tubeRadiusZ);}
itsTotalVolume = itsSliceVolume * tubeLength;
itsMinX = 0;                itsMaxX = tubeLength+1;
itsMinY = -(tubeRadiusY+1); itsMaxY = tubeRadiusY+1;
itsMinZ = -(tubeRadiusZ+1); itsMaxZ = tubeRadiusZ+1;
itsOffsetPlusX  = squareSliceVolume;
itsOffsetMinusX = -itsOffsetPlusX;
itsOffsetPlusY  = squareTransverseLengthZ;
itsOffsetMinusY = -itsOffsetPlusY;
itsOffsetPlusZ  = 1;
itsOffsetMinusZ = -itsOffsetPlusZ;
int tubeRadiusYSquared = tubeRadiusY * tubeRadiusY;
int tubeRadiusZSquared = tubeRadiusZ * tubeRadiusZ;
itsMiddleOfFilament = 0; // if tubeLength = 0, otherwise will be changed later
itsNumberOfFilamentSites=0;
itsNumberOfSpaceSites=0;
int x,y,z;
int r2;
//variables for radial measurement
	double radius;
	int radiusInt;
	int segmentVol[tubeRadiusY];
	for (y=0;y<tubeRadiusY;y++){segmentVol[y]=0;}
int arrayNumber = -1; // C++ array start from 0
for (x=itsMinX;x<=itsMaxX;x++)
{
	for (y=itsMinY;y<=itsMaxY;y++)
	{
		for (z=itsMinZ;z<=itsMaxZ;z++)
		{
		arrayNumber = arrayNumber + 1;
		ASSERT(arrayNumber>=0);ASSERT(arrayNumber<squareTotalVolume);
		#ifdef DEBUG
		{
			int xTest,yTest,zTest;
			GetCoordinates(arrayNumber,xTest,yTest,zTest);
			ASSERT((xTest==x)&&(yTest==y)&&(zTest==z));
		}
    		#endif
		r2 = y*y + z*z;
		if (r2>tubeRadiusYSquared) // outside tube
			{itsLocation[arrayNumber]=OnWall;}
		else //inside tube
		{
			if ((y==0) && (z==0))
			{
				if (x==itsMinX)
				{
					if ((boundaryChoice==RhoInRhoEx)
						||(boundaryChoice==RhoInWall)
						||(boundaryChoice==Periodic)	)
						{itsLocation[arrayNumber]=OnLeftBoundaryOnFilament;}
					else
						{itsLocation[arrayNumber]=OnWall;}
				}//end if x==itsMinX
				else if (x==itsMaxX)
				{
					if ((boundaryChoice==RhoInRhoEx)
						||(boundaryChoice==WallRhoEx)
						||(boundaryChoice==Periodic)  )
						{itsLocation[arrayNumber]=OnRightBoundaryOnFilament;}
					else
						{itsLocation[arrayNumber]=OnWall;}
				}//end else if x==itsMaxX
				else //on filament
				{
					itsLocation[arrayNumber]=OnFilament;
					if (x==(itsMinX+itsMaxX)/2)
						{itsMiddleOfFilament = arrayNumber;}
					itsNumberOfFilamentSites=itsNumberOfFilamentSites+1;
				}// end else on filament
     	  		}//end if y=0 and z=0
			else // y!=0 or z!=0
			{
				if (x==itsMinX)
				{
					if (	(boundaryChoice==RhoInRhoEx)
						||(boundaryChoice==RhoInWall)
						||(boundaryChoice==Periodic)  )
						{itsLocation[arrayNumber]=OnLeftBoundaryInSpace;}
					else
						{itsLocation[arrayNumber]=OnWall;}
				}//end if x=itsMinX
        			else if (x==itsMaxX)
				{
					if (	(boundaryChoice==RhoInRhoEx)
						||(boundaryChoice==WallRhoEx)
						||(boundaryChoice==Periodic)  )
						{itsLocation[arrayNumber]=OnRightBoundaryInSpace;}
					else
					{itsLocation[arrayNumber]=OnWall;}
				}//end else if x=itsMaxX
				else
				{
					ASSERT(arrayNumber>=0);ASSERT(arrayNumber<squareTotalVolume);
					itsLocation[arrayNumber]=InSpace;
					itsNumberOfSpaceSites=itsNumberOfSpaceSites+1;
					radius = sqrt(y*y + z*z);
					radiusInt = int(radius);
					//cout<<y<<", "<<z<<"  "<<y*y+z*z<<", radius = "<<radius<<", "<<radiusInt;;
					if (radius>radiusInt)
					{
						itsRadius[arrayNumber]=radiusInt;
						ASSERT(radiusInt>=0);ASSERT(radiusInt<tubeRadiusY);
						segmentVol[radiusInt]=segmentVol[radiusInt]+1;
					}
					else
					{
						itsRadius[arrayNumber]=radiusInt-1;
						ASSERT(radiusInt>0);ASSERT(radiusInt<=tubeRadiusY);
						segmentVol[radiusInt-1]=segmentVol[radiusInt-1]+1;
					}
					//cout<<"  "<<itsRadius[arrayNumber]<<endl;
				}
 	    		}//end else y!=0 or z!=0
    		}// end else inside tube
		}// end for z
	}//end for y
}// end for x
ASSERT(arrayNumber==squareTotalVolume-1);
ASSERT(itsNumberOfFilamentSites==tubeLength);
ASSERT(itsNumberOfSpaceSites==(itsTotalVolume-tubeLength));
for (y=0;y<tubeRadiusY;y++)
	{
		//cout<<y<<"  segmentVol = "<<segmentVol[y]<<endl;
		ASSERT(segmentVol[y]=NumberOfPointsInCircle(y+1)-NumberOfPointsInCircle(y));
	}
for(arrayNumber=0;arrayNumber<squareTotalVolume;arrayNumber++)
	{
		if (itsLocation[arrayNumber]==OnWall)
					{itsOccupation[arrayNumber] = OCCUPIEDPLUS;}
		else 	{itsOccupation[arrayNumber] = FREE;}
	}
ASSERT((itsMiddleOfFilament>=0)
				&&(itsMiddleOfFilament<=squareTotalVolume));
ASSERT(GetLocation(itsMiddleOfFilament)==OnFilament);
}// end TubeGlobals constructor

//***************************************************************************

void TubeGlobals::DisplayParameters()const
{
cout<<endl;
cout<<"TUBE GEOMETRY PARAMETERS\n";
cout<<"  tubeLength = "<<tubeLength
		<<", tubeRadiusY = "<<tubeRadiusY
		<<", tubeRadiusZ = "<<tubeRadiusZ<<endl;
cout<<"  squareLengthX = "<<squareLengthX
		<<", squareTransverseLengthY = "<<squareTransverseLengthY
		<<", squareTransverseLengthZ = "<<squareTransverseLengthZ<<endl;
cout<<"  squareSliceVolume = "<<squareSliceVolume
		<<", squareTotalVolume = "<<squareTotalVolume<<endl;
cout<<"  sliceVolume = "<<itsSliceVolume
		<<", tubeVolume = "<<itsTotalVolume<<endl;
cout<<"  xRange=["<<itsMinX<<","<<itsMaxX<<"], ";
cout<<"  yRange=["<<itsMinY<<","<<itsMaxY<<"], ";
cout<<"  zRange=["<<itsMinZ<<","<<itsMaxZ<<"]\n";
}//end TubeGlobals DisplayParameters

//***************************************************************************

void TubeGlobals::DisplayGeometry()const
{
int i;
LOCATIONS actualLocation;
cout<<"  LOCATIONS:\n\n";
for(i=0;i<squareTotalVolume;i++)
{
	if ( (i+squareTransverseLengthZ) % squareTransverseLengthZ == 0)
	{cout<<"  ";}
	actualLocation = itsLocation[i];
	if      (actualLocation==OnWall) 										{cout<<"X";}
	else if (actualLocation==InSpace)								    {cout<<"*";}
	else if (actualLocation==OnFilament)						    {cout<<"-";}
	else if (actualLocation==OnLeftBoundaryInSpace)			{cout<<"{";}
	else if (actualLocation==OnLeftBoundaryOnFilament)	{cout<<"<";}
	else if (actualLocation==OnRightBoundaryInSpace)		{cout<<"}";}
	else if (actualLocation==OnRightBoundaryOnFilament)	{cout<<">";}
	else {cout<<"ERROR: nonvalid location!"; exit(8);}
	if ( (i+1) % squareTransverseLengthZ == 0){cout<<endl;}
	if ( (i+1) % squareSliceVolume == 0){cout<<endl;}
}
}//end TubeGlobals DisplayGeometry

//***************************************************************************

void TubeGlobals::DisplayCoordinates()const
{
int i;
int x,y,z;
cout<<"TUBE COORDINATES"<<endl;
for(i=0;i<squareTotalVolume;i++)
{
	GetCoordinates(i,x,y,z);
	cout<<"i= "<<i<<"; \t";
	cout<<"x,y,z\t"<<x<<"\t"<<y<<"\t"<<z<<"\t";
	cout<<"location: "<<itsLocation[i]<<"\t";
	cout<<"occupation: "<<itsOccupation[i]<<endl;
}
}//end TubeGlobals DisplayCoordinates

//***************************************************************************

void TubeGlobals::DisplayOccupations()const
{
int i;
OCCUPATIONS actualOccupation;
cout<<"  OCCUPATIONS:\n\n";
for(i=0;i<squareTotalVolume;i++)
{
	if ((i+squareTransverseLengthZ)%squareTransverseLengthZ==0)
		{cout<<"  ";}
	actualOccupation = itsOccupation[i];
	if   (actualOccupation==OCCUPIEDPLUS)
		{cout<<"p";}
	else if (actualOccupation==OCCUPIEDMINUS)
		{cout<<"m";}
	else
		{cout<<"O";}
	if ( (i+1) % squareTransverseLengthZ == 0){cout<<endl;}
	if ( (i+1) % squareSliceVolume == 0)			{cout<<endl;}
}
}//end TubeGlobals DisplayOccupations

//***************************************************************************

void TubeGlobals::DisplayArrayNumbers()const
{
int i;
cout<<"Offsets: Plus x: "<<itsOffsetPlusX
		<<"\t Minus x: "<<itsOffsetMinusX<<endl;
cout<<"Offsets: Plus y: "<<itsOffsetPlusY
		<<"\t Minus y: "<<itsOffsetMinusY<<endl;
cout<<"Offsets: Plus z: "<<itsOffsetPlusZ
		<<"\t Minus z: "<<itsOffsetMinusZ<<endl;
cout<<endl;
cout<<"  ARRAYNUMBERS:\n\n";
for(i=0;i<squareTotalVolume;i++)
{
	if ((i+squareTransverseLengthZ)%squareTransverseLengthZ==0)
		{cout<<"  ";}
  cout.width(5);cout<<i;
	if ( (i+1) % squareTransverseLengthZ == 0){cout<<endl;}
	if ( (i+1) % squareSliceVolume == 0)      {cout<<endl;}
}
}//end TubeGlobals DisplayarrayNumbers

//***************************************************************************

int TubeGlobals::NumberOfPointsInCircle(const int& radius)
// calculates number of lattice points in circle of radius radius 
// (Gauss circle problem)
{
ASSERT(radius>=0); 
int radius2 = radius * radius;
int numberOfPoints = 0;
int x,y,r2;
for (x=-radius;x<=radius;x++)
{
 	for (y=-radius;y<=radius;y++)
  {
		r2 = x*x + y*y;
		if (r2<=radius2) { numberOfPoints = numberOfPoints + 1; }
  }
}
ASSERT(numberOfPoints>=0);
return numberOfPoints;
}//end TubeGlobals NumberOfPointsInCircle

//***************************************************************************

int TubeGlobals::NumberOfPointsInEllipse(const int& radiusY, 
	const int& radiusZ)
// calculates number of lattice points in ellipse with
// radii radiusY, radiusZ
{
ASSERT(radiusY>=0);ASSERT(radiusZ>=0);
int rY2 = radiusY * radiusY;
int rZ2 = radiusZ * radiusZ;
int y,z;
float r2;
int numberOfPoints = 0;
if (rY2==0) 
	{numberOfPoints = 2*radiusZ + 1;}
else if (rZ2==0)
	{numberOfPoints = 2*radiusY + 1;}
else
	for (y=-radiusY;y<=radiusY;y++)
	{
 		for (z=-radiusZ;z<=radiusZ;z++)
  	{
			r2 = (((float)y)*y)/rY2 + (((float)z)*z)/rZ2;
			if (r2<=1) { numberOfPoints = numberOfPoints + 1; }
  	}
	}
ASSERT(numberOfPoints>=0);
return numberOfPoints;
}//end TubeGlobals NumberOfPointsInEllipse
