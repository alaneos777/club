#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto muSieve(int n){
	vector<int> primes, mu(n+1), lp(n+1);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
			else{
				mu[d] = -mu[i];
			}
		}
	}
	return mu;
}

const int M = 2e7;
const auto mu = muSieve(M);

struct HASH{
  size_t operator()(const pair<int,int>&x)const{
    return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
  }
};

struct FenwickTree2D{
	int m, n;
	unordered_map<pair<int, int>, int, HASH> bit;

	FenwickTree2D(int m, int n): m(m), n(n){
		//bit.reserve(1<<20); bit.max_load_factor(0.25);
	}

	void update(int x, int y, int value){
		for(int i = x; i < m; i |= i+1){
			for(int j = y; j < n; j |= j+1){
				bit[{i,j}] += value;
			}
		}
	}

	int query(int x, int y){
		int res = 0;
		for(int i = x; i >= 0; i = (i & (i+1)) - 1){
			for(int j = y; j >= 0; j = (j & (j+1)) - 1){
				if(bit.find({i,j}) != bit.end()) res += bit[{i,j}];
			}
		}
		return res;
	}
};

int main(){
	vector<int> P(M+1), N(M+1), F(M+1), G(M+1);
	for(int i = 1; i <= M; ++i){
		P[i] = P[i-1] + (mu[i] == 1);
		N[i] = N[i-1] + (mu[i] == -1);
		F[i] = 100*P[i] - 99*N[i];
		G[i] = 100*N[i] - 99*P[i];
	}
	for(int i = 0; i <= M; ++i){
		F[i] += 2000;
		G[i] += 2000;
		assert(F[i] > 0 && G[i] > 0 && F[i] < 1e7 && G[i] < 1e7);
	}
	lli ans = 0;
	FenwickTree2D ft(1e7, 1e7);
	for(int i = 0; i <= M; ++i){
		ans += ft.query(F[i], G[i]);
		ft.update(F[i], G[i], 1);
	}
	/*
	Count number of pairs (a,b) such that 1<=a<=b<=n and:
	 99N(a,b) <= 100P(a,b)
	 99P(a,b) <= 100N(a,b)
	It's the same as number of pairs (a,b) such that 0<=a<b<=M and:
	 F[a] <= F[b]
	 G[a] <= G[b]
	for(int a = 0; a < M; ++a){
		for(int b = a+1; b <= M; ++b){
			if(F[b] >= F[a] && G[b] >= G[a]){
				ans++;
			}
		}
	}*/
	cout << ans << "\n";
	return 0;
}