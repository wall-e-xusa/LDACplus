// LDATest.cpp : �������̨Ӧ�ó������ڵ㡣
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


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
	

	//		std::ifstream ifs("�»���ؼ��ʴʵ�-xs.txt");
	//
	//    if(!ifs)
	//  {
	//      cout<<"���ļ�ʧ��"<<endl;
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
	//		//_CrtDumpMemoryLeaks();//��Ҫ���

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
   dict->LoadDictFromFile("�»���ؼ��ʴʵ�-xs.txt"); ///���˴ʴʵ䡣����

   ///����
  // ldamodel.dict->doc//�� doc��int��vector<string>������ѵ�������ݡ� dict�ʵ�����ڹ���
   delete dict;
   ldamodel.initModel(100,0.5,0.01,1000,988);
   ldamodel.trainModel("����-��.txt","�ĵ�-����.txt");
   ldamodel.freeModel();


}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
