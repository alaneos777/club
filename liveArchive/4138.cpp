#include <bits/stdc++.h>
using namespace std;

struct disjointSet{
    int N;
    vector<short int> rank;
    vector<int> parent;

    disjointSet(int N){
        this->N = N;
        parent.resize(N);
        rank.resize(N);
    }

    void makeSet(int v){
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
        }else{
            parent[b] = a;
            if(rank[a] == rank[b]){
                ++rank[a];
            }
        }
    }
};

struct edge{
	int u, v, cost;
	bool operator<(const edge & e) const{
		return cost < e.cost;
	}
};

inline int mod(int a, int b){
	int r = a % b;
	if(r < 0) r += b;
	return r;
}

int rolls(const string &a, const string & b){
	int ans = 0;
	for(int i = 0; i < 4; ++i){
		ans += min(mod(a[i] - b[i], 10), mod(b[i] - a[i], 10));
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		vector<string> keys(n);
		disjointSet DS(n);
		int ans = 1 << 30;
		for(int i = 0; i < n; ++i){
			cin >> keys[i];
			DS.makeSet(i);
			ans = min(ans, rolls("0000", keys[i]));
		}
		vector<edge> edges;
		for(int i = 0; i < n; ++i){
			for(int j = i + 1; j < n; ++j){
				int r = rolls(keys[i], keys[j]);
				edges.push_back({i, j, r});
			}
		}
		sort(edges.begin(), edges.end());
		int mstSize = 0, i = 0;
		while(i < edges.size() && mstSize < n - 1){
			edge current = edges[i++];
			if(DS.findSet(current.u) != DS.findSet(current.v)){
				DS.unionSet(current.u, current.v);
				ans += current.cost;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}