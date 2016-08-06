class Trainer{


public:
~Trainer();
Trainer(int m,int k,int v,double _alpha,double _beta);
public:
	int** kv;    /// K*V,topic-word矩阵
	int* numK;  ///  K,主题出现的总次数
	int** mk;  ///   m*k,doc-topic矩阵
	int* numM;///    M,文档中主题出现的总次数。
	int k;
	int m;
	int v;
	double alpha;
	double beta;
	//int* doc;
	//int** z;///文档和词位矩阵
	double** phi;  ////最终参数矩阵
	double** theta;/// 最终参数矩阵
	
public:
	void trian(int **z,int m,int length,int index,int*doc);
	void updateEstimatedParameters();
	private:

int sampleTopicZ(int m,int n,int oldtopic,int*doc);

		








};