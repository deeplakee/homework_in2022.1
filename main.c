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
	num_10_to_2_8(a1, ipad1);//把前四个
	num_10_to_2_8(a2, ipad2);//参数转化
	num_10_to_2_8(a3, ipad3);//为八位的
	num_10_to_2_8(a4, ipad4);//二进制
	int i;
	char ss[33];//统一存放在一起
	for (i = 0; i < 8; i++)
		ss[i] = ipad1[i];
	for (i = 8; i < 16; i++)
		ss[i] = ipad2[i - 8];
	for (i = 16; i < 24; i++)
		ss[i] = ipad3[i - 16];
	for (i = 24; i < 32; i++)
		ss[i] = ipad4[i - 24];
	while (a5 < 32) {//根据网络前缀置1
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
	while (a5 < 32) {//根据网络前缀置0
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
	if (!(in1 >= adown && in1 <= aup))//匹配源IP地址
		return -1;
	if (!(in2 >= bdown && in2 <= bup))//匹配目的IP地址
		return -1;
	if (!(in3 >= cdown && in3 <= cup))//匹配源端口
		return -1;
	if (!(in4 >= ddown && in4 <= dup))//匹配目的端口
		return -1;
	if (!(in5 >= edown && in5 <= eup) && (edown != 0 || eup != 0)) //匹配协议
		return -1;
	return i;
}


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


void num_10_to_2_8(int num, char arr[9]);
//把一个10进制的数转化为一个2进制的字符串(8位)

long long up_ipaddress_to_ipnum(int a1, int a2, int a3, int a4, int a5);
//把IP地址的四个数字和网络前缀以int读入，并把IP地址转化为十进制表示（上限）

long long down_ipaddress_to_ipnum(int a1, int a2, int a3, int a4, int a5);
//把IP地址的四个数字和网络前缀以int读入，并把IP地址转化为十进制表示（下限）

int match(long long in1, long long in2, int in3, int in4, int in5, long long aup,
          long long adown, long long bup, long long bdown, int cup, int cdown, int dup,
          int ddown, int eup, int edown, int i);
//用于匹配数据与规则

void packet_classify(char file1[10], char file2[10]);
//所有功能打包成的函数，输入文件名即可自动匹配


int main() {

	char file1[10], file2[10]; //定义字符串存放数据集和规则集名称

	scanf("%s %s", file2, file1); //读取规则集和数据集名称

	packet_classify(file1, file2);

	return 0;
}