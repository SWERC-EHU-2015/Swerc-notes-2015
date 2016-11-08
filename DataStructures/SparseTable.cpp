struct RMQ {
	VI A, logtable;
	VVI spt; // SpT[i][j] = RMQ of range starting at i and length (2^j)
	RMQ(int N, VI data) : A(data), logtable(N + 1) {
		for (int i = 2; i <= N; i++)
			logtable[i] = logtable[i >> 1] + 1;
		spt = VVI(logtable[N] + 1, VI(N));
		for (int i = 0; i < N; i++)
			spt[0][i] = i;
		for (int j = 1; (1 << j) <= N; j++)
			for (int i = 0; i + (1 << j) - 1 < N; i++)
				if (A[spt[j - 1][i]] < A[spt[j - 1][i + (1 << (j - 1))]])
					spt[j][i] = spt[j - 1][i];
				else
					spt[j][i] = spt[j - 1][i + (1 << (j - 1))];
	}
	int query(int i, int j) {
		int k = logtable[j-i+1]; // 2^k <= (j-i+1)
		if (A[spt[k][i]] <= A[spt[k][j - (1 << k) + 1]])
			return spt[k][i];
		else
			return spt[k][j - (1 << k) + 1];
	}
};
