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

struct FenwickTree{
	int N;
	vector<int> bit;

	FenwickTree(int N): N(N), bit(N){}

	void update(int pos, int value){
		while(pos < N){
			bit[pos] += value;
			pos |= pos + 1;
		}
	}

	int query(int r){
		int res = 0;
		while(r >= 0){
			res += bit[r];
			r = (r & (r + 1)) - 1;
		}
		return res;
	}

	int query(int l, int r){
		return query(r) - query(l-1);
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
		assert(F[i] > 0 && G[i] > 0 && F[i] < M && G[i] < M);
	}
	/*
	Count number of pairs (a,b) such that 1<=a<=b<=n and:
	 99N(a,b) <= 100P(a,b)
	 99P(a,b) <= 100N(a,b)
	It's the same as number of pairs (a,b) such that 0<=a<b<=M and:
	 F[a] <= F[b]
	 G[a] <= G[b]
	}
	*/
	lli ans = (lli)M*(M+1)/2;
	FenwickTree ft1(M), ft2(M);
	for(int i = 0; i <= M; ++i){
		ans -= ft1.query(F[i]+1, M-1) + ft2.query(G[i]+1, M-1);
		ft1.update(F[i], 1), ft2.update(G[i], 1);
	}
	cout << ans << "\n";
	return 0;
}