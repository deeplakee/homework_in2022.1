#include <stdio.h>
#include "head.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
int main() {
	char file1[10], file2[10]; //�����ַ���������ݼ��͹�������
	scanf("%s %s", file2, file1); //��ȡ���򼯺����ݼ�����
	FILE *fp1;//���ݼ�ָ��
	FILE *fp2;//����ָ��
	FILE *fp3;//����ļ�ָ��
	int sign1;//�ж϶�ȡ�ļ��Ƿ����
	fp2 = fopen(file2, "r"); //�򿪹����ļ���ֻ��ģʽ
	int i = 0; //����������¼��������
	int rul_ip1, rul_ip2, rul_ip3, rul_ip4, sign_ip1; //ԴIP���ĸ����ֺ�����ǰ׺
	int rul_ip5, rul_ip6, rul_ip7, rul_ip8, sign_ip2; //Ŀ��IP���ĸ����ֺ�����ǰ׺
	char signip1, signip2, signip3, signip4; //�������ַ���ʽ��ȡ����ǰ׺
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
		fprintf(fp3, "ԴIP��ַ:%-15lldĿ��IP��ַ:%-15lldԴ�˿�:%-8dĿ�Ķ˿�:%-8dЭ���:%-8d����:%-12d\n", in1, in2, in3, in4, in5, result);//д��
		result = -1;
	} while ((sign1 = fgetc(fp1)) != EOF);
	fclose(fp1);
	fclose(fp3);
	return 0;
}