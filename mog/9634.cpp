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
int V = 0;

int getId(lli hash){
	auto it = mapeo.find(hash);
	if(it == mapeo.end()){
		return mapeo[hash] = V++;
	}
	return it->second;
};

const int MX = 1.2e6;

vector<int> adj[MX];
vector<int> info[110];
bitset<MX> visited;

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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	memset(Left, -1, sizeof(Left));
	memset(Right, -1, sizeof(Right));
	int n, a;
	string str;
	unordered_map<string, int> mapeo_cadena;
	int cnt = 1;
	cin >> n;
	for(int t = 0; t < n; ++t){
		cin >> a;
		while(a--){
			cin >> str;
			if(mapeo_cadena.find(str) == mapeo_cadena.end()){
				mapeo_cadena[str] = cnt++;
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

	int ans = 0;
	for(int u = 0; u < V; ++u){
		if(Right[u] != -1){
			ans++;
		}
	}

	cout << V - ans << "\n";

	return 0;
}
