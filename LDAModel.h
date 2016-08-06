#pragma once
#include "StdAfx.h"
#include <map>
#include <vector>
//#include "KbaseTest.h"
//#include<iosteam>

#include <string>
#include <iostream>
#include <fstream>
#include "trainer.h"
#include <sstream>
//#define getArraySize(arrayName) (sizeof(arrayName)/sizeof(arrayName[0]));被证明是无效的
using namespace std;
struct word_infor {
  long long id;
  //int *point;
  double weight;
};
 int VocabCompare(const void *a, const void *b) {
    return (((struct word_infor *)b)->weight - ((struct word_infor *)a)->weight)>0?1:-1;
}

class LDAmodel{

public:
	  //map<int,vector<int>> doc;
	  int **z;
	  Trainer* trainer;
	  int num_doc;//文档总数
	  Dict* dict;
	  int max_iterator;
	  int save_iterator;
	  int **idoc;
	  
     
public:
	LDAmodel()
	{
		  dict=new Dict(10000);
	}
	bool initModel(int topic_num,double alpha,double beta,int iterations,int beginSaveIters)
	{
	  
		//if(filename!=NULL)
	 //  { if(!dict->LoadDictFromFile(filename))
		// {
		//		cout<<"载入词典失败"<<endl; ////写入日志记录
		//		return false;
		// }
		// else
		// {
		//	cout<<"载入词典成功"<<endl;
		// }
	 //  }
	  
		if(!dict->LoadWordFromMap())
		{
			cout<<"从map载入词典失败"<<endl;
			return false;
		}
		int m=dict->doc.size();
		num_doc=m;
		if(num_doc==0)
		{
			cout<<"文档数目为0"<<endl;
			return false;
		}
		int v=dict->vocab_size;
		if(v==0)
		{
			cout<<"词典长度为0"<<endl;
			return false;
		}
		z=new int* [m];
		idoc=new int*[m];
		//auto itt;
		for(int i=0;i<m;i++)
		{
		  int size=dict->doc[i].size();
		  z[i]=new int [size];
		  idoc[i]=new int [size];
		  for(int j=0;j<size;j++)
		  {
			  char word[MAX_STRING];
			  strcpy(word,dict->doc[i][j].c_str());
			  idoc[i][j]=dict->SearchVocab(word);
		  }
		}
		trainer=new Trainer(m,topic_num,v,alpha,beta);
		max_iterator=iterations;
		save_iterator=beginSaveIters;


	}
	
	void trainModel(const char * t_w_filename,const char * d_t_filename)
	{
		for(int iterator=0;iterator<max_iterator;iterator++)
		{
			
			for(int i=0;i<num_doc;i++)
			{
				int length =dict->doc[i].size();
				//int* idoc=new int[length];
				//for(int j=0;j<length;j++)
				//{
				//	idoc[j]=doc[i][j];
				//}
				trainer->trian(z,i,length,iterator,idoc[i]);
				//delete[] idoc;
			}
			if(iterator>save_iterator)
			{
				string tempfilename1(t_w_filename);
				string tempfilename2(d_t_filename);
			    stringstream ssa;
				ssa<<iterator;
				string tempIter=ssa.str();
				string filename1=tempIter+"_"+tempfilename1;
				string filename2=tempIter+"_"+tempfilename2;
				saveModel(filename1.c_str(),filename2.c_str());
			}
		}

	}
	bool saveModel(const char* t_w_filename,const char * d_t_filename)
	{
	  ofstream outfile1(t_w_filename);
	  ofstream outfile2(d_t_filename);
	  if (!outfile1 || !outfile2)
      {
        return false;
      }
	  trainer->updateEstimatedParameters();
	  for(int i=0;i<trainer->k;i++)
	  {
		  outfile1<<i<<endl;
		  word_infor* wordinfor=new word_infor[trainer->v];
		  int length=0;
		  for(int j=0;j<trainer->v;j++)
		  {
			
			 word_infor tempword;
			 if(trainer->kv[i][j]>0)
			{ 
			// cout<<trainer->kv[i][j]<<"**";
			 double weight =trainer->phi[i][j];
			 tempword.id=j;
			 tempword.weight=weight;
			 wordinfor[length]=tempword;
			 length++;
			}
			// outfile1<<j<<":"<<weight<<";";
		  }
		  if(length>0)
		  {
			  qsort(&wordinfor[0], length, sizeof(struct word_infor), VocabCompare);
		     for(int i=0;i<length;i++)
		     {
			   char word [100];
			   dict->SearchId( wordinfor[i].id,word);
			   outfile1<<word<<": # "<< wordinfor[i].weight<<";";
		     }
		  }
		  delete []wordinfor;
		  outfile1<<endl;
	  }
	  for(int i=0;i<trainer->m;i++)
	  {
		  outfile2<<i<<endl;
		  word_infor* docinfor=new word_infor[trainer->k];
		  for(int j=0;j<trainer->k;j++)
		  {
			  //outfile2<<j<<":"<<trainer->theta[i][j]<<";";

			 word_infor tempword; 
			 double weight =trainer->theta[i][j];
			 tempword.id=j;
			 tempword.weight=weight;
			 docinfor[j]=tempword;
		  }
		  qsort(&docinfor[0], trainer->k, sizeof(struct word_infor), VocabCompare);
		    for(int i=0;i<trainer->k;i++)
		  {
			   //char word [100];
			  // dict->SearchId( wordinfor[i].id,word);
			  outfile2<< docinfor[i].id<<":"<< docinfor[i].weight<<";";
		  }
		  delete []docinfor;
		  outfile2<<endl;
	  }
		//trainer->theta;
	}
	bool freeModel()
	{
		for(int i=0;i<num_doc;i++)
		{
		  delete []z[i];
		  delete [] idoc[i];

		}
		delete [] z;
		delete [] idoc;
		delete trainer;
		dict->doc.clear();
		delete dict;
		
		return true;
	}
	
};