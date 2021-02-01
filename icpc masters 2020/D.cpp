#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli powerMod(lli a, lli b, lli m){
    lli ans = 1;
    while(b){
        if(b & 1) ans = ans * a % m;
        b >>= 1;
        a = a * a % m;
    }
    return ans;
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

set<int> valid_der;
vector<int> valid;

void der(int n){
    valid_der.insert(n);
    for(int d = 1; d <= 9; ++d){
        lli nxt = stoll(to_string(d) + to_string(n));
        if(nxt <= 1e9 && isPrime(nxt)){
            der(nxt);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for(int p : {2, 3, 5, 7}){
        der(p);
    }
    for(int x : valid_der){
        string str = to_string(x);
        reverse(str.begin(), str.end());
        int y = stoi(str);
        if(valid_der.count(y)){
            valid.push_back(x);
        }
    }
    sort(valid.begin(), valid.end());
    int t;
    cin >> t;
    while(t--){
        int l, r;
        cin >> l >> r;
        int ans = upper_bound(valid.begin(), valid.end(), r) - lower_bound(valid.begin(), valid.end(), l);
        cout << ans << "\n";
    }
    return 0;
}