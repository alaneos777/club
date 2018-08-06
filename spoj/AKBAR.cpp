#include <bits/stdc++.h>
using namespace std;

struct grafo{
	vector<vector<int>> nodos;
	vector<int> values;
	int n;

	grafo(int n){
		nodos.resize(n + 1);
		values.resize(n + 1);
		this->n = n;
	}

	void addEdge(int a, int b){
		nodos[a].push_back(b);
		nodos[b].push_back(a);
	}

	void bfs(int start, int s){
		queue<int> pendientes;
		pendientes.push(start);
		vector<bool> visitados(n + 1, false);
		int dist = 0;
		while(!pendientes.empty()){
			if(dist > s) break;
			int actualSize = pendientes.size();
			while(actualSize--){
				int actual = pendientes.front();
				pendientes.pop();
				if(visitados[actual]) continue;
				visitados[actual] = true;
				values[actual]++;
				for(int dest : nodos[actual]){
					pendientes.push(dest);
				}
			}
			dist++;
		}
	}

	bool ans(){
		for(int i = 1; i <= n; i++){
			if(values[i] != 1) return false;
		}
		return true;
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	int t, n, r, m, a, b, k, s;
	cin >> t;
	while(t--){
		cin >> n >> r >> m;
		grafo ciudad(n);
		while(r--){
			cin >> a >> b;
			ciudad.addEdge(a, b);
		}
		while(m--){
			cin >> k >> s;
			ciudad.bfs(k, s);
		}
		if(ciudad.ans()){
			cout << "Yes\n";
		}else{
			cout << "No\n";
		}
	}
	return 0;
}