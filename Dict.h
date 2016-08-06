#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <map>
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_STRING 100
#define VOCAB_HASH_SIZE 30000000

     

struct vocab_word {
  long long id;
  //int *point;
  char *word;
};
class Dict
{


public:	std::map<int,std::vector<std::string>> doc;//额外定义字段
		long long vocab_size;// = 0;
private: 
	int *vocab_hash;
	struct vocab_word* vocab;
    long long vocab_max_size;/* = 1000,*/ 


public :
	Dict(const int vocab_Max_Size=10000)
	{
		vocab_size=0;
		vocab_max_size=vocab_Max_Size;
		vocab = (struct vocab_word *)calloc(vocab_max_size, sizeof(struct vocab_word));
		vocab_hash = (int *)calloc(VOCAB_HASH_SIZE, sizeof(int));
	    for (long long a = 0; a < VOCAB_HASH_SIZE; a++) 
        {
	       vocab_hash[a] = -1;
        }
	}
	~Dict()
	{
		
		for(int i=0;i<vocab_size;i++)
		{
			
			
			free(vocab[i].word);
		}
		free(vocab);
		free(vocab_hash);
	}


void ReadWord(char *word, FILE *fin) {
   int a = 0, ch;
   while (!feof(fin)) {
    ch = fgetc(fin);
    if (ch == 13) continue;
    if ((ch == ' ') || (ch == '\t') || (ch == '\n')) {
      if (a > 0) {
        if (ch == '\n') ungetc(ch, fin);
        break;
      }
      if (ch == '\n') {
        strcpy(word, (char *)"</s>");
        return;
      } else continue;
    }
    word[a] = ch;
    a++;
    if (a >= MAX_STRING - 1) a--;   // Truncate too long words
  }
  word[a] = 0;
}
int SearchVocab(char *word) {
  unsigned int hash = GetWordHash(word);
  while (1) {
    if (vocab_hash[hash] == -1) return -1;
    if (!strcmp(word, vocab[vocab_hash[hash]].word)) return  vocab[vocab_hash[hash]].id;
    hash = (hash + 1) % VOCAB_HASH_SIZE;
  }
  return -1;
}
int SearchId(int id,char* word)
{
	if(id>vocab_size)return -1;
	if(id<0)return -1;
	if(word==NULL)return -1;
	strcpy(word,vocab[id].word);
	return 1;

}
bool LoadWordFromMap()
{
	if(vocab_size!=0)
	{
		std::cout<<"词典已通过文件加载，不需要通过map加载"<<std::endl;
		return false;
	}
	if(doc.size()==0)
	{
		std::cout<<"map为空不需要加载"<<std::endl;
	}
	for(auto itt=doc.begin();itt!=doc.end();itt++)
	{
		for(int i=0;i<itt->second.size();i++)
		{
			char word[MAX_STRING];
			strcpy(word,itt->second[i].c_str());
			int fig=SearchVocab(word);
			if(fig==-1)
			{
				 AddWordToVocab(word);
			}
			else
			{
				continue;
			}
		}
	}
	return true;
}
bool LoadDictFromFile( const char *filename) {
  char word[MAX_STRING];
  FILE *fin;
  long long a, i;
  fin = fopen(filename, "rb");
  if (fin == NULL) {
    printf("ERROR: training data file not found!\n");
	return false;
    //exit(1);
  }
  vocab_size = 0;
  AddWordToVocab((char *)"</s>");
  while (1) {
    ReadWord(word, fin);
    if (feof(fin)) break;
   
    i = SearchVocab(word);
    if (i == -1) {
      a = AddWordToVocab(word);
     
    } else continue;
   
  }
 
  fclose(fin);
  return true;
}
///输出词典
void SaveVocab(const char* outfilename) {
  long long i;
  FILE *fo = fopen(outfilename, "wb");
  for (i = 0; i < vocab_size; i++) fprintf(fo, "%s %lld\n", vocab[i].word, vocab[i].id);
  fclose(fo);
}


private :
int GetWordHash(char *word) {
  unsigned long long a, hash = 0;
  for (a = 0; a < strlen(word); a++) hash = hash * 257 + word[a];
  hash = hash % VOCAB_HASH_SIZE;
  return hash;
}
int AddWordToVocab(char *word) {
  unsigned int hash, length = strlen(word) + 1;
  if (length > MAX_STRING) length = MAX_STRING;
  vocab[vocab_size].word = (char *)calloc(length, sizeof(char));
  strcpy(vocab[vocab_size].word, word);
  vocab[vocab_size].id =vocab_size;
  vocab_size++;
  // Reallocate memory if needed
  if (vocab_size + 2 >= vocab_max_size) {
    vocab_max_size += 1000;
    vocab = (struct vocab_word *)realloc(vocab, vocab_max_size * sizeof(struct vocab_word));
  }
  hash = GetWordHash(word);
  while (vocab_hash[hash] != -1) hash = (hash + 1) % VOCAB_HASH_SIZE;
  vocab_hash[hash] = vocab_size - 1;
  return vocab_size - 1;
}
};