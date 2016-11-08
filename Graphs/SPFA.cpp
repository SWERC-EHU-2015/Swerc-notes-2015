// Shortest Path Faster Algorithm
// SSSP adjacency-list implementation that handles negative weight cycles.
// The function returns true if such a cycle is detected (i.e., it can be reached from s).
// If not, dist[i] = distance from source node s to node i.
// Worst-case complexity: O(VE), in practice better than Bellman-Ford, but not than Dijkstra.
#define INF 1 << 30

bool spfa(int s, const vector<VPII>& adj, VI& dist) {
	int N = adj.size(), u, i;
	queue<int> cola;
	VI encolado(N), veces(N);

	dist = VI(N, INF);
	dist[s] = 0;

	cola.push(s);
	encolado[s] = veces[s] = 1;
	while (!cola.empty()) {
		u = cola.front();
		cola.pop();
		encolado[u] = 0;
		for (i = 0; i < (int) adj[u].size(); ++i) {
			PII p = adj[u][i];
			if (dist[u] + p.second < dist[p.first]) {
				dist[p.first] = dist[u] + p.second;
				if (!encolado[p.first]) {
					cola.push(p.first);
					encolado[p.first] = 1;
					veces[p.first]++;
					// Tratar ciclo negativo si se desea
					if (veces[p.first] == N) return true;
				}
			}
		}
	}
	return false;
}
