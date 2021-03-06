#include "head.h"
#include <stdio.h>
void packet_classify(char file1[10], char file2[10]) {

	FILE *fp1;//数据集指针
	FILE *fp2;//规则集指针
	FILE *fp3;//输出文件指针

	struct rulelist { //定义结构体存放规则集数据
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
	} rulefile[1000];

	int i = 0; //计数器，记录规则条数
	int rul_ip1, rul_ip2, rul_ip3, rul_ip4, sign_ip1; //源IP的四个部分和网络前缀
	int rul_ip5, rul_ip6, rul_ip7, rul_ip8, sign_ip2; //目的IP的四个部分和网络前缀
	char signip1, signip2, signip3, signip4; //用于以字符形式读取网络前缀
	int sign1;//判断读取文件是否结束

	fp2 = fopen(file2, "r"); //打开规则集文件，只读模式

	fgetc(fp2);//读取第一个@
	do {
		fscanf(fp2, "%d.%d.%d.%d/%d", &rul_ip1, &rul_ip2, &rul_ip3, &rul_ip4, &sign_ip1);//读取源IP地址
		rulefile[i].up_ip_s = up_ipaddress_to_ipnum(rul_ip1, rul_ip2, rul_ip3, rul_ip4, sign_ip1);
		rulefile[i].down_ip_s = down_ipaddress_to_ipnum(rul_ip1, rul_ip2, rul_ip3, rul_ip4, sign_ip1);

		fscanf(fp2, "%d.%d.%d.%d/%d", &rul_ip5, &rul_ip6, &rul_ip7, &rul_ip8, &sign_ip2);//读取目的IP地址
		rulefile[i].up_ip_d = up_ipaddress_to_ipnum(rul_ip5, rul_ip6, rul_ip7, rul_ip8, sign_ip2);
		rulefile[i].down_ip_d = down_ipaddress_to_ipnum(rul_ip5, rul_ip6, rul_ip7, rul_ip8, sign_ip2);

		fscanf(fp2, "%d : %d", &rulefile[i].down_port_s, &rulefile[i].up_port_s);
		fscanf(fp2, "%d : %d", &rulefile[i].down_port_d, &rulefile[i].up_port_d);
		fscanf(fp2, "%i/%i", &rulefile[i].down_agreement, &rulefile[i].up_agreement);
		fgetc(fp2);//读取回车
		i++;
	} while ((sign1 = fgetc(fp2)) != EOF); //读取下一行的@或者EOF

	fclose(fp2);//关闭规则集文件

	sign1 = 1; //重置sign1


	int sign2;
	long long in1, in2;
	int t = 0;
	int in3, in4, in5;
	int result = -1;


	fp3 = fopen("res.txt", "w"); //创建并打开res.txt

	fp1 = fopen(file1, "r"); //打开数据集文件，只读模式

	do {
		if (sign2 = fscanf(fp1, "%lld", &in1) == EOF)
			break;

		fscanf(fp1, "%lld", &in2);//读取数据集
		fscanf(fp1, "%d", &in3);
		fscanf(fp1, "%d", &in4);
		fscanf(fp1, "%d", &in5);

		for (t = 0; t < i; t++) {//循环历遍匹配规则
			result = match(in1, in2, in3, in4, in5, rulefile[t].up_ip_s, rulefile[t].down_ip_s, rulefile[t].up_ip_d,
			               rulefile[t].down_ip_d, rulefile[t].up_port_s, rulefile[t].down_port_s, rulefile[t].up_port_d, rulefile[t].down_port_d,
			               rulefile[t].up_agreement, rulefile[t].down_agreement, t);
			if (result != -1)
				break;
		}
		fprintf(fp3, "源IP地址:%-15lld目的IP地址:%-15lld源端口:%-8d目的端口:%-8d协议号:%-8d规则:%-12d\n", in1, in2, in3, in4,
		        in5, result);//写入
		result = -1;
	} while ((sign1 = fgetc(fp1)) != EOF);

	fclose(fp1);

	fclose(fp3);

}