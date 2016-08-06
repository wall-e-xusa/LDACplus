#include "StdAfx.h"
#include "trainer.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

Trainer::Trainer(int _m,int _k,int _v,double _alpha,double _beta)///length_k主题个数，length_v,词表长度。
{
	k=_k;
	m=_m;
	v=_v;
	alpha=_alpha;
	beta=_beta;
	kv=new int*[k];
	for(int i=0;i<k;i++)
	{
		 kv[i]=new int[v];
	
	    for(int j=0;j<v;j++)
	    {
		  kv[i][j]=0;
	    }
	}
	numK=new int[k];
	for(int i=0;i<k;i++)
	{
		numK[i]=0;
	}
	mk=new int *[m];
	for(int i=0;i<m;i++)
	{
		mk[i]=new int[k];
		for(int j=0;j<k;j++)
		{
			mk[i][j]=0;
		}
	}
	numM=new int[m];
	for(int i=0;i<m;i++)
	{
		numM[i]=0;
	}

	phi=new double*[k];
	for(int i=0;i<k;i++)
	{
		phi[i]=new double[v];
		for(int j=0;j<v;j++)
	    {
		  phi[i][j]=0.0;
	    }
	}

	theta=new double *[m];
	for(int i=0;i<m;i++)
	{
		theta[i]=new double[k];
		for(int j=0;j<k;j++)
		{
			theta[i][j]=0.0;
		}
	}


}
Trainer::~Trainer()
{

	for(int i=0;i<k;i++)
	{
		delete []kv[i];
	}
	delete []kv;
	delete []numK;
	
	for(int i=0;i<m;i++)
	{
		delete[]mk[i];
	}
	delete []mk;
	delete []numM;

	for(int i=0;i<k;i++)
	{
		delete []phi[i];
	}
	delete []phi;
	
	for(int i=0;i<m;i++)
	{
		delete[]theta[i];
	}
	delete []theta;
}
void Trainer::trian(int **z,int m,int length,int index,int*doc)
{
	if(index==0)
	{
	    srand((unsigned)time(0));
		//std::cout<<length<<std::endl;
	   for(int n=0;n<length;n++)
	  {
	
		int inittopic=rand()%k;
		z[m][n]=inittopic;
		kv[inittopic][doc[n]]++;
	    numK[inittopic]++;
	    mk[m][inittopic]++;
	  }
       numM[m]=length;

	}
	else
	{
	  for(int n=0;n<length;n++)
	  {
		int oldtopic=z[m][n];
		z[m][n]=sampleTopicZ(m,n,oldtopic,doc);
	  }
	}

}
int Trainer::sampleTopicZ(int m,int n,int oldtopic,int *doc)
{
	
	kv[oldtopic][doc[n]]--;
	numK[oldtopic]--;
	numM[m]--;
	mk[m][oldtopic]--;
	double *p=new double[k];
	for(int i=0;i<k;i++)
	{
		p[i]=((mk[m][i]+alpha)/(numM[m]+k*alpha))*((kv[i][doc[n]]+beta)/(numK[i]+v*beta));
	}
	for(int j=1;j<k;j++)
	{
		p[j]=p[j]+p[j-1];	
	}
	//std::cout<<std::endl;
    srand((unsigned)time(0));   
	double u=(rand()%100)*0.01*p[k-1];
	int newtopic;
	for(newtopic=0;newtopic<k;newtopic++)
	{
		if(u<p[newtopic])break;
	


	}
	//if(newtopic==k)newtopic=newtopic-1;
	kv[newtopic][doc[n]]++;
	numK[newtopic]++;
	numM[m]++;
	mk[m][newtopic]++;
	delete p;
	//std::cout<<newtopic<<std::endl;
	return newtopic;

}

void Trainer::updateEstimatedParameters()
{

	for(int i = 0; i< k; i++)
	{
		for(int t = 0; t < v; t++)
		{
			//if(kv[i][t])
			//{
			//	//std::cout<<kv[i][t]<<std::endl;
			//}
	       //std::cout<<numK[oldtopic]<<std::endl;
	//std::cout<<numM[m]<<std::endl;
	//std::cout<<mk[m][oldtopic]<<std::endl;
		    phi[i][t] = (kv[i][t] + beta) / (numK[i] + v * beta);
			//std::cout<<phi[i][t]<<std::endl;
		}
	}
		
	for(int j= 0; j< m; j++)
	{
	   for(int i = 0; i < k; i++)
		{
		  theta[j][i] = (mk[j][i] + alpha) / (numM[j] + k * alpha);
		}
	}
}