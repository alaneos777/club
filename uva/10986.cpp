#include <bits/stdc++.h>
using namespace std;

struct arista{
	int v, w;
};

int inf = 1e9;

struct comparador{
	bool operator() (const arista & a, const arista & b) const{
		if(a.w == b.w){
			return a.v > b.v;
		}else{
			return a.w > b.w;
		}
	}
};

int answer(int n, int s, int t, vector< vector<arista> > & nodos){
	priority_queue<arista, vector<arista>, comparador> cola;
	vector<int> costos(n, inf);
	vector<bool> visitados(n, false);
	cola.push({s, 0});
	costos[s] = 0;
	while(!cola.empty()){
		arista actual = cola.top();
		cola.pop();
		if(visitados[actual.v]) continue;
		visitados[actual.v] = true;
		if(actual.v == t) return actual.w;
		for(arista & dest : nodos[actual.v]){
			if(visitados[dest.v]) continue;
			int nuevo = costos[actual.v] + dest.w;
			if(nuevo < costos[dest.v]){
				cola.push({dest.v, nuevo});
				costos[dest.v] = nuevo;
			}
		}
	}
	return -1;
}

int main(){
	ios_base::sync_with_stdio(0);
	int N, n, m, s, t, u, v, w, ans;
	cin >> N;
	for(int caso = 1; caso <= N; ++caso){
		cin >> n >> m >> s >> t;
		vector< vector<arista> > nodos(n, vector<arista>());
		for(int i = 0; i < m; ++i){
			cin >> u >> v >> w;
			nodos[u].push_back({v, w});
			nodos[v].push_back({u, w});
		}
		int ans = answer(n, s, t, nodos);
		cout << "Case #" << caso << ": ";
		if(ans == -1){
			cout << "unreachable";
		}else{
			cout << ans;
		}
		cout << "\n";
	}
	return 0;
}