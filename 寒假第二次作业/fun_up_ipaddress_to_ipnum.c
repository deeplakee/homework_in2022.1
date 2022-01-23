#include <math.h>
#include "head.h"
long long up_ipaddress_to_ipnum(char arr1[4],char arr2[4],char arr3[4],char arr4[4],char arr5[4])
{
	long long ipad=0;
	char ipad1[9],ipad2[9],ipad3[9],ipad4[9];
	int a1=arr_to_10(arr1),a2=arr_to_10(arr2),a3=arr_to_10(arr3),a4=arr_to_10(arr4),a5=arr_to_10(arr5);
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
		ss[a5]=1;
		a5++;
	}
	for(i=0;i<32;i++)
	ipad+=pow(2,i)*(ss[31-i]-48);
	return ipad;
}