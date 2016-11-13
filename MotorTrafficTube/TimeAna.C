#include "Definitions.CPP"

char folder[80]="Time1/";
char configOut[80]; //for simulation parameters
char fileRhoIn[80]; // contains density profiles
char filePOut[80]; // output of derivatives of density profiles
char fileMaxOut[80];// output file for two derivative maxima

const int length = 1000;
int L,rY,rZ;
int numberPlus,numberMinus;

void findTwoMax(int& locMax1, int& locMax2, const int& n, const double* array);

//---------------------------------------------------------------
//---------------------------------------------------------------
// program to calculate derivatives of density profiles
//	of TimeMotorSim
//---------------------------------------------------------------
//---------------------------------------------------------------
int main()
{
int x,t;
int dummy;
double rho[length]; //density profile
double p[length-1];//normalized derivative of density profile
double norm;
int locMax1,locMax2;

sprintf(fileRhoIn,"%s%s",folder,"CorrRho_b.dat");
sprintf(filePOut,"%s%s",folder,"CorrP.dat");
sprintf(configOut,"%s%s",folder,"ConfigOut");
sprintf(fileMaxOut,"%s%s",folder,"CorrMax.dat");

//--------------------------------------------------------------------
//read simulation parameters
//--------------------------------------------------------------------
ifstream finConf(configOut);
	if(!finConf){cout<<"Error, can't open file"<<endl;ASSERTperm(0);}
	finConf>>L; //tubeLength
	finConf>>rY;//tubeRadiusY
	finConf>>rZ;//tubeRadiusZ
	finConf>>numberPlus;//numberOfPlusMotors
	finConf>>numberMinus;//numberOfMinusMotors
finConf.close();
if (length<L){cout<<"ERROR! Tube length too large!";ASSERTperm(0);}
cout<<"tubeLength = "<<L
		<<"; tubeRadius = "<<tubeRadiusY<<endl;
cout<<"numberOfPlusMotors = "<<numberPlus
		<<"; numberOfMinusMotors = "<<numberMinus<<endl;

//--------------------------------------------------------------------
// read motor profile, calculate and write derivative,
//	calculate and write two first maxima locations of derivative
//--------------------------------------------------------------------
ifstream fin(fileRhoIn);
	if(!fin){cout<<"Error, can't open file"<<endl;ASSERTperm(0);}
ofstream fout(filePOut);
	if(!fout){cout<<"Error, can't open file"<<endl;ASSERTperm(0);}
ofstream foutMax(fileMaxOut);
		if(!foutMax){cout<<"Error, can't open file"<<endl;ASSERTperm(0);}
t=0;
while(!fin.eof())
{
//read densities
	for (x=0;x<L;x++)
	{
		fin>>dummy;
		fin>>rho[x];
	}
//calculate and write derivative
	norm = 0;
	for (x=0;x<L-1;x++)
	{
		p[x] = rho[x+1] - rho[x];
		norm = norm + p[x];
	}
	for (x=0;x<L-1;x++)
	{
		p[x] = p[x]/norm;
		fout.width(6); 
		fout.setf(ios::left);
		fout<<x;
		fout.precision(3);
		fout.setf(ios::showpoint|ios::fixed);
		fout<<p[x]<<endl;
	}
	fout<<endl;
//calculate and write maxima locations
	findTwoMax(locMax1,locMax2,L-1,p);
	foutMax.width(6); 
	foutMax.setf(ios::left);
	foutMax<<t<<locMax1<<"   "<<locMax2<<endl;
t=t+1;	
}//end while !fin.eof()
/*
cout<<"norm = "<<norm<<endl;
for (x=0;x<L;x++)
	{
		cout<<x<<"  "<<rho[x]<<"   "<<p[x]<<endl;;
	}
cout<<"max1 at "<<locMax1<<endl;
cout<<"max2 at "<<locMax2<<endl;
*/
fin.close();
fout.close();
foutMax.close();

return 0;
}//end main
//---------------------------------------------------------------
//---------------------------------------------------------------

//---------------------------------------------------------------
// find the first two maxima locations locMax1, locMax2 
//		of array array of length n
// maxima must be at least a distance minDist apart
// maxLoc1 < maxLoc2
//---------------------------------------------------------------
void findTwoMax(int& locMax1, int& locMax2, const int& n, const double* array)
{
int i;
double max1,max2;
int minDist = 7; // distance of the two max
ASSERTperm(n>0);
max1=array[0];locMax1=0;
// find absolute max
for (i=0;i<n;i++)
{
	if (array[i]>max1){max1=array[i]; locMax1=i;}
}
// find second max
max2=array[0];locMax2=0;
for (i=0;i<n;i++)
{
	if ((array[i]>max2)&&(array[i]<=max1)
				&&(abs(i-locMax1)>minDist))
		{max2=array[i]; locMax2=i;}
}
/*
if (locMax1>locMax2) 
	{
		i=locMax1;
		locMax1=locMax2;
		locMax2=i;
	}*/
/*cout<<"array: "<<endl;
for (i=0;i<n;i++)
{
	cout<<"  "<<i<<"  "<<array[i]<<endl;
}
cout<<"max1 = "<<max1<<" at "<<locMax1<<endl;
cout<<"max2 = "<<max2<<" at "<<locMax2<<endl;*/
}//end subroutine findTwoMax
