class UnionFindDisjointSet {
    VI p, setSize; int numSets;
public:
    explicit UnionFindDisjointSet(int n) : p(n,-1), setSize(n,1), numSets(n) {}
    int findSet(int i) { return (p[i] < 0) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            numSets--;
            int x = findSet(i), y = findSet(j);
            if (p[x] < p[y]) { // rank[x] > rank[y]
                p[y] = x;
                setSize[x] += setSize[y];
            } else {
                p[x] = y;
                setSize[y] += setSize[x];
                if (p[x] == p[y]) p[y]--;
            }
        }
    }
};