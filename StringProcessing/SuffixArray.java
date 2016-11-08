public class SuffixArray {
    
    public final int n;
    public final int[] s, sa, lcp, owner;
    
    private static void countingSort(int[] sa, int[] ra, int raMax, int k) {
        final int n = sa.length;
        final int maxi = Math.max(raMax+1, n);
        final int[] c = new int[maxi];
        final int[] tempSa = new int[n];
        for (int i = 0; i < n ; i++) c[i+k < n ? ra[i+k] : 0]++;
        for (int i = 0, sum = 0; i < maxi; i++) {
            final int aux = c[i];
            c[i] = sum;
            sum += aux;
        }
        for (int i = 0; i < n; i++) tempSa[c[sa[i] + k < n ? ra[sa[i] + k] : 0]++] = sa[i];
        System.arraycopy(tempSa, 0, sa, 0, n);
    }
    
    public static int[] createSA(int[] s) {
        final int n = s.length;
        final int[] ra = new int[n];
        final int[] tempRa = new int[n];
        final int[] sa = new int[n];
        int r = 0;
        for (int i = 0; i < n; i++) if ((ra[i] = s[i]) > r) r = ra[i];
        for (int i = 0; i < n; i++) sa[i] = i;
        for (int k = 1; k < n; k <<= 1) {
            countingSort(sa, ra, r, k);
            countingSort(sa, ra, r, 0);
            tempRa[sa[0]] = r = 0;
            for (int i = 1; i < n; i++)
                tempRa[sa[i]] = (ra[sa[i]] == ra[sa[i-1]] && (sa[i]+k < n ? ra[sa[i]+k] : 0) == (sa[i-1]+k < n ? ra[sa[i-1]+k] : 0)) ? r : ++r;
            System.arraycopy(tempRa, 0, ra, 0, n);
        }
        return sa;
    }
    
    public static int[] createLCP(int[] s, int[] sa) {
        final int n = sa.length;
        final int[] phi = new int[n];
        final int[] plcp = new int[n];
        final int[] lcp = new int[n];
        phi[sa[0]] = -1;
        for (int i = 1; i < n; i++) phi[sa[i]] = sa[i-1];
        for (int i = 0, l = 0; i < n; i++) {
            if (phi[i] == -1) {
                plcp[i] = 0;
            } else {
                while (i + l < n && phi[i] + l < n && s[i+l] == s[phi[i]+l]) l++;
                plcp[i] = l;
                l = Math.max(l-1, 0);
            }
        }
        for (int i = 1; i < n; i++) lcp[i] = plcp[sa[i]];
        return lcp;
    }
    
    public SuffixArray(String... strings) {
        int ntemp = strings.length;
        for (String string : strings) ntemp += string.length();
        n = ntemp;
        s = new int[n];
        owner = new int[n];
        int ind = 0;
        int current = 0;
        for (String string : strings) {
            for (int i = 0; i < string.length(); i++) {
                s[ind] = string.charAt(i)+strings.length;
                owner[ind] = current;
                ind++;
            }
            s[ind] = owner[ind] = current;
            ind++;
            current++;
        }
        sa = createSA(s);
        lcp = createLCP(s, sa);
    }
    
    public int[] search(String string) {
        final int p[] = new int[string.length()];
        final int offset = owner[owner.length-1]+1;
        for (int i = 0; i < p.length; i++) p[i] = string.charAt(i)+offset;
        
        int lo = 0;
        int hi = n-1;
        int mid;
        while (lo < hi) {
            mid = (lo+hi)/2;
            if (strcmp(s, sa[mid], p, 0) >= 0) hi = mid;
            else lo = mid+1;
        }
        if (strcmp(s, sa[lo], p, 0) != 0) return new int[]{-1, -1};
        
        final int[] res = new int[]{lo, 0};
        lo = 0;
        hi = n-1;
        while (lo < hi) {
            mid = (lo+hi)/2;
            if (strcmp(s, sa[mid], p, 0) > 0) hi = mid;
            else lo = mid+1;
        } 
        if (strcmp(s, sa[hi], p, 0) == 0) hi++;
        res[1] = hi;
        return res;
    }
    
    private int strcmp(int[] a, int i, int[] b, int j) {
        for (int k = 0; i+k < a.length && j+k < b.length; k++) {
            if (a[i+k] != b[j+k]) return a[i+k] - b[j+k];
        }
        return 0;
    }
    
}