#include <math.h>
#include "head.h"
long long ipaddress_to_ipnum(char arr1[4],char arr2[4],char arr3[4],char arr4[4])
{
	long long ipad=0;
	char ipad1[9],ipad2[9],ipad3[9],ipad4[9];
	int a1=arr_to_10(arr1),a2=arr_to_10(arr2),a3=arr_to_10(arr3),a4=arr_to_10(arr4);
	num_10_to_2_8(a1,ipad1);
	num_10_to_2_8(a2,ipad2);
	num_10_to_2_8(a3,ipad3);
	num_10_to_2_8(a4,ipad4);
	int i,k=0;
	for(i=0;i<8;i++)
	ipad+=pow(2,k)*(ipad4[7-i]-48),k++;
	for(i=0;i<8;i++)
	ipad+=pow(2,k)*(ipad3[7-i]-48),k++;
	for(i=0;i<8;i++)
	ipad+=pow(2,k)*(ipad2[7-i]-48),k++;
	for(i=0;i<8;i++)
	ipad+=pow(2,k)*(ipad1[7-i]-48),k++;
	return ipad;
}