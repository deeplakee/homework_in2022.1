#include <string.h>
int arr_to_10(char arr[4]) {
	int length = strlen(arr), num = 0;
	int i;
	for (i = 0 ; i <= length - 1; i++)
		num = arr[i] - 48 + num * 10;
	return num;
}