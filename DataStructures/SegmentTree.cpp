template<typename T, typename Op>
class SegmentTree {
    Op op; vector<T> a, st; size_t n;
    T update(int p, int l, int r, int lo, int hi) {
        return l == r ? a[l] : hi < l || lo > r ? st[p] : st[p] = op(update(2*p, l, (l+r)/2, lo, hi), update(2*p+1, (l+r)/2+1, r, lo, hi));
    }
    T query(int p, int l, int r, int lo, int hi) {
        if (l == r) return a[l];
        if (lo <= l && hi >= r) return st[p];
        if (!(hi < l || lo > (l+r)/2)) {
            T left = query(2*p, l, (l+r)/2, lo, hi);
            return !(hi < (l+r)/2+1 || lo > r) ? op(left, query(2*p+1, (l+r)/2+1, r, lo, hi)) : left;
        } else {
            return query(2*p+1, (l+r)/2+1, r, lo, hi);
        }
    }
public:
    SegmentTree() : n(0), st(0) {}
    template <typename InputIterator>
    SegmentTree(InputIterator first, InputIterator last, const Op &op = Op()) : n(last-first), a(first, last), st(2*(last-first)), op(op) {
        update(0, n-1);
    }
    T get(int i) { return a[i]; }
    T query(int lo, int hi) { return query(1, 0, n-1, lo, hi); } // Both inclusive
    void set(int i, int v) { a[i] = v; update(i); }
    void update(int i) { update(i, i); }
    void update(int lo, int hi) { update(1, 0, n-1, lo, hi); }  // Both inclusive
};

template<typename T, typename Compare>
class MinimumIndexSegmentTree {
    struct Op {
        Compare cmp; vector<T> *a;
        int operator()(int i, int j) { return cmp((*a)[i], (*a)[j]) ? i : j; }
    }; vector<T> a; SegmentTree<size_t, Op> st;
public:
    template <typename InputIterator>
    MinimumIndexSegmentTree(InputIterator first, InputIterator last) : a(first, last) {
        VI aux(last-first);
        for (int i = 0; i < aux.size(); i++) aux[i] = i;
        Op op; op.a = &a;
        st = SegmentTree<size_t, Op>(aux.begin(), aux.end(), op);
    }
    T get(int i) { return a[i]; }
    int query(int lo, int hi) { return st.query(lo, hi); } // Both inclusive
    void set(int i, int v) { a[i] = v; st.update(i); }
};
typedef SegmentTree<int, plus<int> > RSQ;
typedef MinimumIndexSegmentTree<int, less<int> > RMQ;