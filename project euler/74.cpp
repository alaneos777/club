#include <bits/stdc++.h>
using namespace std;

vector<int> fact(10, 1);

const int M = 3e6;
vector<int> length(M);
vector<int> state(M);
vector<int> adj(M);
vector<bool> cyclic(M);

void dfs(int u){
	state[u] = 1;
	int v = 0;
	int tmp = u;
	do{
		int digit = tmp % 10;
		tmp /= 10;
		v += fact[digit];
	}while(tmp);
	adj[u] = v;
	if(state[v] == 0){
		dfs(v);
		if(!cyclic[u]) length[u] = length[v] + 1;
	}else if(state[v] == 1){
		int cycle_length = 0;
		int curr = u;
		do{
			curr = adj[curr];
			cyclic[curr] = true;
			cycle_length++;
		}while(curr != u);
		do{
			length[curr] = cycle_length;
			curr = adj[curr];
		}while(curr != u);
	}else{
		length[u] = length[v] + 1;
	}
	state[u] = 2;
}

const int N = 999999;

int main(){
	int ans = 0;
	for(int i = 1; i <= 9; ++i){
		fact[i] = i * fact[i-1];
	}
	for(int i = 0; i <= N; ++i){
		if(state[i] == 0){
			dfs(i);
		}
	}
	for(int i = 0; i <= N; ++i){
		if(length[i] == 60) ans++;
	}
	cout << ans << "\n";
	return 0;
}