#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli g = 5;
const lli mod = 1e9 + 7;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

lli discLog(lli a, lli b, lli m){
	lli order = m - 1;
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
	assert(0);
	return -1;
}

lli rec(const vector<lli> & P, const vector<lli> & init, lli n){
	int deg = P.size();
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				R[i + j + d] += ans[i] * ans[j] % (mod-1);
		for(int i = 0; i < 2*deg; ++i) R[i] %= (mod-1);
		for(int i = deg-1; i >= 0; i--){
			R[i + deg] %= (mod-1);
			for(int j = 0; j < deg; j++)
				R[i + j] += R[i + deg] * P[j] % (mod-1);
		}
		for(int i = 0; i < deg; i++) R[i] %= (mod-1);
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		nValue += ans[i] * init[i] % (mod-1);
	return nValue % (mod-1);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, f1, f2, f3, c;
	cin >> n >> f1 >> f2 >> f3 >> c;
	--n;
	lli d = discLog(g, c, mod);
	lli ans = rec({1, 1, 1}, {(discLog(g, f1, mod) + d) % (mod-1), (discLog(g, f2, mod) + 2*d) % (mod-1), (discLog(g, f3, mod) + 3*d) % (mod-1)}, n);
	ans -= d * ((n+1) % (mod - 1)) % (mod - 1);
	if(ans < 0) ans += mod-1;
	cout << powerMod(g, ans, mod) << "\n";
	return 0;
}