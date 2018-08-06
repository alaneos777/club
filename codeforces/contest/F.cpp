#include <bits/stdc++.h>
using namespace std;

int pairwiseSum(vector<int> & nums){
	int ans = 0;
	for(int i = 0; i < nums.size() - 1; i++){
		int tmp = 0;
		for(int j = i + 1; j < nums.size(); j++){
			tmp += nums[j];
		}
		ans += nums[i] * tmp;
	}
	return ans;
}

int count(int start, int pos, vector<vector<int>> & graph, vector<vector<int>> & info){
	int ans = 0;
	int n = graph.size() - 1;
	for(int i = 0; i < graph[pos].size(); i++){
		int dest = graph[pos][i];
		if(start != dest){
			int tmp = 1 + count(pos, dest, graph, info);
			info[pos].push_back(tmp);
			info[dest].push_back(n + 1 - tmp);
			ans += tmp;
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	vector<vector<int>> graph(n + 1, vector<int>());
	vector<vector<int>> info(n + 1, vector<int>());
	for(int i = 0; i < n; i++){
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	count(-1, 0, graph, info);
	int pos, maxPairs = 0;
	for(int i = 0; i <= n; i++){
		int value = pairwiseSum(info[i]);
		if(value > maxPairs){
			maxPairs = value;
			pos = i;
		}
	}
	int max1, max2;
	if(info[pos][0] > info[pos][1]){
		max1 = info[pos][0];
		max2 = info[pos][1];
	}else{
		max1 = info[pos][1];
		max2 = info[pos][0];
	}
	for(int i = 2; i < info[pos].size(); i++){
		if(info[pos][i] > max1){
			max2 = max1;
			max1 = info[pos][i];
		}else if(info[pos][i] > max2){
			max2 = info[pos][i];
		}
	}
	cout << maxPairs << " " << (maxPairs - max1 * max2);
	return 0;
}