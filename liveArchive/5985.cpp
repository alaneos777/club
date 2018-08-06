#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

void combine(int a, int b, vector<lli> & A, vector<lli> & ans){
	ans.push_back(0);
	for(int i = a; i <= b; i++){
		int size = ans.size();
		for(int j = 0; j < size; j++){
			ans.push_back(ans[j] + A[i]);
		}
	}
	sort(ans.begin(), ans.end());
}

bool can(lli v, vector<lli> & first, vector<lli> & second){
	for(int i = 0; i < first.size(); ++i){
		if(binary_search(second.begin(), second.end(), v - first[i])){
			return true;
		}
	}
	return false;
}

bool kuhn(int u, vector<vector<int>> & adjList, vector<bool> & used, vector<int> & left, vector<int> & right){
	if(used[u]) return false;
	used[u] = true;
	for(int & v : adjList[u]){
		if(right[v] == -1 || kuhn(right[v], adjList, used, left, right)){
			right[v] = u;
			left[u] = v;
			return true;
		}
	}
	return false;
}

lli kuhn(vector<vector<int>> & adjList, vector<lli> & weights, int l, int r){
	vector<int> left(l, -1), right(r, -1);
	vector<bool> used(l);
	for(int u = 0; u < l; ++u){
		kuhn(u, adjList, used, left, right);
		fill(used.begin(), used.end(), false);
	}
	lli ans = 0;
	for(int u = 0; u < r; ++u){
		if(right[u] != -1){
			ans += weights[right[u]];
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int m, n, cap;
		cin >> m >> n;
		vector<lli> weights(m);
		for(int i = 0; i < m; ++i){
			cin >> weights[i];
		}
		sort(weights.begin(), weights.end(), greater<lli>());
		vector<vector<lli>> vaults(n, vector<lli>());
		vector<pair<vector<lli>, vector<lli>>> info(n);
		for(int i = 0; i < n; ++i){
			cin >> cap;
			vaults[i].resize(cap);
			for(int j = 0; j < cap; ++j){
				cin >> vaults[i][j];
			}
			combine(0, (cap - 1) / 2, vaults[i], info[i].first);
			combine((cap + 1) / 2, cap - 1, vaults[i], info[i].second);
		}
		vector<vector<int>> left(m, vector<int>());
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				if(can(weights[i], info[j].first, info[j].second)){
					left[i].push_back(j);
				}
			}
		}
		cout << kuhn(left, weights, m, n) << "\n";
	}
	return 0;
}