#include <stdio.h>
#include <string.h>
#include <math.h>

void num_10_to_2_8(int num, char arr[9]) {
	int i;
	for (i = 7; i >= 0; i--) {
		arr[i] = '0';
	}
	for (i = 7; i >= 0; i--) {
		arr[i] = num % 2 + 48;
		num = num / 2;
	}
}


long long up_ipaddress_to_ipnum(int a1, int a2, int a3, int a4, int a5) {
	long long ipad = 0;
	char ipad1[9], ipad2[9], ipad3[9], ipad4[9];
	num_10_to_2_8(a1, ipad1);//��ǰ�ĸ�
	num_10_to_2_8(a2, ipad2);//����ת��
	num_10_to_2_8(a3, ipad3);//Ϊ��λ��
	num_10_to_2_8(a4, ipad4);//������
	int i;
	char ss[33];//ͳһ�����һ��
	for (i = 0; i < 8; i++)
		ss[i] = ipad1[i];
	for (i = 8; i < 16; i++)
		ss[i] = ipad2[i - 8];
	for (i = 16; i < 24; i++)
		ss[i] = ipad3[i - 16];
	for (i = 24; i < 32; i++)
		ss[i] = ipad4[i - 24];
	while (a5 < 32) {//��������ǰ׺��1
		ss[a5] = 49;
		a5++;
	}
	for (i = 0; i < 32; i++)
		ipad += pow(2, i) * (ss[31 - i] - 48);
	return ipad;
}


long long down_ipaddress_to_ipnum(int a1, int a2, int a3, int a4, int a5) {
	long long ipad = 0;
	char ipad1[9], ipad2[9], ipad3[9], ipad4[9];
	num_10_to_2_8(a1, ipad1);
	num_10_to_2_8(a2, ipad2);
	num_10_to_2_8(a3, ipad3);
	num_10_to_2_8(a4, ipad4);
	int i;
	char ss[33];
	for (i = 0; i < 8; i++)
		ss[i] = ipad1[i];
	for (i = 8; i < 16; i++)
		ss[i] = ipad2[i - 8];
	for (i = 16; i < 24; i++)
		ss[i] = ipad3[i - 16];
	for (i = 24; i < 32; i++)
		ss[i] = ipad4[i - 24];
	while (a5 < 32) {//��������ǰ׺��0
		ss[a5] = 48;
		a5++;
	}
	for (i = 0; i < 32; i++)
		ipad += pow(2, i) * (ss[31 - i] - 48);
	return ipad;
}


int match(long long in1, long long in2, int in3, int in4, int in5, long long aup,
          long long adown, long long bup, long long bdown, int cup, int cdown, int dup,
          int ddown, int eup, int edown, int i) {
	if (!(in1 >= adown && in1 <= aup))//ƥ��ԴIP��ַ
		return -1;
	if (!(in2 >= bdown && in2 <= bup))//ƥ��Ŀ��IP��ַ
		return -1;
	if (!(in3 >= cdown && in3 <= cup))//ƥ��Դ�˿�
		return -1;
	if (!(in4 >= ddown && in4 <= dup))//ƥ��Ŀ�Ķ˿�
		return -1;
	if (!(in5 >= edown && in5 <= eup) && (edown != 0 || eup != 0)) //ƥ��Э��
		return -1;
	return i;
}


