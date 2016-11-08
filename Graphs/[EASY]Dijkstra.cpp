// COMPLEXITY: O((V+E)log V) (V,E < 300K)
const int INF = 1e9; //Use long long if something bigger is needed
VVI graph, weight;
VI dist;
void dijkstra(int source) {
	dist = VI(graph.size(), INF);
	dist[source] = 0;
	priority_queue<pii, vector<pii>, greater<pii> > pq;
	pq.push(pii(0, source));
	while(!pq.empty()) {
		int d = pq.top().first;
		int u = pq.top().second;
		pq.pop();
		if (d > dist[u])	continue;
		for (int i = 0; i < (int)graph[u].size(); ++i) {
			int v = graph[u][i];
			int w = weight[u][i];
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w ;
				pq.push(pii(dist[v], v));
			}
		}
	}
}
