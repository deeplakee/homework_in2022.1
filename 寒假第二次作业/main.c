#include <stdio.h>
#include "head.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
int main()
{
	char file1[10],file2[10];//�����ַ���������ݼ��͹�������
	scanf("%s %s",file2,file1);//��ȡ���򼯺����ݼ�����
	FILE *fp1;//���ݼ�ָ��
	FILE *fp2;//����ָ��
	FILE *fp3;//����ļ�ָ��
	int sign1;//�ж϶�ȡ�ļ��Ƿ����
	fp2=fopen(file2,"r");//�򿪹����ļ���ֻ��ģʽ
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
	int i=0;//����������¼��������
	int rul_ip1,rul_ip2,rul_ip3,rul_ip4,sign_ip1;//ԴIP���ĸ����ֺ�����ǰ׺
	int rul_ip5,rul_ip6,rul_ip7,rul_ip8,sign_ip2;//Ŀ��IP���ĸ����ֺ�����ǰ׺
	char signip1,signip2,signip3,signip4;//�������ַ���ʽ��ȡ����ǰ׺
	fgetc(fp2);//��ȡ��һ��@
	do{
		fscanf(fp2,"%d.%d.%d.%d/%c%c",&rul_ip1,&rul_ip2,&rul_ip3,&rul_ip4,&signip1,&signip2);
		sign_ip1=cc_to_num(signip1,signip2);
		rulefile[i].up_ip_s=up_ipaddress_to_ipnum(rul_ip1,rul_ip2,rul_ip3,rul_ip4,sign_ip1);
		rulefile[i].down_ip_s=down_ipaddress_to_ipnum(rul_ip1,rul_ip2,rul_ip3,rul_ip4,sign_ip1);
		
		fscanf(fp2,"%d.%d.%d.%d/%c%c",&rul_ip5,&rul_ip6,&rul_ip7,&rul_ip8,&signip1,&signip2);
		sign_ip2=cc_to_num(signip3,signip4);
		rulefile[i].up_ip_d=up_ipaddress_to_ipnum(rul_ip5,rul_ip6,rul_ip7,rul_ip8,sign_ip2);
		rulefile[i].down_ip_d=down_ipaddress_to_ipnum(rul_ip5,rul_ip6,rul_ip7,rul_ip8,sign_ip2);
		
		fscanf(fp2,"%d : %d",&rulefile[i].down_port_s,&rulefile[i].up_port_s);
		fscanf(fp2,"%d : %d",&rulefile[i].down_port_d,&rulefile[i].up_port_d);
		fscanf(fp2,"%i/%i",&rulefile[i].down_agreement,&rulefile[i].up_agreement);
		fgetc(fp2);//��ȡ�س�
		i++;
	}
	while((sign1 = fgetc(fp2)) != EOF);//��ȡ��һ�е�@����EOF
	fclose(fp2);//�رչ����ļ�
	sign1=1;//����sign1
	long long in1,in2;
	int t=0,w=0;
	int in3,in4,in5;
	int result[1000];
	for(t=0;t<1000;t++)
	result[t]=-1;
	fp3=fopen("res.txt","w");//��������res.txt
	fp1=fopen(file1,"r");//�����ݼ��ļ���ֻ��ģʽ
	do{
		fscanf(fp1,"%lld",&in1);
		fscanf(fp1,"%lld",&in2);
		fscanf(fp1,"%d",&in3);
		fscanf(fp1,"%d",&in4);
		fscanf(fp1,"%d",&in5);
		for(t=0;t<i;t++)
		{
			result[w]=match(in1,in2,in3,in4,in5,rulefile[t].up_ip_s,rulefile[t].down_ip_s,
			rulefile[t].up_ip_d,rulefile[t].down_ip_d,rulefile[t].up_port_s,
			rulefile[t].down_port_s,rulefile[t].up_port_d,rulefile[t].down_port_d,
			rulefile[t].up_agreement,rulefile[t].down_agreement,t);
			if(result[w]!=-1)
			break;
		}
		fprintf(fp3,"%lld %lld %d %d %d  %d\n",in1,in2,in3,in4,in5,result[w]);
	}
	while((sign1 = fgetc(fp2)) != EOF);
	fclose(fp1);
	fclose(fp3);
	return 0;
}