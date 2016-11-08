public class EditDistance {
    
    public static final EditDistance LEVENSHTEIN_DISTANCE = new EditDistance(2, -1, -1, -1);
    public static final EditDistance LONGEST_COMMON_SUBSEQUENCE = new EditDistance(1, -1000000000, 0, 0);
    
    public final int matchScore;     // Character a[i] and b[i] match and we do nothing
    public final int mismatchScore;  // Character a[i] and b[i] mismatch and we replace a[i] with b[i]
    public final int insertScore;    // We insert a space in A[i]
    public final int deleteScore;    // We delete a letter from A[i]
    
    public EditDistance(int matchScore, int mismatchScore, int insertScore, int deleteScore) {
        this.matchScore = matchScore;
        this.mismatchScore = mismatchScore;
        this.insertScore = insertScore;
        this.deleteScore = deleteScore;
    }
    
    public int getMaxScore(String a, String b) { // Needleman-Wunsch's algorithm
        final int[][] table = new int[a.length()+1][b.length()+1];
        for (int i = 1; i <= a.length(); i++) table[i][0] = i * deleteScore;
        for (int j = 1; j <= b.length(); j++) table[0][j] = j * insertScore;
        for (int i = 1; i <= a.length(); i++) {
            for (int j = 1; j <= b.length(); j++) {
                table[i][j] = table[i-1][j-1] + (a.charAt(i-1) == b.charAt(j-1) ? matchScore : mismatchScore);
                table[i][j] = Math.max(table[i][j], table[i-1][j] + deleteScore);
                table[i][j] = Math.max(table[i][j], table[i][j-1] + insertScore);
            }
        }
        return table[a.length()][b.length()];
    }
    
}
