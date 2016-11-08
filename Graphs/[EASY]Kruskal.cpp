// COMPLEXITY: O(E log E)
#include "UnionFindDisjointSet.cpp"
//Returns the cost of the msp
int Kruskal(vector<pair<int, PII>> edgeList, int graphSize) {
	sort(edgeList.begin(), edgeList.end());

	int mst_cost = 0;
	UnionFindDisjointSet UF(graphSize);

	for (int i = 0; i < edgeList.size(); ++i) {
		pair<int, PII> front = edgeList[i];
		if (!UF.isSameSet(front.second.first, front.second.second)) {
			mst_cost += front.first;
			UF.unionSet(front.second.first, front.second.second);
		}
	}
	return mst_cost;
}
