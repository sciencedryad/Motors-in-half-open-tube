#include<math.h>
#define max(a,b) (((a)>(b))?(a):(b)) 
#define min(a,b) (((a)<(b))?(a):(b)) 

void dataAnalysis
	(	const char dataFile[80], FILETYPES dataFileType,
		const int& numberOfData,const int& n_disc, 
		const char outputFileMean[80],const char outputFileC[80])
// dataFile: file containing data, one double per line
// dataFileType: ASCI or BINARY file
// numberOfData: number of data elements
// n_disc: number of data elements to be discarded at beginning
// outputFileMean: output file with mean, error, tau_int
// outputFileC: output file with correlation function
{
cout<<endl;
cout<<"DATA ANALYSIS for dataFile "<<dataFile<<endl;
//*****************************************************************
// variables
//*****************************************************************
// data variables
int dataNumber = numberOfData - n_disc;
double* data; // array of data
	data = static_cast<double*>(malloc(dataNumber*sizeof(double)));
const int M = 5; // automatic windowing parameter (c in Sokal, p.16)

double mean,meanStd; // data mean and its standard deviation
double dmean;

// autocorrelation variables
double* C;	// autocorrelation function
	C = static_cast<double*>(malloc(dataNumber*sizeof(double)));
double tau_int, tau_intStd;	
	// integrated autocorrelation time and std deviation

// miscellaneous variables
int t,i,n,nt; // loop counter & Co

//*****************************************************************
//read data
//*****************************************************************
ifstream fin(dataFile);
	if(!fin){cout<<"Error! Can't open file!";exit(8);}
	if (dataFileType==ASCI)
	{
		for(t=0;t<n_disc;t++)
			{fin>>dmean;} // discard first n_disc data
		for(t=0;t<dataNumber;t++)
		{
			fin>>data[t];
		}
	}//end if ASCI-file
	else if (dataFileType==BINARY)
	{
		for(t=0;t<n_disc;t++)
			{fin.read((char*)& dmean,sizeof(double));}
		for(t=0;t<dataNumber;t++)
		{
			fin.read((char*)& data[t],sizeof(double));
		}
	}//end if BINARY-file
	else
		{cout<<"dataFileType unknown!"<<endl;exit(8);}
fin.close();

//for(t=0;t<dataNumber;t++)
//	{cout<<data[t]<<"  ";}
//	cout<<endl;

//*****************************************************************
// calculate mean
//*****************************************************************
mean=0; dmean=0; n=0;
for(t=0;t<dataNumber;t++)
{
dmean = dmean + data[t];
n = n + 1;
if(dmean>10000*dataNumber)
	{
		mean = mean + (dmean/n);		//avoid roundoff errors
		n = 0;
		dmean = 0;
	}
}//end for t
mean = mean + dmean/n;

//*****************************************************************
// autocorrelation function and integrated autocorrelation time
//*****************************************************************
// according to A. Sokal, Monte Carlo Methods in Statistical Mechanics,
// 		Foundations and New Algorithms, Cours de Troisieme Cycle de la 
// 		Phsysique en Suisse Romande, Lausanne 1989
// C(t), tau_int: automatic rectangular windowing 
// 	Sokal, eq. (3.9), (3.14), (3.16)
t = 0;
tau_int = 0.5;
while ((t<M*tau_int)&&(t<dataNumber))
	{
		C[t]=0;
		for(i=0;i<(dataNumber-t);i++)
		{
			C[t] = C[t] + (data[i]-mean) * (data[i+t]-mean);
		}
		C[t] = C[t]/(dataNumber-t);
		if(t>0)
			{ 
				C[t] = C[t]/C[0];
				tau_int = tau_int + C[t];
			}
		if(t>=dataNumber)
			{cout<<"ERROR in automatic windowing ana.CPP. Not enough data.";
				exit(8);}
		t = t + 1;
	}//end while t
// now t = Gauss[M*tau_int]
// C[0] still unnormalized

// calculate error of mean (Sokal eq. (2.20))
//	and error of tau_int (Sokal, eq. (3.19))
meanStd = sqrt(2*tau_int*C[0]/dataNumber);
tau_intStd = sqrt( (((float)2)*(2*t-1))/dataNumber ) * tau_int;

// calculate normalized autocorrelation function for 
//	all t <= 5*M*tau_int, Sokal eq. (3.9), 3.14)
nt = min(5*t,dataNumber-1);
//cout<<"autocorrelation function"<<endl;
for(t=0;t<nt;t++)
{
	C[t]=0;
	for(i=0;i<(dataNumber-t);i++)
	{
		C[t] = C[t] + (data[i]-mean) * (data[i+t] - mean);		
	}
C[t] = C[t]/(dataNumber-t);
if(t>0) 
	{
		C[t] = C[t]/C[0];
	}
//cout<<C[t]<<"  ";
}//end for t
C[0]=1;
//cout<<endl;

//*****************************************************************
// output
//*****************************************************************
//cout<<"DATA ANALYSIS for dataFile "<<dataFile<<endl;
cout<<"  output in files "<<outputFileMean<<"  and "<<outputFileC<<endl;
cout<<"  numberOfData = "<<numberOfData
		<<", n_disc = "<<n_disc
		<<", dataNumber = "<<dataNumber
		<<", M*tau_int = "<<nt<<endl;
cout<<"  mean    = "<<mean<<"\t error = "<<meanStd<<endl;
cout<<"  tau_int = "<<tau_int<<"\t  error = "<<tau_intStd<<endl;

ofstream fout(outputFileMean);
	fout<<mean<<endl;
	fout<<meanStd<<endl;
	fout<<tau_int<<endl;
	fout<<tau_intStd<<endl;
fout.close();

fout.open(outputFileC);
//	fout<<nt<<endl;
	for(t=0;t<=nt;t++)
		{fout<<t<<"  "<<C[t]<<endl;}
fout.close();

//*****************************************************************
//calculate effective autocorrelation time
//*****************************************************************
// Sokal eq. (2.38)
/*{
C[0] = 0;
t=0;
int r; 
double tau_eff;
cout<<"effective autocorrelation time:"<<endl;
while(t<tau_int)
{
	r = C[t+1]/C[t];
	if(r>0)
		{
			tau_eff = -1/log(r);
			cout<<tau_eff<<endl;
		}
	t = t + 1;
}//end while t
}//end calculate effective autocorrelation time
*/ 
//*****************************************************************
}// end subroutine dataAnalysis
