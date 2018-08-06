#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int M;
const int MAXI = 7e7 + 10;
int Mu[MAXI], pre_G[MAXI], pre_T[MAXI], cnt[MAXI];
bool isPrime[MAXI];
vector<int> primes;

void sieve(int n){
	Mu[0] = 0, Mu[1] = 1;
	pre_T[0] = 0, pre_T[1] = 1;
	fill(begin(isPrime), end(isPrime), true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){
			primes.push_back(i);
			Mu[i] = -1;
			pre_T[i] = 2;
			cnt[i] = 2;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0){
				pre_T[d] = pre_T[i] / cnt[i] * (cnt[i] + 1);
				cnt[d] = cnt[i] + 1;
				break;
			}else{
				Mu[d] = -Mu[i];
				pre_T[d] = pre_T[i] * 2;
				cnt[d] = 2;
			}
		}
	}
}

map<lli, lli> PRE_G, PRE_T;

lli G(lli n){
	if(n <= M) return pre_G[n];
	if(PRE_G.find(n) != PRE_G.end()) return PRE_G[n];
	int m = sqrt(n);
	lli ans = 0;
	for(int k = 1; k <= m; ++k){
		ans += Mu[k] * (n / k / k);
	}
	return PRE_G[n] = ans;
}

lli T(lli n){
	if(n <= M) return pre_T[n];
	if(PRE_T.find(n) != PRE_T.end()) return PRE_T[n];
	int m = sqrt(n);
	lli ans = 0;
	for(int k = 1; k <= m; ++k){
		ans += n / k;
	}
	return PRE_T[n] = 2 * ans - (lli)m * m;
}

lli S(lli n){
	int m = sqrt(n);
	lli ans = 0;
	lli k = 1;
	for(int k = 1, l = n/m; k <= l; ++k){
		ans += Mu[k] * Mu[k] * T(n / k);
	}
	for(int k = 1; k < m; ++k){
		ans += (G(n / k) - G(n / (k + 1))) * T(k);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	vector<lli> queries(t);
	lli m = 0;
	for(int i = 0; i < t; ++i){
		cin >> queries[i];
		m = max(m, queries[i]);
	}
	//clock_t start = clock();
	M = pow(m / 2.0, 2.0 / 3.0);
	sieve(M);
	for(int k = 1; k <= M; ++k){
		pre_G[k] = pre_G[k - 1] + Mu[k] * Mu[k];
		pre_T[k] += pre_T[k - 1];
	}
	for(int i = 0; i < t; ++i){
		cout << S(queries[i]) << "\n";
	}
	//cout << fixed << setprecision(4) << (clock() - start) / (double)CLOCKS_PER_SEC << "s\n";
	return 0;
}