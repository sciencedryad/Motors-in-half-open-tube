#include<iostream.h>
#include<fstream.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#include<time.h>
#include "Assert.CPP"

enum FILETYPES { ASCI, BINARY};
FILETYPES dataFileType = BINARY;

int numberOfMeasurements;
int numberOfMCSteps;
int measureInterval;
int equilibrationSteps;

int numberOfData;
int n_disc; // number of data at beginning to be discarded

#include "ana.CPP"

char folder[80];
const int numberOfFiles=6;
char fileList[numberOfFiles][80];

int main()
{
char infoFile[80];
char dataFile[80];
char outputFileMean[80];
char outputFileCorr[80];
time_t time1,time2;
double timediff;
int fileNumber,fileNumber2;

time (&time1);

//*****************************************************************
// make names of files to be analyzed
//*****************************************************************
cout<<"folder for data analysis (include /): ";
cin>>folder;
sprintf(fileList[0],"%s","CorrRho_b.dat");
sprintf(fileList[1],"%s","CorrJ_b.dat");
sprintf(fileList[2],"%s","CorrRho_b_tot.dat");
sprintf(fileList[3],"%s","CorrRho_ub_tot.dat");
sprintf(fileList[4],"%s","CorrJ_b_tot.dat");
sprintf(fileList[5],"%s","CorrN.dat");
sprintf(infoFile,"%s%s",folder,"MeasureInfo.dat");

//*****************************************************************
// read general info
//*****************************************************************
ifstream fin(infoFile);
  fin>>numberOfMeasurements;
	fin>>numberOfMCSteps;
	fin>>measureInterval;
	fin>>equilibrationSteps;
fin.close();
numberOfData = numberOfMeasurements/measureInterval;
//if(numberOfData<100)
//	{cout<<"NumberOfData too small!"; exit(8);}

n_disc=0;
//numberOfData=200; //n_disc=10;
//n_disc = 20000;
//numberOfData=40000;

cout<<"numberOfMeasurements = "<<numberOfMeasurements
		<<", measureInterval = "<<measureInterval
		<<", numberOfMCSteps = "<<numberOfMCSteps
		<<", equilibrationSteps = "<<equilibrationSteps<<endl;
cout<<"numberOfData = "<<numberOfData
		<<", n_disc = "<<n_disc<<endl;

ASSERTperm(numberOfMeasurements>0);
ASSERTperm(measureInterval>=0);
ASSERTperm(numberOfMCSteps>0);
ASSERTperm(equilibrationSteps>=0);
ASSERTperm(numberOfData>1);
ASSERTperm(n_disc>=0)
ASSERTperm(n_disc<numberOfData);

//*****************************************************************
// DATA ANALYSIS
//*****************************************************************
for(fileNumber=0;fileNumber<numberOfFiles;fileNumber++)
//for(fileNumber=0;fileNumber<=2;fileNumber++)
{
	fileNumber2=fileNumber;
//	fileNumber2 = fileNumber*fileNumber;
	sprintf(dataFile,"%s%s",folder,fileList[fileNumber2]);
	sprintf(outputFileMean,"%s%s%s",folder,"AnaMean",fileList[fileNumber2]);
	sprintf(outputFileCorr,"%s%s%s",folder,"Ana",fileList[fileNumber2]);
	dataAnalysis(dataFile,dataFileType,numberOfData,n_disc,
			outputFileMean,outputFileCorr);
	time (&time2);
	timediff = difftime(time2,time1);
	cout<<"	time used: "<<timediff<<" sec"<<endl;
}

time (&time2);
timediff = difftime(time2,time1);
cout<<endl;
cout<<"time used for data analysis: "<<timediff<<" sec"<<endl;

return 0;
}// end main
