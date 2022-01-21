void ipnum_to_ipadress(long num,char arr[16])
{
	char ss[33]={'0'};
	int i;
	for (i = 31; i >= 0; i--) {
		ss[i] = num % 2 + 48;
		num = num / 2;
		int ipnum1=0,ipnum2=0,ipnum3=0,ipnum4=0;
		
}