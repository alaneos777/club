#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct disjointSet{
	int N;
	vector<short int> rank;
	vector<int> parent;
	vector<lli> count;

	disjointSet(int N){
		this->N = N;
		parent.resize(N);
		rank.resize(N);
		count.resize(N);
	}

	void makeSet(int v){
		count[v] = 0;
		parent[v] = v;
	}

	int findSet(int v){
		if(v == parent[v]) return v;
		return parent[v] = findSet(parent[v]);
	}

	void unionSet(int a, int b){
		a = findSet(a);
		b = findSet(b);
		if(a == b) return;
		if(rank[a] < rank[b]){
			parent[a] = b;
			count[b] += count[a] + 1;
		}else{
			parent[b] = a;
			count[a] += count[b] + 1;
			if(rank[a] == rank[b]){
				++rank[a];
			}
		}
	}
};

template<typename T>
struct FenwickTree{
	int N;
	vector<T> bit;

	FenwickTree(int N){
		this->N = N;
		bit.assign(N, 0);
	}

	void update(int pos, T value){
		while(pos < N){
			bit[pos] += value;
			pos |= pos + 1;
		}
	}

	T query(int r){
		T res = 0;
		while(r >= 0){
			res += bit[r];
			r = (r & (r + 1)) - 1;
		}
		return res;
	}

	T query(int l, int r){
		return query(r) - query(l - 1);
	}
};

struct edge{
	int a, b, c;
	bool operator<(const edge & e) const{
		return c < e.c;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, q;
	cin >> n >> q;
	int a, b;
	int c, l, r;
	disjointSet ds(n);
	for(int i = 0; i < n; ++i){
		ds.makeSet(i);
	}
	vector<edge> edges(n-1);
	vector<int> weights(n+1);
	FenwickTree<lli> bit(n-1);
	for(int i = 0; i < n-1; ++i){
		cin >> edges[i].a >> edges[i].b >> edges[i].c;
		edges[i].a--, edges[i].b--;
	}
	sort(edges.begin(), edges.end());
	unordered_map<int, int> mapping;
	int idx = 0;
	for(int i = 0; i < n-1; ++i){
		edge & curr = edges[i];
		weights[i + 1] = curr.c;
		if(mapping.count(curr.c) == 0) mapping[curr.c] = idx++;
		bit.update(mapping[curr.c], (ds.count[ds.findSet(curr.a)] + 1) * (ds.count[ds.findSet(curr.b)] + 1));
		ds.unionSet(curr.a, curr.b);
	}
	weights[n] = numeric_limits<int>::max();
	for(int i = 0; i < q; ++i){
		cin >> l >> r;
		int w1 = weights[lower_bound(weights.begin(), weights.end(), l) - weights.begin()];
		int w2 = weights[upper_bound(weights.begin(), weights.end(), r) - weights.begin() - 1];
		if(w1 <= w2){
			cout << bit.query(mapping[w1], mapping[w2]) << "\n";
		}else{
			cout << "0\n";
		}
	}
	return 0;
}