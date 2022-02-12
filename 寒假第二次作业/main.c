#include <stdio.h>
#include "head.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
int main() {

	char file1[10], file2[10]; //定义字符串存放数据集和规则集名称

	scanf("%s %s", file2, file1); //读取规则集和数据集名称

	packet_classify(file1, file2);

	return 0;
}