
void num_10_to_2_8(int num,char arr[9]);//��һ��10���Ƶ���ת��Ϊһ��2���Ƶ��ַ���(8λ)

long long up_ipaddress_to_ipnum(int a1,int a2,int a3,int a4,int a5);
//��IP��ַ���ĸ����ֺ�����ǰ׺��int���룬����IP��ַת��Ϊʮ���Ʊ�ʾ�����ޣ�

long long down_ipaddress_to_ipnum(int a1,int a2,int a3,int a4,int a5);
//��IP��ַ���ĸ����ֺ�����ǰ׺��int���룬����IP��ַת��Ϊʮ���Ʊ�ʾ�����ޣ�

int match(long long in1,long long in2,int in3,int in4,int in5,long long aup,
long long adown,long long bup,long long bdown,int cup,int cdown,int dup,
int ddown,int eup,int edown,int i);//����ƥ�����������


	struct rulelist { //����ṹ���Ź�������
		long long up_ip_s;//ԴIP��ַ����
		long long down_ip_s;//ԴIP��ַ����
		long long up_ip_d;//Ŀ��IP��ַ����
		long long down_ip_d;//Ŀ��IP��ַ����
		int up_port_s;//Դ�˿�����
		int down_port_s;//Դ�˿�����
		int up_port_d;//Ŀ�Ķ˿�����
		int down_port_d;//Ŀ�Ķ˿�����
		int up_agreement;//Э������
		int down_agreement;//Э������
	} rulefile[1000];