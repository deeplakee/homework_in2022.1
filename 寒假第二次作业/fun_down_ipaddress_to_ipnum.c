#include <math.h>
#include "head.h"
long long down_ipaddress_to_ipnum(int a1,int a2,int a3,int a4,int a5)
{
	long long ipad=0;
	char ipad1[9],ipad2[9],ipad3[9],ipad4[9];
	num_10_to_2_8(a1,ipad1);
	num_10_to_2_8(a2,ipad2);
	num_10_to_2_8(a3,ipad3);
	num_10_to_2_8(a4,ipad4);
	int i;
	char ss[33];
	for(i=0;i<8;i++)
	ss[i]=ipad1[i];
	for(i=8;i<16;i++)
	ss[i]=ipad1[i-8];
	for(i=16;i<24;i++)
	ss[i]=ipad1[i-16];
	for(i=24;i<32;i++)
	ss[i]=ipad1[i-24];
	while(a5<32)
	{
		ss[a5]=0;
		a5++;
	}
	for(i=0;i<32;i++)
	ipad+=pow(2,i)*(ss[31-i]-48);
	return ipad;
}