#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int mex(const vector<int> & a){
	int n = a.size();
	vector<bool> is(n);
	for(int ai : a){
		if(ai < n){
			is[ai] = true;
		}
	}
	for(int i = 0; i < n; ++i){
		if(!is[i]) return i;
	}
	return n;
}

const int N = 1e7 + 19;
const int C = 100;
const lli mod = 1e9;
int mem[N+100];

int g(int n){
	if(mem[n] != -1) return mem[n];
	vector<int> st;
	for(int p : {2, 3, 5, 7}){
		if(n - p >= 0){
			st.push_back(g(n - p));
		}
	}
	return mem[n] = mex(st);
}

int near(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

auto mult(const vector<int> & a, const vector<int> & b){
	vector<int> c(a.size());
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			int k = i ^ j;
			c[k] += (lli)a[i] * b[j] % mod;
			if(c[k] >= mod) c[k] -= mod;
		}
	}
	return c;
}

int main(){
	memset(mem, -1, sizeof(mem));
	vector<int> P;
	for(int i = 0; i < N; ++i){
		int pos = g(i);
		if(pos >= P.size()) P.resize(pos+1);
		P[pos]++;
	}
	int sz = near(P.size());
	P.resize(sz);
	vector<int> Q(sz);
	Q[0] = 1;
	for(int i = 1; i <= 2*C; ++i){
		Q = mult(P, Q);
	}
	int ans = 0;
	for(int i = 1; i < sz; ++i){
		ans += Q[i];
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}