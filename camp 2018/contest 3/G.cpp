#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<vector<lli>> ncr;
lli m = 998244353;

lli Pow(lli a, lli b, lli mod){
	lli ans = 1;
	a %= mod;
	while(b){
		if(b & 1) ans = (ans * a) % mod;
		b >>= 1;
		a = (a * a) % mod;
	}
	return ans;
}

void pascal(int n){
	ncr.push_back({1});
	for(int i = 1; i <= n; i++){
		ncr.push_back(vector<lli>(i + 1));
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j <= i / 2; j++){
			ncr[i][j] = ncr[i][i - j] = (ncr[i - 1][j - 1] + ncr[i - 1][j]) % m;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	pascal(300);
	vector<lli> f(301);
	f[0] = f[1] = 1;
	for(int n = 2; n <= 300; n++){
		lli tmp = Pow(2, n * (n - 1) / 2, m);
		lli sum = 0;
		for(int k = 1; k < n; k++){
			sum = (sum + ncr[n][k] * k % m * Pow(2, (n - k) * (n - k - 1) / 2, m) % m * f[k]) % m;
		}
		sum = sum * Pow(n, m - 2, m) % m;
		tmp = (tmp - sum) % m;
		if(tmp < 0) tmp += m;
		f[n] = tmp;
	}
	int n;
	while(cin >> n){
		cout << f[n] << "\n";
	}
	return 0;
}