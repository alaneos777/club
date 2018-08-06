#include <bits/stdc++.h>
using namespace std;

const int M = 1e6 + 10;
vector<int> graph[M];
int in[M], out[M];
pair<int, int> S[4*M];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, q, u, v, a, b;
	cin >> n >> q;
	for(int i = 1; i < n; ++i){
		cin >> u >> v;
		--u, --v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	int t = 0, pos = -1;
	S[++pos] = {0, -1};
	while(pos >= 0){
		int u = S[pos].first;
		int prev = S[pos--].second;
		if(u == -1){
			out[prev] = t++;
			continue;
		}
		in[u] = t++;
		S[++pos] = {-1, u};
		for(int v : graph[u])
			if(v != prev)
				S[++pos] = {v, u};
	}
	while(q--){
		cin >> a >> b;
		--a, --b;
		if(a == b || (in[a] < in[b] && out[b] < out[a])) cout << "0\n";
		else cout << "1\n";
	}
	return 0;
}