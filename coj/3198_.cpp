#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct info{
	lli prestige;
	int m;
	int index;
	vector<int> women;
	info(){
		return;
	}
	info(lli prestige, int m){
		this->prestige = prestige;
		this->m = m;
		women.resize(m);
	}
	bool operator>(const info & i) const{
		return prestige > i.prestige;
	}
};

int augmenting_path(int u, vector<info> & graph, vector<bool> & used, vector<int> & left, vector<int> & right){
	used[u] = true;
	for(int & v : graph[u].women){
		if(right[v] == -1){
			right[v] = u;
			left[u] = v;
			return u;
		}
	}
	for(int & v : graph[u].women){
		if(!used[right[v]] && augmenting_path(right[v], graph, used, left, right) != -1){
			right[v] = u;
			left[u] = v;
			return u;
		}
	}
	return -1;
}

vector<pair<int, int>> max_matching(vector<info> & graph, int l, int r){
	vector<int> left(l, -1), right(r, -1);
	vector<bool> used(l, false);
	for(int u = 0; u < l; ++u){
		augmenting_path(u, graph, used, left, right);
		fill(used.begin(), used.end(), false);
	}
	vector<pair<int, int>> ans;
	for(int u = 0; u < r; ++u){
		if(right[u] != -1){
			ans.push_back({right[u], u});
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<info> men(n);
	for(int i = 0; i < n; ++i){
		int pi, mi, mij;
		cin >> pi >> mi;
		men[i] = info(pi, mi);
		men[i].index = i;
		for(int j = 0; j < mi; ++j){
			cin >> mij;
			--mij;
			men[i].women[j] = mij;
		}
	}
	sort(men.begin(), men.end(), greater<info>());
	auto matching = max_matching(men, n, m);
	long double total = 0.0;
	for(auto & edge : matching){
		total += log10l((long double)men[edge.first].prestige);
		//cout << men[edge.first].index+1 << "<->" << edge.second+1 << ", " << men[edge.first].prestige << "\n";
	}
	cout << (int)(floor(total + 1.0l)) << "\n";
	return 0;
}