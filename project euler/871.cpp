#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> Blossom(vector<set<int>>& graph) {
	int n = graph.size(), timer = -1;
	vector<int> mate(n, -1), label(n), parent(n), orig(n), aux(n, -1), q;
	auto lca = [&](int x, int y) {
		for (timer++; ; swap(x, y)) {
			if (x == -1) continue;
			if (aux[x] == timer) return x;
			aux[x] = timer;
			x = (mate[x] == -1 ? -1 : orig[parent[mate[x]]]);
		}
	};
	auto blossom = [&](int v, int w, int a) {
		while (orig[v] != a) {
			parent[v] = w; w = mate[v];
			if (label[w] == 1) label[w] = 0, q.push_back(w);
			orig[v] = orig[w] = a; v = parent[w];
		}
	};
	auto augment = [&](int v) {
		while (v != -1) {
			int pv = parent[v], nv = mate[pv];
			mate[v] = pv; mate[pv] = v; v = nv;
		}
	};
	auto bfs = [&](int root) {
		fill(label.begin(), label.end(), -1);
		iota(orig.begin(), orig.end(), 0);
		q.clear(); 
		label[root] = 0; q.push_back(root);
		for (int i = 0; i < (int)q.size(); ++i) {
			int v = q[i];
			for (auto x : graph[v]) {
				if (label[x] == -1) {
					label[x] = 1; parent[x] = v;
					if (mate[x] == -1) 
						return augment(x), 1;
					label[mate[x]] = 0; q.push_back(mate[x]);
				} else if (label[x] == 0 && orig[v] != orig[x]) {
					int a = lca(orig[v], orig[x]);
					blossom(x, v, a); blossom(v, x, a);
				}
			}
		}
		return 0;
	};

	for (int i = 0; i < n; i++) 
		if (mate[i] == -1) 
			bfs(i);
	return mate;
}

int D(int n){
	vector<set<int>> adj(n);
	for(int i = 0; i < n; ++i){
		int j = ((lli)i*i*i + i + 1) % n;
		if(i != j){
			adj[i].insert(j);
			adj[j].insert(i);
		}
	}
	auto matching = Blossom(adj);
	int ans = 0;
	for(int i = 0; i < n; ++i){
		if(matching[i] != -1) ans++;
	}
	return ans/2;
}

int main(){
	int ans = 0;
	for(int i = 1; i <= 100; ++i){
		int val = D(1e5 + i);
		ans += val;
		cout << i << " " << val << "\n";
	}
	cout << ans << "\n";
	return 0;
}