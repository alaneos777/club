#include <bits/stdc++.h>
using namespace std;
using tup = array<int, 3>;

int P(int a, int b){
	tup cap = {a, b, a+b};
	auto pour = [&](const tup& a, int u, int v){
		int t = min(a[u], cap[v] - a[v]);
		tup ans;
		ans[u] = a[u] - t;
		ans[v] = a[v] + t;
		ans[3-u-v] = a[3-u-v];
		return ans;
	};
	tup start = {a, b, 0};
	queue<tup> q;
	q.push(start);
	map<tup, int> dis;
	dis[start] = 0;
	while(!q.empty()){
		tup u = q.front(); q.pop();
		if(u[0] == 1 || u[1] == 1 || u[2] == 1){
			return dis[u];
		}
		for(int i = 0; i < 3; ++i){
			for(int j = 0; j < 3; ++j){
				if(i == j) continue;
				tup v = pour(u, i, j);
				if(dis.count(v) == 0){
					dis[v] = dis[u] + 1;
					q.push(v);
				}
			}
		}
	}
	return -1;
}

int main(){
	for(int p = 1; p <= 20; ++p){
		for(int q = 1; q <= 20; ++q){
			if(__gcd(p, q) == 1){
				int ans = P((1<<p)-1, (1<<q)-1);
				cout << p << ", " << q << ": " << ans << " " << ans/pow(2,q) << "\n";
			}
		}
		cout << "\n";
	}
	return 0;
}