int match(long long in1, long long in2, int in3, int in4, int in5, long long aup,
          long long adown, long long bup, long long bdown, int cup, int cdown, int dup,
          int ddown, int eup, int edown, int i) {
	if (!(in1 >= adown && in1 <= aup))//ƥ��ԴIP��ַ
		return -1;
	if (!(in2 >= bdown && in2 <= bup))//ƥ��Ŀ��IP��ַ
		return -1;
	if (!(in3 >= cdown && in3 <= cup))//ƥ��Դ�˿�
		return -1;
	if (!(in4 >= ddown && in4 <= dup))//ƥ��Ŀ�Ķ˿�
		return -1;
	if (!(in5 >= edown && in5 <= eup) && (edown != 0 || eup != 0)) //ƥ��Э��
		return -1;
	return i;
}