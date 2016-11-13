#include<fstream.h>
#include<stdlib.h>
#include<iostream.h>
#include<stdio.h>
#include "Assert.CPP"

char folder[80]="Data/";
const int numberOfFiles = 6;
char fileList[numberOfFiles][80];
char fileNameBIN[80];
char fileNameASCI[80];

int main()
{
int i,fileNumber;
double dummy;
//int dummyint;

cout<<"folder for converting binary double files (include /): ";
cin>>folder;

sprintf(fileList[0],"%s%s",folder,"CorrRho_b.dat");
sprintf(fileList[1],"%s%s",folder,"CorrJ_b.dat");
sprintf(fileList[2],"%s%s",folder,"CorrRho_b_tot.dat");
sprintf(fileList[3],"%s%s",folder,"CorrRho_ub_tot.dat");
sprintf(fileList[4],"%s%s",folder,"CorrJ_b_tot.dat");
sprintf(fileList[5],"%s%s",folder,"CorrN.dat");

for(fileNumber=0;fileNumber<numberOfFiles;fileNumber++)
{
	sprintf(fileNameBIN,"%s",fileList[fileNumber]);
	sprintf(fileNameASCI,"%s%s",fileNameBIN,"ASCI");
	cout<<"converting file no "<<fileNumber
			<<"\t name of binary: "<<fileNameBIN
			<<"\t name of ASCI "<<fileNameASCI<<endl;
	ifstream fin(fileNameBIN);
		if(!fin){cout<<"Error, can't open file"<<endl;ASSERTperm(0);}
	ofstream fout(fileNameASCI);
		if(!fout){cout<<"Error, can't open file"<<endl;ASSERTperm(0);}
		i=0;
		while(!fin.eof())
			{
				if(i>0)
					{
						fout<<dummy<<endl;
					}
				i=i+1;
				fin.read((char*)& dummy, sizeof(double));
//				fin.read((char*)& dummyint, sizeof(int));
			}//end while !fin.eof()
	fout.close();
	fin.close();
}//end for fileNumber

return 0;
}
