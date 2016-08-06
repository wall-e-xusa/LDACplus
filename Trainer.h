class Trainer{


public:
~Trainer();
Trainer(int m,int k,int v,double _alpha,double _beta);
public:
	int** kv;    /// K*V,topic-word����
	int* numK;  ///  K,������ֵ��ܴ���
	int** mk;  ///   m*k,doc-topic����
	int* numM;///    M,�ĵ���������ֵ��ܴ�����
	int k;
	int m;
	int v;
	double alpha;
	double beta;
	//int* doc;
	//int** z;///�ĵ��ʹ�λ����
	double** phi;  ////���ղ�������
	double** theta;/// ���ղ�������
	
public:
	void trian(int **z,int m,int length,int index,int*doc);
	void updateEstimatedParameters();
	private:

int sampleTopicZ(int m,int n,int oldtopic,int*doc);

		








};