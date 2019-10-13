#include <bits/stdc++.h>
using namespace std;

int main(){
	int n = 1e6;
	vector<int> divs(n + 1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j] += i;
		}
	}
	for(int i = 1; i <= n; ++i){
		divs[i] -= i;
	}
	vector<int> vis(n + 1);
	vector<int> adj(n + 1);
	vector<int> smallest(n + 1, 1<<30);
	int id_chain = 0;
	int longest_chain_length = -1;
	int longest_chain_id = -1;
	function<void(int)> dfs = [&](int u){
		vis[u] = 1;
		int v = divs[u];
		if(v <= n){
			adj[u] = v;
			if(vis[v] == 0){
				dfs(v);
			}else if(vis[v] == 1){
				int curr = u;
				int chain_length = 0;
				do{
					curr = adj[curr];
					smallest[id_chain] = min(smallest[id_chain], curr);
					chain_length++;
				}while(curr != u);
				if(longest_chain_id == -1 || chain_length > longest_chain_length){
					longest_chain_length = chain_length;
					longest_chain_id = id_chain;
				}
				id_chain++;
			}
		}
		vis[u] = 2;
	};
	vector<int> id(n + 1);
	for(int i = 0; i <= n; ++i){
		if(vis[i] == 0){
			dfs(i);
		}
	}
	cout << smallest[longest_chain_id] << "\n";
	return 0;
}