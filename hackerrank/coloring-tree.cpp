#include <bits/stdc++.h>
using namespace std;

struct FenwickTree{
	int N;
	vector<int> bit;

	FenwickTree(int N): N(N){
		bit.resize(N);
	}

	void update(int pos, int value){
		while(pos < N){
			bit[pos] += value;
			pos |= pos + 1;
		}
	}

	int query(int r){
		int res = 0;
		while(r >= 0){
			res += bit[r];
			r = (r & (r + 1)) - 1;
		}
		return res;
	}

	int query(int l, int r){
		return query(r) - query(l - 1);
	}
};

struct query{
	int l, r, index, S;
	bool operator<(const query & q) const{
		int c_o = l / S, c_q = q.l / S;
		if(c_o == c_q)
			return r < q.r;
		return c_o < c_q;
	}
};

vector<int> MO(const vector<int> & A, vector<query> & queries){
	vector<int> freq(*max_element(A.begin(), A.end()) + 1);
	FenwickTree ft(freq.size());
	vector<int> ans(queries.size());
	sort(queries.begin(), queries.end());
	int prevL = 0, prevR = -1;
	int i, j;
	for(const query & q : queries){
		for(i = prevL, j = min(prevR, q.l - 1); i <= j; ++i){
			freq[A[i]]--;
			if(freq[A[i]] == 0){
				ft.update(A[i], -1);
			}
		}
		for(i = prevL - 1; i >= q.l; --i){
			freq[A[i]]++;
			if(freq[A[i]] == 1){
				ft.update(A[i], 1);
			}
		}
		for(i = max(prevR + 1, q.l); i <= q.r; ++i){
			freq[A[i]]++;
			if(freq[A[i]] == 1){
				ft.update(A[i], 1);
			}
		}
		for(i = prevR; i >= q.r + 1; --i){
			freq[A[i]]--;
			if(freq[A[i]] == 0){
				ft.update(A[i], -1);
			}
		}
		prevL = q.l, prevR = q.r;
		ans[q.index] = ft.query(0, freq.size() - 1);
	}
	return ans;
}

int main(){
	ofstream fout(getenv("OUTPUT_PATH"));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, r;
	cin >> n >> m >> r;
	--r;
	vector<vector<int>> adj(n);
	for(int i = 0; i < n-1; ++i){
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	unordered_map<int, int> mapeo;
	int id = 0;
	vector<int> color(n);
	for(int i = 0; i < n; ++i){
		int ci;
		cin >> ci;
		if(mapeo.count(ci) == 0){
			mapeo[ci] = id++;
		}
		color[i] = mapeo[ci];
	}

	vector<int> start(n), end(n), arr(2*n);
	int pos = 0;
	function<void(int, int)> dfs = [&](int u, int p){
		start[u] = pos;
		arr[pos] = color[u];
		pos++;
		for(int v : adj[u]){
			if(v == p) continue;
			dfs(v, u);
		}
		end[u] = pos;
		arr[pos] = color[u];
		pos++;
	};
	dfs(r, -1);

	vector<query> queries(m);
	int S = 2*n / sqrt(m) + 1;

	for(int i = 0; i < m; ++i){
		int s;
		cin >> s;
		--s;
		queries[i] = {start[s], end[s], i, S};
	}
	auto resp = MO(arr, queries);
	for(int x : resp){
		fout << x << "\n";
	}
	return 0;
}