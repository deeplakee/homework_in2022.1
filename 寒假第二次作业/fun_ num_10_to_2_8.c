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