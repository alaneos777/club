#include <bits/stdc++.h>
using namespace std;

struct satisfiability_twosat{
	int n;
	vector<set<int>> imp;

	satisfiability_twosat(int n) : n(n), imp(2 * n) {}

	void add_edge(int u, int v){imp[u].insert(v);}

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
	int m, n;
	cin >> m >> n;
	vector<vector<char>> grid(m, vector<char>(n));
	vector<vector<int>> mapeo(m, vector<int>(n, -1));
	vector<vector<pair<int, int>>> attackers_rows(m, vector<pair<int, int>>(n, make_pair(-1, -1)));
	vector<vector<pair<int, int>>> attackers_cols(m, vector<pair<int, int>>(n, make_pair(-1, -1)));

	int cnt = 0;
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			cin >> grid[i][j];
			if(grid[i][j] == 'T'){
				mapeo[i][j] = cnt++;
			}
		}
	}

	satisfiability_twosat st(4*cnt);
	auto id = [&](int i, int d){
		return 4*i + d;
	};
	auto disable_tower = [&](int i, int d){
		st.implication(id(i, d), st.neg(id(i, d)));
	};
	auto add_rotation = [&](int i, int d){
		st.implication(id(i, d), st.neg(id(i, d+2)));
		st.implication(st.neg(id(i, d+2)), id(i, d));
	};
	auto enable_towers = [&](int i1, int d1, int i2, int d2){
		st.implication(st.neg(id(i1, d1)), id(i2, d2));
	};

	for(int i = 0; i < m; ++i){
		int prev = -1;
		for(int j = 0; j < n; ++j){
			if(grid[i][j] == 'T'){
				if(prev != -1){
					disable_tower(mapeo[i][prev], 0);
					disable_tower(mapeo[i][j], 2);
				}
				prev = j;
			}else if(grid[i][j] == '#'){
				prev = -1;
			}
		}
	}

	for(int j = 0; j < n; ++j){
		int prev = -1;
		for(int i = 0; i < m; ++i){
			if(grid[i][j] == 'T'){
				if(prev != -1){
					disable_tower(mapeo[prev][j], 3);
					disable_tower(mapeo[i][j], 1);
				}
				prev = i;
			}else if(grid[i][j] == '#'){
				prev = -1;
			}
		}
	}

	for(int i = 0; i < cnt; ++i){
		add_rotation(i, 0);
		add_rotation(i, 1);
	}

	for(int i = 0; i < m; ++i){
		int prev = -1;
		for(int j = 0; j < n; ++j){
			if(grid[i][j] == 'T'){
				prev = j;
			}else if(grid[i][j] == '#'){
				prev = -1;
			}else if(grid[i][j] == 'n'){
				attackers_rows[i][j].first = prev;
			}
		}
		prev = -1;
		for(int j = n-1; j >= 0; --j){
			if(grid[i][j] == 'T'){
				prev = j;
			}else if(grid[i][j] == '#'){
				prev = -1;
			}else if(grid[i][j] == 'n'){
				attackers_rows[i][j].second = prev;
			}
		}
	}

	for(int j = 0; j < n; ++j){
		int prev = -1;
		for(int i = 0; i < m; ++i){
			if(grid[i][j] == 'T'){
				prev = i;
			}else if(grid[i][j] == '#'){
				prev = -1;
			}else if(grid[i][j] == 'n'){
				attackers_cols[i][j].first = prev;
			}
		}
		prev = -1;
		for(int i = m-1; i >= 0; --i){
			if(grid[i][j] == 'T'){
				prev = i;
			}else if(grid[i][j] == '#'){
				prev = -1;
			}else if(grid[i][j] == 'n'){
				attackers_cols[i][j].second = prev;
			}
		}
	}

	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			if(grid[i][j] == 'n'){
				int l, r;
				tie(l, r) = attackers_rows[i][j];
				vector<pair<int, int>> posible;
				if(l != -1 && r == -1){
					posible.emplace_back(mapeo[i][l], 0);
				}else if(l == -1 && r != -1){
					posible.emplace_back(mapeo[i][r], 2);
				}
				int u, d;
				tie(u, d) = attackers_cols[i][j];
				if(u != -1 && d == -1){
					posible.emplace_back(mapeo[u][j], 3);
				}else if(u == -1 && d != -1){
					posible.emplace_back(mapeo[d][j], 1);
				}
				if(posible.size() == 1) posible.push_back(posible.back());
				enable_towers(posible[0].first, posible[0].second, posible[1].first, posible[1].second);
			}
		}
	}

	vector<bool> ans = st.solve();
	vector<int> dir(cnt);
	for(int i = 0; i < cnt; ++i){
		if(ans[id(i, 0)] && ans[id(i, 1)]){
			dir[i] = 3;
		}else if(ans[id(i, 1)] && ans[id(i, 2)]){
			dir[i] = 4;
		}else if(ans[id(i, 2)] && ans[id(i, 3)]){
			dir[i] = 1;
		}else if(ans[id(i, 3)] && ans[id(i, 0)]){
			dir[i] = 2;
		}
	}

	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			if(grid[i][j] == 'T'){
				cout << dir[mapeo[i][j]];
 			}else{
 				cout << grid[i][j];
 			}
		}
		cout << "\n";
	}

	return 0;
}