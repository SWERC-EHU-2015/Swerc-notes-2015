inline VI longestIncreasingSubsequence(const vector<int> &a) { // O(n log k)
    int n = a.size(), lsize = 0;
    VI lval(n), lind(n), rec(n);
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(lval.begin(), lval.begin() + lsize, a[i]) - lval.begin();
        lval[pos] = a[i]; lind[pos] = i;
        rec[i] = pos == 0 ? -1 : lind[pos-1];
        if (pos == lsize) lsize++;
    }
    // Recover the solution (return lsize and remove lind and rec if you only need its length)
    VI res(lsize);
    for (int i = lind[lsize-1]; i != -1; i = rec[i]) res[--lsize] = a[i];
    return res;
}
