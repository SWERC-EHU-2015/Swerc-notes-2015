VII adj, scc;
VI num, low;
VI S;
VB visited, currentSCC;
int nodeCount, numSCC;

/* num[i] = orden en el que se visita por primera vez el nodo i */
/* low[i] = minimo num alcanzable desde el nodo i y desde sus hijos en la busqueda */
/* currentSCC[i] <=> el nodo i forma parte del SCC que se está explorando */
/* S = Pila que guarda los nodos según el orden en que se exploran */
/* Los nodos que forman cada componente quedan en scc */
/* Inicializar 'nodeCount' y 'numSCC' a 0 antes de llamar a la función */
void dfs(int u) {
	num[u] = low[u] = nodeCount++;
	S.push_back(u);
	visited[u] = currentSCC[u] = true;
	int v;
	for (int i = 0; i < (int)adj[u].size(); ++i) {
		v = adj[u][i];
		if (!visited[v])
			dfs(v);
		if (currentSCC[v]) /* si es parte de la misma componente que u */
			low[u] = min(low[u], low[v]); /* desde u alcanzo lo mismo que desde v */
	}
	if (low[u] == num[u]) { /* si u es raíz de una SCC */
		scc.push_back(VI());
		do { /* El SCC lo forman los nodos en la pila hasta alcanzar u */
			v = S.back(); S.pop_back(); currentSCC[v] = 0;
			scc[numSCC].push_back(v);
		} while (u != v);
		numSCC++; /* Si solo se desea el número de SCCs, el vector scc sobra */
	}
}
/* Ejemplo de main, donde N es el número de nodos*/
// adj = VII(N, VI()); scc = VII(); num = VI(N); low = VI(N);
// S = VI(); visited = VB(N);
// currentSCC = VB(N); nodeCount = numSCC = 0;
/* Rellenar la lista de adyacencia */
// for (int i = 0; i < N; ++i)
// 	if (!visited[i])
// 		dfs(i);
