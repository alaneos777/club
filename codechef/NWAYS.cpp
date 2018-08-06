#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int inv(int a, int n){
	int r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1 != 0){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

int main(){
	ios_base::sync_with_stdio(0);
	int m = 1000000007;
	int n_max = 1000000, k_max = 1000000;
	int maximo = n_max + k_max + 1;
	vector<int> f(maximo + 1);
	f[0] = 1;
	for(lli i = 1; i <= maximo; i++){
		f[i] = (i * f[i - 1]) % m;
	}
	int t, n, k;
	cin >> t;
	lli two = (lli)2;
	while(t--){
		cin >> n >> k;
		lli ans = (two * f[k + n + 1]) % m;
		ans = (ans * inv(f[n], m)) % m;
		ans = (ans * inv(f[k + 2], m)) % m - 1;
		ans = (ans * n) % m;
		cout << ans << "\n";
	}
	return 0;
}