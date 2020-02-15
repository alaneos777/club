#include <bits/stdc++.h>
using namespace std;
using lli = bitset<128>;

lli calc_hash(const vector<int> & info){
	lli hash = 0;
	for(const int & ii : info){
		hash = (hash << 10) | lli(ii);
	}
	return hash;
}

unordered_map<lli, int> mapeo;
vector<lli> hashes;
int V = 0;

int getId(lli hash){
	auto it = mapeo.find(hash);
	if(it == mapeo.end()){
		hashes.push_back(hash);
		return mapeo[hash] = V++;
	}
	return it->second;
};

const int MX = 1.2e6;

vector<int> adj[MX], bipartite[2*MX];
vector<int> info[110];
bitset<2*MX> visited, incident;

void rec(lli hash){
	int u = getId(hash);
	visited[u] = true;
	int p_pow = 0;
	lli left = 0, right = hash;
	while(hash.any()){
		lli d = hash & lli(1023);
		right = (right ^ d) >> 10;
		lli newHash = left | (right << p_pow);
		if(newHash != 0){
			int v = getId(newHash);
			adj[u].push_back(v);
			if(!visited[v]){
				rec(newHash);
			}
		}
		left = left | (d << p_pow);
		hash >>= 10;
		p_pow += 10;
	}
}

int Left[MX], Right[MX];
bitset<MX> used;

bool tryKuhn(int u){
	if(used[u]) return false;
	used[u] = true;
	for(int v : adj[u]){
		if(Right[v] == -1 || tryKuhn(Right[v])){
			Right[v] = u;
			Left[u] = v;
			return true;
		}
	}
	return false;
}

void dfs(int u){
	visited[u] = true;
	for(int v : bipartite[u]){
		if(!visited[v]){
			dfs(v);
		}
	}
}

unordered_map<string, int> mapeo_cadena;
vector<string> cadenas;

vector<string> getNames(lli hash){
	vector<string> ans;
	while(hash.any()){
		lli d = hash & lli(1023);
		ans.push_back(cadenas[d.to_ulong() - 1]);
		hash >>= 10;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	memset(Left, -1, sizeof(Left));
	memset(Right, -1, sizeof(Right));
	int n, a;
	string str;
	int cnt = 1;
	cin >> n;
	for(int t = 0; t < n; ++t){
		cin >> a;
		while(a--){
			cin >> str;
			if(mapeo_cadena.find(str) == mapeo_cadena.end()){
				mapeo_cadena[str] = cnt++;
				cadenas.push_back(str);
			}
			info[t].push_back(mapeo_cadena[str]);
		}
		sort(info[t].begin(), info[t].end(), greater<int>());
	}
	for(int t = 0; t < n; ++t){
		rec(calc_hash(info[t]));
	}

	for(int u = 0; u < V; ++u){
		tryKuhn(u);
		used.reset();
	}

	set<pair<int, int>> matching;
	for(int u = 0; u < V; ++u){
		if(Right[u] != -1){
			matching.emplace(Right[u], u);
			incident[Right[u]] = true;
			incident[u + V] = true;
		}
	}

	for(int i = 0; i < V; ++i){
		for(int v : adj[i]){
			if(matching.count({i, v})){
				bipartite[v + V].push_back(i);
			}else{
				bipartite[i].push_back(v + V);
			}
		}
	}

	visited.reset();
	for(int i = 0; i < V; ++i){
		if(!incident[i] && !visited[i]){
			dfs(i);
		}
	}

	set<int> VC;
	for(int i = 0; i < V; ++i){
		if(!visited[i]){
			VC.insert(i);
		}
	}
	for(int i = V; i < 2*V; ++i){
		if(visited[i]){
			VC.insert(i - V);
		}
	}

	vector<int> antichain;
	for(int i = 0; i < V; ++i){
		if(!VC.count(i)){
			antichain.push_back(i);
		}
	}

	assert(V - matching.size() == antichain.size());

	cout << "Hay " << V - matching.size() << " equipos:" << "\n";

	for(int i = 0; i < antichain.size(); ++i){
		cout << "Equipo #" << i+1 << ": ";
		vector<string> team = getNames(hashes[antichain[i]]);
		for(const string & alg : team){
			cout << alg << " ";
		}
		cout << "\n";
	}

	return 0;
}
