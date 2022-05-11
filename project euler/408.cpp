#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

const int M = 1e7;
vector<int> fact(2*M+1, 1), inv(2*M+1, 1), invfact(2*M+1, 1);

lli ncr(int n, int r){
	if(r < 0 || r > n) return 0;
	return (lli)fact[n] * invfact[r] % mod * invfact[n-r] % mod;
}

int main(){
	for(lli i = 2; i <= 2*M; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod/i) * inv[mod%i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	set<int> sq;
	for(int i = 1; i*i <= 2*M; ++i){
		sq.insert(i*i);
	}
	vector<pair<int, int>> obstacles;
	for(int x = 1; x*x <= M; ++x){
		for(int y = 1; y*y <= M; ++y){
			if(sq.count(x*x+y*y)){
				obstacles.emplace_back(x*x, y*y);
			}
		}
	}
	obstacles.emplace_back(M, M);
	int k = obstacles.size();
	vector<int> d(k);
	for(int i = 0; i < k; ++i){
		auto[xi, yi] = obstacles[i];
		d[i] = ncr(xi+yi, xi);
		for(int t = 0; t < i; ++t){
			auto[xt, yt] = obstacles[t];
			if(xt <= xi && yt <= yi){
				d[i] -= d[t]*ncr(xi-xt + yi-yt, xi-xt) % mod;
				if(d[i] < 0) d[i] += mod;
			}
		}
	}
	cout << d[k-1] << "\n";
	return 0;
}