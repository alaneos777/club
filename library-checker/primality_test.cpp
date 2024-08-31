#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

lli powerMod(lli a, lli b, lli m){
    lli ans = 1;
    a %= m;
    while(b){
        if(b & 1) ans = ans * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return ans;
}

bool isPrimeMillerRabin(lli n){
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

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int q;
    cin >> q;
    while(q--){
        int64_t n;
        cin >> n;
        cout << (isPrimeMillerRabin(n) ? "Yes" : "No") << "\n";
    }
    return 0;
}