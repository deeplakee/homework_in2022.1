#include <stdio.h>
#include "head.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
int main()
{
	char file1[10],file2[10];//�������ݼ��͹���
	scanf("%s %s",file1,file2);//��ȡ���ݼ��͹���
	FILE *fp1;//���ݼ�ָ��
	FILE *fp2;//����ָ��
	FILE *fp3;//����ļ�ָ��
	int sign1//�ж϶�ȡ�ļ��Ƿ����
	char 
	fp1=fopen("file2","r");//�򿪹����ļ�
	struct rulelist//����ṹ���Ź�������
	{
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
	}rulefile[1000];
	int i=0;//������
	char rul_ip1[4],rul_ip2[4],rul_ip3[4],rul_ip4[4],sign_ip1[4];//ԴIP���ĸ����ֺ�����ǰ׺
	char rul_ip5[4],rul_ip6[4],rul_ip7[4],rul_ip8[4],sign_ip2[4];//Ŀ��IP���ĸ����ֺ�����ǰ׺
	char signip1,signip2,signip3,signip4;//�������ַ���ʽ��ȡ����ǰ׺
	do{
		fscanf(fp2,"@%[^.].%[^.].%[^.].%[^/]/%c%c",rul_ip1,rul_ip2,rul_ip3,rul_ip4,&signip1,&signip2);
		sign_ip1[0]=signip1;
		sign_ip1[1]=signip2;
		sign_ip1[2]='\0';
		sign_ip1[3]='\0';
		rulefile[i].up_ip_s=up_ipaddress_to_ipnum(rul_ip1,rul_ip2,rul_ip3,rul_ip4,sign_ip1);
		rulefile[i].down_ip_s=down_ipaddress_to_ipnum(rul_ip1,rul_ip2,rul_ip3,rul_ip4,sign_ip1);
		fscanf(fp2,"%[^.].%[^.].%[^.].%[^/]/%c%c",rul_ip5,rul_ip6,rul_ip7,rul_ip8,&signip1,&signip2);
		sign_ip2[0]=signip3;
		sign_ip2[1]=signip4;
		sign_ip2[2]='\0';
		sign_ip2[3]='\0';
		rulefile[i].up_ip_d=up_ipaddress_to_ipnum(rul_ip5,rul_ip6,rul_ip7,rul_ip8,sign_ip2);
		rulefile[i].down_ip_d=down_ipaddress_to_ipnum(rul_ip5,rul_ip6,rul_ip7,rul_ip8,sign_ip2);
		fscanf(fp2,"%d : %d",&rulefile[i].down_port_s,&rulefile[i].up_port_s);
		fscanf(fp2,"%d : %d",&rulefile[i].down_port_d,&rulefile[i].up_port_d);
		fscanf(fp2,"%i/%i",&rulefile[i].down_agreement,&rulefile[i].up_port_s);
		fgetc(fp2);
	}
	while(!feof(fp2));
	
	return 0;
}