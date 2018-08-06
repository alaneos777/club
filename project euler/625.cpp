#include <bits/stdc++.h>
using namespace std;
typedef __int128 lli;

vector<lli> phi;
void criba(int n){
	phi.resize(n + 1);
	for(int i = 1; i <= n; i++) phi[i] = (i & 1 ? i : i / 2);
	for(int i = 3; i <= n; i += 2){
		if(phi[i] == i){
			for(int j = i; j <= n; j += i){
				phi[j] -= phi[j] / i;
			}
		}
	}
}

lli n = 1e11;
lli mod = 998244353;

lli sum_1(lli n){
	return n * (n + 1) / 2;
}

vector<lli> Tsmall;
unordered_map<lli, lli> Tbig;

lli T(lli n){
	if(n < Tsmall.size()){
		return Tsmall[n];
	}else{
		if(Tbig.count(n) == 0){
			lli m = sqrt(n), q2 = n / m;
			lli ans = sum_1(n);
			for(lli k = 2; k <= q2; k++){
				ans -= T(n / k);
			}
			for(lli k = 1; k < m; k++){
				ans -= (n / k - n / (k + 1)) * T(k);
			}
			ans %= mod;
			if(ans < 0) ans += mod;
			Tbig[n] = ans;
		}
		return Tbig[n];
	}
}

lli S(lli n){
	lli ans = 0;
	lli m = sqrt(n), q2 = n / m;
	for(lli k = 1; k <= q2; k++){
		ans += sum_1(n / k) * phi[k];
	}
	for(lli k = 1; k < m; k++){
		ans += (T(n / k) - T(n / (k + 1))) * sum_1(k);
	}
	ans %= mod;
	if(ans < 0) ans += mod;
	return ans;
}

int main(){
	clock_t begin = clock();
	int limit = pow(n, 2.0 / 3.0);
	criba(limit);
	Tsmall.resize(limit + 1);
	for(int i = 1; i <= limit; i++){
		Tsmall[i] = (Tsmall[i - 1] + phi[i]) % mod;
	}
	long long int ans = S(n);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << ans << "\n";
	cout << fixed << setprecision(4) << elapsed_secs << "s\n";
	return 0;
}