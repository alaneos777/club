#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using lli = int64_t;

using vec = vector<uint32_t>;
using mat = vector<vec>;

mat operator+(const mat & a, const mat & b){
	int n = a.size();
	mat c(n, vec(n));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

mat operator*(const mat & a, const mat & b){
	int n = a.size();
	mat c(n, vec(n));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			for(int k = 0; k < n; ++k){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}

mat power(mat a, lli b){
	int n = a.size();
	mat ans(n, vec(n));
	for(int i = 0; i < n; ++i) ans[i][i] = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

mat geometric(const mat & a, lli k){
	int n = a.size();
	if(k == 0){
		mat I(n, vec(n));
		for(int i = 0; i < n; ++i) I[i][i] = 1;
		return I;
	}else{
		mat ans = power(a, (k + 1) / 2);
		for(int i = 0; i < n; ++i) ans[i][i] += 1;
		ans = ans * geometric(a, (k - 1) / 2);
		if(k % 2 == 0) ans = ans + power(a, k);
		return ans;
	}
}

const pair<int, int> movs[8] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	mat adj(64, vec(64));
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			for(auto mov : movs){
				int dx, dy;
				tie(dx, dy) = mov;
				int ni = i + dx;
				int nj = j + dy;
				if(0 <= ni && ni < 8 && 0 <= nj && nj < 8){
					adj[i*8 + j][ni*8 + nj] += 1;
				}
			}
		}
	}
	lli k;
	cin >> k;
	mat ans = geometric(adj, k);
	uint32_t ways = 0;
	for(int i = 0; i < 64; ++i) ways += ans[0][i];
	cout << ways << "\n";
	return 0;
}