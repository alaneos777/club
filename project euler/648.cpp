#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const lli mod = 1e9;

using poly = vector<lli>;

const int N = 1001;

poly operator+(const poly & a, const poly & b){
	int sz = max(a.size(), b.size());
	poly c(min(sz, N));
	for(int i = 0; i < c.size(); ++i){
		if(i < a.size()) c[i] += a[i];
		if(i < b.size()) c[i] += b[i];
		if(c[i] >= mod) c[i] -= mod;
	}
	return c;
}

poly operator*(const poly & a, const poly & b){
	int sz = a.size() + b.size() - 1;
	poly c(min(sz, N));
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			if(i+j < c.size()){
				(c[i+j] += a[i] * b[j]) %= mod;
			}else{
				break;
			}
		}
	}
	return c;
}

poly operator*(const poly & a, lli n){
	auto c = a;
	for(lli & y : c){
		y = y * n % mod;
	}
	return c;
}

poly rec(const vector<poly> & P, const vector<poly> & init, lli n){
	int deg = P.size();
	vector<poly> ans(deg, {0}), R(2*deg, {0});
	ans[0] = {1};
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), poly{0});
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				R[i + j + d] = R[i + j + d] + ans[i] * ans[j];
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				R[i + j] = R[i + j] + R[i + deg] * P[j];
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	poly nValue = {0};
	for(int i = 0; i < deg; i++)
		nValue = nValue + ans[i] * init[i];
	return nValue;
}

int main(){
	int i = 2;
	vector<poly> init = {{1, -1+mod}, {0, 1, -1+mod}};
	poly ans = {0}, prev = {0};
	while(true){
		int sq = i*i;
		int a0 = (i-1)*(i-1) + 1;
		int a1 = (i-1)*(i-1) + 2;
		int n = sq - a0;
		poly tmp = rec({{1, -1+mod}, {0, 1}}, init, n-1);
		poly curr = rec({{1, -1+mod}, {0, 1}}, init, n);
		ans = ans + curr * (i-1);
		init[0] = tmp * poly{1, -1+mod};
		init[1] = init[0] * poly{0, 1};
		++i;
		if(ans == prev) break;
		prev = ans;
	}
	lli sum = 0;
	for(lli x : ans){
		sum = (sum + x) % mod;
	}
	cout << sum << "\n";
	return 0;
}