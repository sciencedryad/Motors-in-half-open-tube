//SUBROUTINES TO ANALYZE A PROFILE double data[L]

//=============================================================
//=============================================================
void readProfile(const int& L, double* data, const char dataFile[80],
const int& numberOfColumns, const int& takeColumn)
// reads profile double data[L] from the takeColumn column
//	of file dataFile (which has numberOfColumns columns)
{
int i,j;
char dummyChar[80];
double dummy;
ifstream fin;
	fin.open(dataFile);
		if(!fin){cout<<"Error, can't open file"<<endl;exit(8);}
	// first line: characters
	for(j=1;j<=numberOfColumns+1;j++)
	{
		fin>>dummyChar;
	}//end for j
	// data lines
	for (i=1;i<=L-1;i++)
	{
		for(j=1;j<takeColumn;j++){fin>>dummy;}
		fin>>data[i-1];
		for(j=takeColumn+1;j<=numberOfColumns;j++){fin>>dummy;}
	}//end for i
	fin.close();
	for (i=1;i<=L;i++)
	{
		//cout<<i<<"    "<<data[i-1]<<endl;
	}//end for i
}//end void readProfile
//=============================================================
//=============================================================

void findMax(const int& L, const double* data, double& maxVal, int& maxPos)
// finds maximum of double array data[L]
// if maximum is degenerate, takes most right maximum
{
double array[L];
int i;
//cout<<"calling subroutine findMax"<<endl;
for(i=0;i<L;i++){array[i]=data[i];}
maxPos=0;
maxVal=array[maxPos];
for(i=1;i<L;i++)
{
	if (array[i]>maxVal)
	{
		maxVal=array[i];
		maxPos=i;
	}
}
}//end void findMax

//=============================================================
//=============================================================

void findMin(const int& L, const double* data, double& minVal, int& minPos)
// finds minimum of double array data[L], using findMax
{
double array[L];
int i;
//cout<<"calling subroutine findMin"<<endl;
for(i=0;i<L;i++){array[i]=-data[i];}
findMax(L,array,minVal,minPos);
minVal=-minVal;
}//end void findMin

//=============================================================
//=============================================================

void averageProfile(const int& L, const double* data, double& mean)
// gives mean of array data(L)
{
int i;
mean=0;
for(i=0;i<L;i++)
{
mean = mean + data[i];
}
mean = mean/L;
}//end void averageProfile

//=============================================================
//=============================================================
void findValuePass(const int& L, const double* data, const double& val,int& valPos)
//finds position valPos where data profile last passes the value val
{
int i;
double value;
valPos=0;
value=data[0]-val;
for(i=0;i<L;i++)
{
	if(value*(data[i]-val)<0)
	{
		valPos=i;
		value=data[valPos]-val;
	}
}
}//end void findValuePass
