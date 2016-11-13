#include "Definitions.CPP"

int NumberOfPointsInCircle(const int& radius)
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
}//end NumberOfPointsInCircle

//==================================================

int main()
{
int r;
int segmentVol;

for(r=0;r<100;r++)
{
segmentVol=NumberOfPointsInCircle(r+1) - NumberOfPointsInCircle(r);
//cout<<r<<"    "<<NumberOfPointsInCircle(r)<<endl;
cout<<r<<"       "<<segmentVol<<endl;
}


}//end main