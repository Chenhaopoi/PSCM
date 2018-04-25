// This is new version test. copyright by Poi!
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;
int SB[100][100]={0};
int cost[100];
int Re[100];
short x[100]={0}; 
int E,numS,P,minK; 
int minob=1;
int lmin[30]={0};
void readinstance()
{
	ifstream insfile; 
    insfile.open("instance01.txt");   
    insfile>>E>>numS>>P;
    for (int i=1;i<=E;i++)
    insfile>>Re[i];
    for (int i=1;i<=numS;i++)
    insfile>>cost[i];
    int temp[1000]={0};
    int k=0;
    while (!insfile.eof())
    {
	    insfile>>temp[++k];
	}
    insfile.close();
    if (temp[k]==0) k--;
    int t=1,i=1,j=1;
	while (t<=k)
	{
		SB[i][j++]=temp[t++];
		if ((temp[t]<SB[i][j-1])&&(j>1)&&(temp[t]!=0)) 
		{
			SB[i][0]=j-1;
			i++;
			j=1;
		}
		SB[i][0]=j-1;
	}
}
void generatex (long n)
{
	int i=1; 
	while (n!=0)
	{
		x[i]=n%2;
		n/=2;
		i++;
	} 
}
void findmin ()
{
	int K=0,tcost=0;
	for (int i=1;i<=numS;i++)
	{
		if (x[i]==1) 
		{
			K++;
			tcost+=x[i]*cost[i];
		}
	} 
	if (tcost<minob)
	{  
		minob=tcost;
		minK=K;
		for (int i=1;i<=numS;i++)
		lmin[i]=x[i];
	}
}
/*void findcover (int n)
{
	int numelment[E+1]={0};
	int satisfyRe=0;
	for (int i=1;i<=numS;i++)
	{
		if ((x[i]==1)&&(SB[i][0]!=0))
		{
			for (int j=1;j<=SB[i][0];j++)
			{
				numelment[SB[i][j]]++;	
			}
		}
	}
	for (int l=1;l<=E;l++)
	{
		if (numelment[l]>=Re[l]) satisfyRe++;
	}
	if ((satisfyRe>=P)) findmin();
}*/
int testmin ()
{
	ifstream testfile("solution02.txt"); 
	int kt,costt,i=0;
	testfile>>kt>>costt; 
	int tsb[kt+3]={0};
	if (kt<1) 
	{
		cout<<"Wrong format"; exit(0);
	} 
	else
	{	
	   while ((!testfile.eof())&&(i<kt))
 	   {
	   		testfile>>tsb[++i];
	   		if ((tsb[i]>numS)||(tsb[i]<=0)) 	
			   {
			   		cout<<"Wrong format";
			   		exit(0);
			   }
	   }
	   if (i<kt) 
	   {
	   		cout<<"Wrong format";exit(0);
	   } 
	   else
	   {
	   	    testfile>>tsb[i+1];
			if (tsb[i+1]>0)	{cout<<"Wrong format"; exit(0);}
	   }
	}
	int ssb[numS+1]={0};
	for (i=1;i<=kt;i++)
	{
		ssb[tsb[i]]++;
		if (ssb[tsb[i]]>1) {cout<<"Wrong format"; exit(0);}  
	}   // find the wrong format include # element(set) k!= #of set B or input same set B
	testfile.close();
	int rcost=0;
    for (i=1;i<=numS;i++)
	{
		if (ssb[i]==1) rcost+=cost[i];
	}
	if (rcost!=costt) {cout<<"incorrect cost"; exit(0);}
	int testele[E+1]={0};
	for (i=1;i<=numS;i++)
	{
		if (ssb[i]>0) 
		{
			for (int j=1;SB[i][j]>0;j++)
			testele[SB[i][j]]++;		    
		}
		testele[0]=0;
	}   // compute wether the cost is correct or not 
	for (i=1;i<=E;i++)
	{
		if (testele[i]>0) testele[0]++;
	}
	int Pbool=0;
	for (i=1;i<=E;i++)
	{
		if (testele[i]>=Re[i]) 	Pbool++;  //compute how many elements satisfied with Re
	}
	if (Pbool<P) 
	{
		cout<<"infeasible"; exit(0);	
	}
	bool pmin=true;
	for ( i=1;i<=numS;i++)
	{
		Pbool=0; 
		if (ssb[i]==1) 
		{
			for (int j=1;SB[i][j]>0;j++)
			{
				testele[SB[i][j]]--;
			}		    
    	
		for (int j=1;j<=E;j++)
		{
			if (testele[j]>=Re[j]) 	Pbool++;  //compute how many elements satisfied with Re
		}	 	
		if (Pbool>P) 
		{
			pmin=false; 
			break;
		}
			for (int j=1;SB[i][j]>0;j++)
			testele[SB[i][j]]++;
			//cout<<endl;
	 	}
	}
	
	if (pmin) 
	{ 
		cout<<"everything is correct!"; 
		exit(0);
	}
	else 
	{
		cout<<"not minimal"; 
		exit(0);
 	}
	
}
int main()
{
	readinstance();
	/*long comb=1;
	for (int i=1;i<=numS;i++)
	comb*=2;
    for (int i=0;i<comb;i++)
	{
		generatex(i);
		findcover(E);
	}*/
	testmin();
	return 0;
}
