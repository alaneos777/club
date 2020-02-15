#include <bits/stdc++.h>
using namespace std;
 
bool similar(const string & a, const string & b, int k){
	int cnt = 0;
	for(int i = 0; i < a.size(); ++i){
		cnt += a[i] == b[i];
	}
	return cnt >= k;
}
 
struct edge{
	int v, color;
	edge(){}
	edge(int v, int color): v(v), color(color){}
};
 
void solve(){
	int n, m, k;
	cin >> n >> m >> k;
	vector<string> strings(n), strings_rev(n);
	for(int i = 0; i < n; ++i){
		cin >> strings[i];
		strings_rev[i] = strings[i];
		reverse(strings_rev[i].begin(), strings_rev[i].end());
	}
	vector<vector<edge>> adj(n);
	for(int i = 0; i < n; ++i){
		for(int j = i+1; j < n; ++j){
			bool b1 = similar(strings[i], strings[j], k);
			bool b2 = similar(strings[i], strings_rev[j], k);
			if(!b1 && !b2){
				cout << "-1\n";
				return;
			}
			if(b1 && b2){
				//cout << "string " << i << " and " << j << " are always similar\n";
			}else if(b1){
				//cout << "string " << i+1 << " and " << j+1 << " are similar but not if one of them is swapped\n";
				//require that ans[i] = ans[j]
				adj[i].emplace_back(j, 0);
				adj[j].emplace_back(i, 0);
			}else{
				//cout << "string " << i+1 << " and " << j+1 << " are not similar but yes if one of them is swapped\n";
				//require that ans[i] != ans[j]
				adj[i].emplace_back(j, 1);
				adj[j].emplace_back(i, 1);
			}
		}
	}
	vector<int> side(n, -1);
	vector<int> ans;
	queue<int> q;
	for(int i = 0; i < n; ++i){
		vector<vector<int>> comp(2);
		if(side[i] != -1) continue;
		q.push(i);
		side[i] = 0;
		comp[side[i]].push_back(i);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(const edge & e : adj[u]){
				if(side[e.v] == -1){
					q.push(e.v);
					side[e.v] = side[u] ^ e.color;
					comp[side[e.v]].push_back(e.v);
				}else{
					if((side[e.v] == side[u] && e.color == 1) || (side[e.v] != side[u] && e.color == 0)){
						cout << "-1\n";
						return;
					}
				}
			}
		}
		if(comp[0].size() > comp[1].size()) swap(comp[0], comp[1]);
		ans.insert(ans.end(), comp[0].begin(), comp[0].end());
	}
	cout << ans.size() << "\n";
	for(int ai : ans){
		cout << ai+1 << " ";
	}
	cout << "\n";
}
 
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}