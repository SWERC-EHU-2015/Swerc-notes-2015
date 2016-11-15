// e The number of entries
// n The index of the permutation
int fact[MAX];  // MAX >= n
int perm[MAX];  // MAX >= n
void nthPermutation(const int e, int n) {
   int j, k = 0;

   // compute factorial numbers
   fact[k] = 1;
   while (++k < e)
      fact[k] = fact[k - 1] * k;

   // compute factorial code
   for (k = 0; k < n; ++k) {
      perm[k] = i / fact[n - 1 - k];
      n = n % fact[e - 1 - k];
   }

   // readjust values to obtain the permutation
   // start from the end and check if preceding values are lower
   for (k = e - 1; k > 0; --k)
      for (j = k - 1; j >= 0; --j)
         if (perm[j] <= perm[k])
            perm[k]++;

   // perm[0..e] contains the nth permutation
}