void packet_classify(char file1[10], char file2[10]) {

	FILE *fp1;//���ݼ�ָ��
	FILE *fp2;//����ָ��
	FILE *fp3;//����ļ�ָ��

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

	int i = 0; //����������¼��������
	int rul_ip1, rul_ip2, rul_ip3, rul_ip4, sign_ip1; //ԴIP���ĸ����ֺ�����ǰ׺
	int rul_ip5, rul_ip6, rul_ip7, rul_ip8, sign_ip2; //Ŀ��IP���ĸ����ֺ�����ǰ׺
	char signip1, signip2, signip3, signip4; //�������ַ���ʽ��ȡ����ǰ׺
	int sign1;//�ж϶�ȡ�ļ��Ƿ����

	fp2 = fopen(file2, "r"); //�򿪹����ļ���ֻ��ģʽ

	fgetc(fp2);//��ȡ��һ��@
	do {
		fscanf(fp2, "%d.%d.%d.%d/%d", &rul_ip1, &rul_ip2, &rul_ip3, &rul_ip4, &sign_ip1);//��ȡԴIP��ַ
		rulefile[i].up_ip_s = up_ipaddress_to_ipnum(rul_ip1, rul_ip2, rul_ip3, rul_ip4, sign_ip1);
		rulefile[i].down_ip_s = down_ipaddress_to_ipnum(rul_ip1, rul_ip2, rul_ip3, rul_ip4, sign_ip1);

		fscanf(fp2, "%d.%d.%d.%d/%d", &rul_ip5, &rul_ip6, &rul_ip7, &rul_ip8, &sign_ip2);//��ȡĿ��IP��ַ
		rulefile[i].up_ip_d = up_ipaddress_to_ipnum(rul_ip5, rul_ip6, rul_ip7, rul_ip8, sign_ip2);
		rulefile[i].down_ip_d = down_ipaddress_to_ipnum(rul_ip5, rul_ip6, rul_ip7, rul_ip8, sign_ip2);

		fscanf(fp2, "%d : %d", &rulefile[i].down_port_s, &rulefile[i].up_port_s);
		fscanf(fp2, "%d : %d", &rulefile[i].down_port_d, &rulefile[i].up_port_d);
		fscanf(fp2, "%i/%i", &rulefile[i].down_agreement, &rulefile[i].up_agreement);
		fgetc(fp2);//��ȡ�س�
		i++;
	} while ((sign1 = fgetc(fp2)) != EOF); //��ȡ��һ�е�@����EOF

	fclose(fp2);//�رչ����ļ�

	sign1 = 1; //����sign1


	int sign2;
	long long in1, in2;
	int t = 0;
	int in3, in4, in5;
	int result = -1;


	fp3 = fopen("res.txt", "w"); //��������res.txt

	fp1 = fopen(file1, "r"); //�����ݼ��ļ���ֻ��ģʽ

	do {
		if (sign2 = fscanf(fp1, "%lld", &in1) == EOF)
			break;

		fscanf(fp1, "%lld", &in2);//��ȡ���ݼ�
		fscanf(fp1, "%d", &in3);
		fscanf(fp1, "%d", &in4);
		fscanf(fp1, "%d", &in5);

		for (t = 0; t < i; t++) {//ѭ������ƥ�����
			result = match(in1, in2, in3, in4, in5, rulefile[t].up_ip_s, rulefile[t].down_ip_s, rulefile[t].up_ip_d,
			               rulefile[t].down_ip_d, rulefile[t].up_port_s, rulefile[t].down_port_s, rulefile[t].up_port_d, rulefile[t].down_port_d,
			               rulefile[t].up_agreement, rulefile[t].down_agreement, t);
			if (result != -1)
				break;
		}
		fprintf(fp3, "ԴIP��ַ:%-15lldĿ��IP��ַ:%-15lldԴ�˿�:%-8dĿ�Ķ˿�:%-8dЭ���:%-8d����:%-12d\n", in1, in2, in3, in4,
		        in5, result);//д��
		result = -1;
	} while ((sign1 = fgetc(fp1)) != EOF);

	fclose(fp1);

	fclose(fp3);

}


void num_10_to_2_8(int num, char arr[9]);
//��һ��10���Ƶ���ת��Ϊһ��2���Ƶ��ַ���(8λ)

long long up_ipaddress_to_ipnum(int a1, int a2, int a3, int a4, int a5);
//��IP��ַ���ĸ����ֺ�����ǰ׺��int���룬����IP��ַת��Ϊʮ���Ʊ�ʾ�����ޣ�

long long down_ipaddress_to_ipnum(int a1, int a2, int a3, int a4, int a5);
//��IP��ַ���ĸ����ֺ�����ǰ׺��int���룬����IP��ַת��Ϊʮ���Ʊ�ʾ�����ޣ�

int match(long long in1, long long in2, int in3, int in4, int in5, long long aup,
          long long adown, long long bup, long long bdown, int cup, int cdown, int dup,
          int ddown, int eup, int edown, int i);
//����ƥ�����������

void packet_classify(char file1[10], char file2[10]);
//���й��ܴ���ɵĺ����������ļ��������Զ�ƥ��


int main() {

	char file1[10], file2[10]; //�����ַ���������ݼ��͹�������

	scanf("%s %s", file2, file1); //��ȡ���򼯺����ݼ�����

	packet_classify(file1, file2);

	return 0;
}