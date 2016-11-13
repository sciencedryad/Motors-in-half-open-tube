#include "Definitions.CPP"

//const char folder[80]="RhoInWallMinusAlpha001Rho093/";
//const char folder[80]="RhoInWallMinusRho09Alph0006/";
const char folder[80]="RhoInWallMinusAlpha001K12/";
const char fileName[80]="ResRho.dat";
//const char fileName[80]="ResJEvents.dat";
const int profileLength = 600;
const int numberOfColumns=7;  // for "ResRho.dat"
//const int numberOfColumns=8;	//for "ResJEvents.dat"

int takeColumn=2;

const int arrayLength=10000;//to avoid dynamic allocation

#include "ProfileAnaSubroutines.CPP"

int main()
{
char fileIn[80];
double data[arrayLength];
int i,j;
double dummy;
ifstream fin;
int L=profileLength;

//========================================================

cout<<"profile from "<<folder<<fileName<<endl;
cout<<"  profile length = "<<L<<endl;
//========================================================

//for (takeColumn=1;takeColumn<=numberOfColumns;takeColumn++)
{
//read profile
sprintf(fileIn,"%s%s",folder,fileName);
readProfile(L,data,fileIn,numberOfColumns,takeColumn);
//for (i=0;i<L;i++){cout<<i<<"  "<<data[i]<<endl;}

//========================================================
/*
//find minimum of profile
int minPos;
double minVal;
findMin(L,data,minVal,minPos);
cout<<"  profile has minimum at     with min value "<<endl;
cout<<minPos<<"          "<<minVal<<endl;
*/
//========================================================
/*
//average profile
double mean;
averageProfile(L,data,mean);
//cout<<"  mean = "<<mean<<endl;
cout<<"  total = "<<mean*L<<endl;
*/
//========================================================

//find where profile passes 1/2
int shockPos;
double val=0.5;
findValuePass(L,data,val,shockPos);
cout<<"  shock at "<<shockPos<<endl;

//========================================================
}//end for takeColumn

}//end main
