#include <bits/stdc++.h>
using namespace std;

struct disjointSet{
	int N;
	vector<int> parent, power;

	disjointSet(int N): N(N), parent(N), power(N){}

	void makeSet(int v, int pi){
		power[v] = pi;
		parent[v] = v;
	}

	int update(int v){
		if(v == parent[v]) return v;
		int k = update(parent[v]);
		power[v] = min(power[v], power[parent[v]]);
		return parent[v] = k;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	disjointSet ds(n);
	for(int i = 0; i < n; ++i){
		int pi;
		cin >> pi;
		ds.makeSet(i, pi);
	}
	while(q--){
		char c; int i, j;
		cin >> c;
		if(c == '+'){
			cin >> i >> j; //j -> i
			ds.parent[j-1] = i-1;
		}else{
			cin >> i;
			ds.update(i-1);
			cout << ds.power[i-1] << "\n";
		}
	}
	return 0;
}