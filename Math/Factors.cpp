// COMPLEXITY: O(sqrt(n))
//Returns a list of all the factors of n
//Example: n = 12 -> result = [2, 2, 3]
// n > 1
VI factors(int n)  {
	int z = 2;
	VI result;
	while (z * z <= n) {
		if (n % z == 0) {
			result.push_back(z);
			n /= z;
		} else z++;
	}
	if (n > 1) result.push_back(n);
	return result;
}
