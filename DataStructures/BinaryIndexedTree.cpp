#define LSOne(S) (S & (-S))

class FenwickTree { // Queries for dynamic RSQ in O(log n), elements numbered from 1 to n
private:
  VI ft;
public:
  FenwickTree(int n) : ft(n+1, 0) {} // initialization: n + 1 zeroes, ignore index 0
  int rsq(int b) { int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b]; return sum; } // RSQ(1, b)
  int rsq(int a, int b) { return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); } // RSQ(a, b)
  // adjusts value of the k-th element by v (v can be +ve/inc or -ve/dec)
  void adjust(int k, int v) { for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }
};
