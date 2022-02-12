int match(long long in1, long long in2, int in3, int in4, int in5, long long aup,
          long long adown, long long bup, long long bdown, int cup, int cdown, int dup,
          int ddown, int eup, int edown, int i) {
	if (!(in1 >= adown && in1 <= aup))//匹配源IP地址
		return -1;
	if (!(in2 >= bdown && in2 <= bup))//匹配目的IP地址
		return -1;
	if (!(in3 >= cdown && in3 <= cup))//匹配源端口
		return -1;
	if (!(in4 >= ddown && in4 <= dup))//匹配目的端口
		return -1;
	if (!(in5 >= edown && in5 <= eup) && (edown != 0 || eup != 0)) //匹配协议
		return -1;
	return i;
}