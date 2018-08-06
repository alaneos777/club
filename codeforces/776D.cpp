#include <bits/stdc++.h>
using namespace std;

struct satisfiability_twosat
{
	int n;
	vector<vector<int>> imp;

	satisfiability_twosat(int n) : n(n), imp(2 * n) {}

	void add_edge(int u, int v)
	{
		imp[u].push_back(v);
	}

	int neg(int u) { return (n << 1) - u - 1; }

	void implication(int u, int v)
	{
		add_edge(u, v);
		add_edge(neg(v), neg(u));
	}

	vector<bool> solve()
	{
		int size = 2 * n;
		vector<int> S, B, I(size);

		function<void(int)> dfs = [&](int u)
		{
			B.push_back(I[u] = S.size());
			S.push_back(u);

			for (int v : imp[u])
				if (!I[v]) dfs(v);
				else while (I[v] < B.back()) B.pop_back();

			if (I[u] == B.back())
				for (B.pop_back(), ++size; I[u] < S.size(); S.pop_back())
					I[S.back()] = size;
		};

		for (int u = 0; u < 2 * n; ++u)
			if (!I[u]) dfs(u);

		vector<bool> values(n);

		for (int u = 0; u < n; ++u)
			if (I[u] == I[neg(u)]) return {};
			else values[u] = I[u] < I[neg(u)];

		return values;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m, count, door;
	cin >> n >> m;
	vector<bool> init(n);
	vector<vector<int>> doors(n);
	for(int i = 0; i < n; ++i){
		cin >> door;
		init[i] = door;
	}
	for(int i = 0; i < m; ++i){
		cin >> count;
		while(count--){
			cin >> door;
			doors[door-1].push_back(i);
		}
	}
	satisfiability_twosat SAT(m);
	for(int i = 0; i < n; ++i){
		if(init[i]) SAT.implication(doors[i][0], doors[i][1]), SAT.implication(doors[i][1], doors[i][0]);
		else SAT.implication(doors[i][0], SAT.neg(doors[i][1])), SAT.implication(SAT.neg(doors[i][1]), doors[i][0]);
	}
	auto ans = SAT.solve();
	if(ans.size()) cout << "YES\n";
	else cout << "NO\n";
	return 0;
}