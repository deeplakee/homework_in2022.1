int match(long long in1, long long in2, int in3, int in4, int in5, long long aup,
          long long adown, long long bup, long long bdown, int cup, int cdown, int dup,
          int ddown, int eup, int edown, int i) {
	int sign1 = 0, sign2 = 0, sign3 = 0, sign4 = 0, sign5 = 0;
	if (in1 >= adown && in1 <= aup)//匹配源IP地址
		sign1 = 1;
	if (in2 >= bdown && in2 <= bup)//匹配目的IP地址
		sign2 = 1;
	if (in3 >= cdown && in3 <= cup)//匹配源端口
		sign3 = 1;
	if (in4 >= ddown && in4 <= dup)//匹配目的端口
		sign4 = 1;
	if (in5 >= edown && in5 <= eup)//匹配协议
		sign5 = 1;
	if (edown == 0 && eup == 0)//匹配协议
		sign5 = 1;
	if (sign1 + sign2 + sign3 + sign4 + sign5 != 5)
		i = -1;
	return i;
}