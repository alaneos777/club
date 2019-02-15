#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 998244353;
const lli g = 3;

vector<lli> rec(const vector<lli> & P, int deg, lli n, lli m){
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli b = 1;
	for(lli v = n; v >>= 1; b <<= 1);
	do{
		int d = (n & b) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				R[i + j + d] += ans[i] * ans[j] % m;
		for(int i = 0; i < 2*deg; ++i) R[i] %= m;
		for(int i = deg-1; i >= 0; i--){
			R[i + deg] %= m;
			for(int j = 0; j < deg; j++)
				R[i + j] += R[i + deg] * P[j] % m;
		}
		for(int i = 0; i < deg; i++) R[i] %= m;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(b >>= 1);
	return ans;
}

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	a %= m;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

lli discLog(lli a, lli b, lli m){
	lli order = m-1;
	lli n = sqrt(order) + 1;
	lli a_n = powerMod(a, n, m);
	lli ans = 0;
	unordered_map<lli, lli> firstHalf;
	lli current = a_n;
	for(lli p = 1; p <= n; p++){
		firstHalf[current] = p;
		current = (current * a_n) % m;
	}
	current = b % m;
	for(lli q = 0; q <= n; q++){
		if(firstHalf.count(current)){
			lli p = firstHalf[current];
			lli x = n * p - q;
			return x % order;
		}
		current = (current * a) % m;
	}
	assert(true);
}

lli gcd(lli a, lli b, lli & x, lli & y){
	if(b == 0){
		x = 1, y = 0;
		return a;
	}else{
		lli x0, y0;
		lli d = gcd(b, a % b, x0, y0);
		x = y0, y = x0 - y0 * (a / b);
		return d;
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int k, n;
	lli m;
	cin >> k;
	vector<lli> b(k);
	for(lli & bi : b){
		cin >> bi;
	}
	cin >> n >> m;
	reverse(b.begin(), b.end());
	lli a = rec(b, k, n-1, mod-1)[k-1];

	lli rn = discLog(g, m, mod);
	lli x0, y0;
	lli d = gcd(a, mod-1, x0, y0);
	if(rn % d != 0){
		cout << "-1\n";
	}else{
		lli rk = x0 * (rn / d) % (mod-1);
		if(rk < 0) rk += mod-1;
		lli ans = powerMod(g, rk, mod);
		cout << ans << "\n";
	}
	return 0;
}