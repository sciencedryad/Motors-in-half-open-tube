#include "Definitions.CPP"

const int numberOfFolders = 1;
char folderList[numberOfFolders][80];

/*
char outJ[80]="ClosedRes/ResJtotFin.dat";
char outJam[80]="ClosedRes/ResJam.dat";
*/

char outJ[80]="ResTest/ResJtot.dat";
char outJam[80]="ResTest/ResJam.dat";

/*
char outJ[80]="PeriRes/ResJ_tot1.dat";
char outJam[80]="PeriRes/ResJam.dat";
*/

const int arrayLength = 1000;//to avoid dynamic allocation


void sortIntArray(int* array, int* sortedArray, const int& length);

int main()
{
int folderNumber;
char fileIn[80];
int motorNumber;
int L;
int i;
int dummy;
double boundDensity[arrayLength];
double boundCurrent[arrayLength-1];
double avBoundCurrent[numberOfFolders];
double avBoundCurrentSorted[numberOfFolders];
int motorN[numberOfFolders];
int motorNSorted[numberOfFolders];
int jamLength[numberOfFolders];
int jamLengthSorted[numberOfFolders];

for (i=0;i<numberOfFolders;i++)
{
//	sprintf(folderList[i],"%s%i%s","Closed",i+1,"/");
//	sprintf(folderList[i],"%s%i%s","Period",i+1,"/");
}
sprintf(folderList[i],"%","ClosEventsTau1/");

//open output files
ofstream foutJ(outJ);
		if(!foutJ){cout<<"Error, can't open file"<<endl;ASSERTperm(0);}
ofstream foutJam(outJam);
		if(!foutJam){cout<<"Error, can't open file"<<endl;ASSERTperm(0);}

ifstream fin;
cout<<"Analysing data from files: "<<endl;
//file loop
for (folderNumber=0;folderNumber<numberOfFolders;folderNumber++)
{
//read simulation parameters
	sprintf(fileIn,"%s%s",folderList[folderNumber],"MeasureInfo.dat");
	cout<<"  "<<fileIn<<endl;
	fin.open(fileIn);
		if(!fin){cout<<"Error, can't open file"<<endl;ASSERTperm(0);}
		for (i=0;i<5;i++){fin>>motorNumber;}
		for (i=0;i<3;i++){fin>>L;}
	fin.close();
	if (L>=arrayLength)
		{cout<<"ERROR! TubeLength longer than expected!"<<endl;ASSERTperm(0);}
	//cout<<"motorNumber = "<<motorNumber<<endl;
	//cout<<"tubeLength = "<<L<<endl;
//read current profiles, calculate average
	sprintf(fileIn,"%s%s",folderList[folderNumber],"ResJ_b.dat");
	fin.open(fileIn);
		if(!fin){cout<<"Error, can't open file"<<endl;ASSERTperm(0);}
		avBoundCurrent[folderNumber] = 0;
		for (i=0;i<L-1;i++)
		{
			fin>>dummy;
			fin>>boundCurrent[i];
			avBoundCurrent[folderNumber] 
				= avBoundCurrent[folderNumber] + boundCurrent[i];
			//cout<<dummy<<"  "<<boundCurrent[i]<<endl;;
		}//end for i
		avBoundCurrent[folderNumber] = avBoundCurrent[folderNumber]/(L-1);
	fin.close();
//read density profiles
	sprintf(fileIn,"%s%s",folderList[folderNumber],"ResRho_b.dat");
	fin.open(fileIn);
		if(!fin){cout<<"Error, can't open file"<<endl;ASSERTperm(0);}
		for (i=0;i<L;i++)
		{
			fin>>dummy;
			fin>>boundDensity[i];
			//cout<<dummy<<"  "<<boundDensity[i]<<endl;
		}//end for i
	fin.close();
//calculate jam length
	i=0;
	while ((boundDensity[i]<0.5)&&(i<tubeLength)) {i=i+1;} 
	motorN[folderNumber]=motorNumber;
	jamLength[folderNumber] = L - i;
	//cout<<motorN[folderNumber]<<"  "<<jamLength[folderNumber]<<endl;
}//end for folderNumber
//sort jam lengths
	sortIntArray(motorN,motorNSorted,folderNumber);
	for (folderNumber=0;folderNumber<numberOfFolders;folderNumber++)
	{
		for (i=0;i<numberOfFolders;i++)
		{
			if (motorNSorted[folderNumber]==motorN[i])
			{	
				jamLengthSorted[folderNumber]=jamLength[i];
				avBoundCurrentSorted[folderNumber]=avBoundCurrent[i];
			}//end if
		}//end for i
	}//end for folderNumber
//write output to files
	for (folderNumber=0;folderNumber<numberOfFolders;folderNumber++)
	{
		//cout<<"  "<<motorNSorted[folderNumber]<<"  "
		//		<<jamLengthSorted[folderNumber]<<endl;
		foutJam.width(6); 
		foutJam.setf(ios::left);
		foutJam<<motorNSorted[folderNumber];
		foutJam<<jamLengthSorted[folderNumber]<<endl;
		foutJ.width(6); 
		foutJ.setf(ios::left);
		foutJ<<motorNSorted[folderNumber];
		foutJ.precision(6);
		foutJ.setf(ios::showpoint|ios::fixed);
		foutJ<<avBoundCurrentSorted[folderNumber]<<endl;
	}//end for folderNumber

//close output files
foutJ.close();
foutJam.close();

cout<<"output written to "<<outJ<<" and "<<outJam<<endl;

return 0;
}//end main

//------------------------------------------------------------------
//------------------------------------------------------------------

void sortIntArray(int* array, int* sortedArray, const int& length)
{
if (length>arrayLength){cout<<"ERROR! ArrayLength!";ASSERTperm(0);}
int dummy;
int i,j;
for (i=0;i<length;i++)
{
	sortedArray[i]=array[i];
}
for (i=0;i<length;i++)
{
	for (j=i+1;j<length;j++)
	{
		if (sortedArray[j]<sortedArray[i])
		{
			dummy=sortedArray[i];
			sortedArray[i]=sortedArray[j];
			sortedArray[j]=dummy;
		}//end if
	}//end for j
}//end for i
return;
}//end subroutine sortIntArray
