#include <bits/stdc++.h>
using namespace std;

struct satisfiability_twosat{
	int n;
	vector<vector<int>> imp;

	satisfiability_twosat(int n) : n(n), imp(2 * n) {}

	void add_edge(int u, int v){imp[u].push_back(v);}

	int neg(int u){return (n << 1) - u - 1;}

	void implication(int u, int v){
		add_edge(u, v);
		add_edge(neg(v), neg(u));
	}

	vector<bool> solve(){
		int size = 2 * n;
		vector<int> S, B, I(size);

		function<void(int)> dfs = [&](int u){
			B.push_back(I[u] = S.size());
			S.push_back(u);

			for(int v : imp[u])
				if(!I[v]) dfs(v);
				else while (I[v] < B.back()) B.pop_back();

			if(I[u] == B.back())
				for(B.pop_back(), ++size; I[u] < S.size(); S.pop_back())
					I[S.back()] = size;
		};

		for(int u = 0; u < 2 * n; ++u)
			if(!I[u]) dfs(u);

		vector<bool> values(n);

		for(int u = 0; u < n; ++u)
			if(I[u] == I[neg(u)]) return {};
			else values[u] = I[u] < I[neg(u)];

		return values;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string str;
	int n, m;
	cin >> str >> str >> n >> m;
	satisfiability_twosat sat(n);
	for(int i = 1; i <= m; ++i){
		int a, b, zero;
		cin >> a >> b >> zero;
		int x = abs(a) - 1;
		int y = abs(b) - 1;
		if(a < 0) x = sat.neg(x);
		if(b < 0) y = sat.neg(y);
		sat.implication(sat.neg(x), y);
	}
	auto ans = sat.solve();
	if(ans.size() == 0){
		cout << "s UNSATISFIABLE\n";
	}else{
		cout << "s SATISFIABLE\n";
		cout << "v";
		for(int i = 1; i <= n; ++i){
			cout << " ";
			if(ans[i-1]) cout << i;
			else cout << -i;
		}
		cout << " 0\n";
	}
	return 0;
}