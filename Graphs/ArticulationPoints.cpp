VVI adj;
VI num, low;
VI parent;
vb visited;
vb artPoint;
int nodeCount, root, rootChildren;

/* num[i] = orden en el que se visita por primera vez el nodo i */
/* low[i] = mínimo num alcanzable desde el nodo i y desde sus hijos en la búsqueda */
/* Establecer 'root' al nodo raíz de la búsqueda, y 'rootChildren' y 'nodeCount' a 0 antes de llamar a dfs(root) */
void dfs(int u) {
	num[u] = low[u] = nodeCount++;
	visited[u] = true;
	for (int i = 0; i < (int)adj[u].size(); ++i) {
		int v = adj[u][i];
		if (!visited[v]) {
			parent[v] = u;
			if (u == root) rootChildren++;
			dfs(v);
			if (low[v] >= num[u]) /* si desde v no puedo alcanzar nada más arriba de u */
				artPoint[u] = true;
			if (low[v] > num[u]) /* si desde v no puedo alcanzar ni u */
				cout << "(u,v) is a bridge" << endl;
			low[u] = min(low[u], low[v]); /* desde u alcanzo lo mismo que desde v */
		} else if (v != parent[u])
			low[u] = min(low[u], num[v]); /* desde u alcanzo v */
	}
}

/* Después de la llamada: 'root' es un punto de articulación sii 'rootChildren' > 1 */
artPoint[root] = (rootChildren > 1);