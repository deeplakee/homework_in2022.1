#include <stdio.h>
#include "head.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
int main()
{
	char file1[10],file2[10];//定义数据集和规则集
	scanf("%s %s",file1,file2);//读取数据集和规则集
	FILE *fp1;//数据集指针
	FILE *fp2;//规则集指针
	FILE *fp3;//输出文件指针
	int sign1//判断读取文件是否结束
	char 
	fp1=fopen("file2","r");//打开规则集文件
	struct rulelist//定义结构体存放规则集数据
	{
		long long up_ip_s;//源IP地址上限
		long long down_ip_s;//源IP地址下限
		long long up_ip_d;//目的IP地址上限
		long long down_ip_d;//目的IP地址下限
		int up_port_s;//源端口上限
		int down_port_s;//源端口下线
		int up_port_d;//目的端口上限
		int down_port_d;//目的端口下线
		int up_agreement;//协议上限
		int down_agreement;//协议下限
	}rulefile[1000];
	int i=0;//计数器
	char rul_ip1[4],rul_ip2[4],rul_ip3[4],rul_ip4[4],sign_ip1[4];//源IP的四个部分和网络前缀
	char rul_ip5[4],rul_ip6[4],rul_ip7[4],rul_ip8[4],sign_ip2[4];//目的IP的四个部分和网络前缀
	char signip1,signip2,signip3,signip4;//用于以字符形式读取网络前缀
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