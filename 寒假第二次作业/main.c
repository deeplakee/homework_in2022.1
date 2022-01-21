#include <stdio.h>
#include "head.h"
#include <string.h>
#include <math.h>
int main()
{
	long long a;
	char s1[4],s2[4],s3[4],s4[4];
	scanf("%[^.].%[^.].%[^.].%s",s1,s2,s3,s4);
	a=ipaddress_to_ipnum(s1,s2,s3,s4);
	printf("%lld",a);
	return 0;
}