#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const int B = 60, W = 40;

using poly = vector<vector<lli>>;

vector<lli> operator+(const vector<lli>& a, const vector<lli>& b){
	vector<lli> c(max(a.size(), b.size()));
	for(int i = 0; i < c.size(); ++i){
		if(i < a.size()) c[i] += a[i];
		if(i < b.size()) c[i] += b[i];
	}
	return c;
}

vector<lli> operator*(const vector<lli>& a, const vector<lli>& b){
	if(a.empty() || b.empty()) return {};
	vector<lli> c(min(W+1, int(a.size() + b.size() - 1)));
	for(int i = 0; i < a.size() && i < c.size(); ++i){
		for(int j = 0; j < b.size() && j < c.size(); ++j){
			if(i+j >= c.size()) break;
			c[i+j] += a[i]*b[j];
		}
	}
	return c;
}

poly operator+(const poly& a, const poly& b){
	poly c(max(a.size(), b.size()));
	for(int i = 0; i < c.size(); ++i){
		if(i < a.size()) c[i] = c[i] + a[i];
		if(i < b.size()) c[i] = c[i] + b[i];
	}
	return c;
}

poly operator*(const poly& a, const poly& b){
	if(a.empty() || b.empty()) return {};
	poly c(min(B+1, int(a.size() + b.size() - 1)));
	for(int i = 0; i < a.size() && i < c.size(); ++i){
		for(int j = 0; j < b.size() && j < c.size(); ++j){
			if(i+j >= c.size()) break;
			c[i+j] = c[i+j] + a[i]*b[j];
		}
	}
	return c;
}

poly operator/(poly a, lli n){
	for(auto& p : a){
		for(lli& x : p){
			x /= n;
		}
	}
	return a;
}

int main(){
	int N = B+W;
	vector<poly> base(N+1, poly(B+1, vector<lli>(W+1)));
	base[1] = poly(B+1, vector<lli>(W+1, 1));
	for(int n = 2; n <= N; ++n){
		for(int i = 0; i*n <= B; ++i){
			for(int j = 0; j*n <= W; ++j){
				base[n][i*n][j*n] = base[1][i][j];
			}
		}
	}
	vector<poly> Z(N+1);
	Z[0] = {{1}};
	for(int n = 1; n <= N; ++n){
		for(int l = 1; l <= n; ++l){
			Z[n] = Z[n] + base[l] * Z[n-l];
		}
		Z[n] = Z[n] / n;
	}
	cout << Z[N][B][W] << "\n";
	return 0;
}