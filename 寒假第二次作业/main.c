#include <stdio.h>
#include "head.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
int main() {

	char file1[10], file2[10]; //�����ַ���������ݼ��͹�������

	scanf("%s %s", file2, file1); //��ȡ���򼯺����ݼ�����

	packet_classify(file1, file2);

	return 0;
}