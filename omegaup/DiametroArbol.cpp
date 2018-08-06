#include <bits/stdc++.h>
using namespace std;

int count(int start, int pos, vector<vector<int>> & graph, vector<int> & heights){
	int ans = 0;
	for(int i = 0; i < graph[pos].size(); i++){
		int dest = graph[pos][i];
		if(start != dest){
			ans = max(count(pos, dest, graph, heights), ans);
		}
	}
	return heights[pos] = 1 + ans;
}

int diameter(int start, int pos, vector<vector<int>> & graph, vector<int> & heights){
	int max1 = 0, max2 = 0, max3 = 0;
	for(int & dest : graph[pos]){
		if(start != dest){
			if(heights[dest] > max1){
				max2 = max1, max1 = heights[dest];
			}else if(heights[dest] > max2){
				max2 = heights[dest];
			}
			max3 = max(max3, diameter(pos, dest, graph, heights));
		}
	}
	return max(1 + max1 + max2, max3);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, u, v;
	cin >> n;
	vector<vector<int>> graph(n + 1, vector<int>());
	vector<int> heights(n + 1);
	for(int i = 1; i < n; i++){
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	count(-1, 1, graph, heights);
	cout << diameter(-1, 1, graph, heights) - 1 << "\n";
	return 0;
}