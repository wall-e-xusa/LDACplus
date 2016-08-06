// LDATest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "LDATest.h"
#include "Dict.h"
#include <iostream>
#include <fstream>
#include <string>
//#include "KbaseTest.h"
#include "LDAmodel.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: 在此处为应用程序的行为编写代码。
	

	//		std::ifstream ifs("新机标关键词词典-xs.txt");
	//
	//    if(!ifs)
	//  {
	//      cout<<"打开文件失败"<<endl;
	//   }
	//string temp="";
	//
	//while(getline(ifs,temp)!= '\0')
	//{
	//	
	//	//CString aa(temp.c_str());
	//	int id=dict->SearchVocab((char*)temp.c_str());
	//		if(id<0)
	//		{
	//			cout<<temp<<endl;
	//		}
	//	
	//		//_CrtDumpMemoryLeaks();//重要语句

	//}
	//	dict->SaveVocab("outdict.txt");
	//
   /*word_infor* wordinfor =new word_infor[2];
   word_infor temp1;
   temp1.id=0;
   temp1.weight=2.0;
   word_infor temp2;
   temp2.id=1;
   temp2.weight=3.0;
   wordinfor[0]=temp1;
   wordinfor[1]=temp2;*/
   //qsort(&wordinfor[0],2, sizeof(struct word_infor), VocabCompare);
	/*cout<<wordinfor[0].id<<endl;*/
   LDAmodel ldamodel;
   Dict *dict=new Dict();
   dict->LoadDictFromFile("新机标关键词词典-xs.txt"); ///过滤词词典。。。

   ///内容
  // ldamodel.dict->doc//在 doc（int，vector<string>）载入训练的内容。 dict词典可用于过滤
   delete dict;
   ldamodel.initModel(100,0.5,0.01,1000,988);
   ldamodel.trainModel("主题-词.txt","文档-主题.txt");
   ldamodel.freeModel();


}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
