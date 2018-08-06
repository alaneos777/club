#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<int> Mu;
void muSieve(int n){
	Mu.resize(n + 1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(Mu[i]){
			for(int j = 2*i; j <= n; j += i){
				Mu[j] -= Mu[i];
			}
		}
	}
}

lli S(lli b, lli d, lli k){
	if(k == 0 || b < 1 || d < 1) return 0;
	lli ans = 0;
	for(lli D = 1; D <= b || D <= d; ++D){
		lli p1 = b / (k * D), p2 = d / (k * D);
		if(p1 == 0 || p2 == 0) break;
		ans += Mu[D] * p1 * p2;
	}
	return ans;
}

int main(){
	//ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	muSieve(1e5 + 10);
	int t;
	cin >> t;
	for(int i = 1; i <= t; ++i){
		lli a, b, c, d, k;
		cin >> a >> b >> c >> d >> k;
		if(b > d) swap(b, d);
		lli ans = (2 * S(b, d, k) - S(b, b, k) + (k <= b)) / 2;
		cout << "Case " << i << ": " << ans << "\n";
	}
	return 0;
}