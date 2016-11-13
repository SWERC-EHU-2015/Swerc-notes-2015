// n The number of entries
// i The index of the permutation
int fact[MAX];  // MAX >= n
int perm[MAX];  // MAX >= n
void ithPermutation(const int n, int i) {
   int j, k = 0;

   // compute factorial numbers
   fact[k] = 1;
   while (++k < n)
      fact[k] = fact[k - 1] * k;

   // compute factorial code
   for (k = 0; k < n; ++k) {
      perm[k] = i / fact[n - 1 - k];
      i = i % fact[n - 1 - k];
   }

   // readjust values to obtain the permutation
   // start from the end and check if preceding values are lower
   for (k = n - 1; k > 0; --k)
      for (j = k - 1; j >= 0; --j)
         if (perm[j] <= perm[k])
            perm[k]++;

   // perm[0..n] contains the ith permutation
}
