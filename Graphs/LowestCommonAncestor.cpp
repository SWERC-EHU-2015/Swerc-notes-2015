// Lowest Common Ancestor with adjacency list
// Requires an RMQ implementation
//  Par[i] = parent of node i in the DFS, root is its own parent
//  E[i] = i-th node visited in the DFS (Euler tour)
//  L[i] = levels of the i-th node visited in the DFS (Euler tour)
//  H[i] = index of the first occurrence of node i in E
struct LCA {
	int idx;
	VVI adj;
	VI Par, E, L, H;
	RMQ * rmq;

	LCA(int N, VVI adjlist) :
	  idx(0), adj(adjlist), Par(N, -1), E(2*N-1), L(2*N-1), H(N, -1) {
		dfs(0, 0, 0); // We fix the root at index 0
		rmq = new RMQ(2*N-1, L);
	}

	void dfs(int cur, int depth, int parent) {
		Par[cur] = parent;
		H[cur] = idx;
		E[idx] = cur;
		L[idx++] = depth;
		for (int i = 0; i < (int) adj[cur].size(); i++) {
			if (Par[adj[cur][i]] == -1) {
				dfs(adj[cur][i], depth + 1, cur);
				E[idx] = cur;
				L[idx++] = depth;
			}
		}
	}

	int depth(int u) { return L[H[u]]; } // Depth of u
	int parent(int u) { return Par[u]; } // Parent of u
	int find(int u, int v) { // LCA(u, v)
		if (H[u] > H[v]) swap(u, v);
		return E[rmq->query(H[u], H[v])];
	}
};
