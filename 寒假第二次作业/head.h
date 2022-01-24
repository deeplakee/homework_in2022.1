
void num_10_to_2_8(int num,char arr[9]);//把一个10进制的数转化为一个2进制的字符串(8位)

long long up_ipaddress_to_ipnum(int a1,int a2,int a3,int a4,int a5);
//把IP地址的四个数字和网络前缀以int读入，并把IP地址转化为十进制表示（上限）

long long down_ipaddress_to_ipnum(int a1,int a2,int a3,int a4,int a5);
//把IP地址的四个数字和网络前缀以int读入，并把IP地址转化为十进制表示（下限）

int match(long long in1,long long in2,int in3,int in4,int in5,long long aup,
long long adown,long long bup,long long bdown,int cup,int cdown,int dup,
int ddown,int eup,int edown,int i);//用于匹配数据与规则


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