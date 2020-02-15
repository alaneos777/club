#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

bool isPrime(lli n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		lli m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) continue;
		int k = 0;
		for(; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}

lli findPrime(lli l, lli r, int dir){
	if(dir == -1){
		swap(l, r);
		l = -l, r = -r;
	}
	for(lli p = l; p <= r; p++){
		if(isPrime(abs(p))) return abs(p);
	}
	return -1;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<lli> a(n);
	lli sum = 0;
	for(lli & ai : a){
		cin >> ai;
		sum += ai;
	}
	sort(a.begin(), a.end());
	lli ans = 1e18;
	int k = -n;
	for(int i = 0; i <= n; ++i){
		lli p = findPrime(i > 0 ? a[i-1] : 1, i < n ? a[i] : 1e18, k>=0 ? 1 : -1);
		if(p != -1){
			ans = min(ans, sum + k*p);
		}
		if(i < n){
			sum -= 2*a[i];
			k += 2;
		}
	}
	cout << ans << "\n";
	return 0;
}