typedef map<char,int> mci;
L factorial(L i) {
	if (i <= 1) return 1;

	L totala = 2;
	for (L j = 3; j <= i; ++j)
		totala *= j;
	return totala;
}
string nthPermutationRepetitions(string input, L n) {
	mci mapa;
	int input_len = input.length();
	for (int i = 0; i < input_len; ++i) {
		if (mapa.find(input[i]) == mapa.end())
			mapa[input[i]] = 1;
		else
			mapa[input[i]]++;
	}

	string buffer;
	buffer.resize(input_len);
	L totala = 0;
	for (int i = 0; i < input_len; ++i) {
		for (mci::iterator elem = mapa.begin(); elem != mapa.end(); ++elem) {
			if (elem->second > 0) {
				elem->second--;
				L perm = factorial(input_len - i -1);
				for (mci::iterator c = mapa.begin(); c != mapa.end(); ++c)
					perm /= factorial(c->second);

				if (n < totala + perm) {
					buffer[i] = elem->first;
					break;
				}
				totala += perm;
				elem->second++;
			}
		}
	}
	return buffer;
}
