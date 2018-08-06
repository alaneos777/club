#include <iostream>
#include <vector>
using namespace std;
typedef long long int lli;

lli mod = 1e9 + 7;

vector<lli> P;
vector<lli> sums, prods;

lli inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1= si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	return s0;
}

lli partitionsP(int n){
	int pos1 = 1, pos2 = 2, inc1 = 4, inc2 = 5;
	lli ans = 0;
	for(int k = 1; k <= n; k++){
		lli tmp = (n >= pos1 ? P[n - pos1] : 0) + (n >= pos2 ? P[n - pos2] : 0);
		if(k & 1){
			ans += tmp;
		}else{
			ans -= tmp;
		}
		if(n < pos2) break;
		pos1 += inc1, pos2 += inc2;
		inc1 += 3, inc2 += 3;
	}
	ans %= mod;
	if(ans < 0) ans += mod;
	return ans;
}

void calculateFunctionP(int n){
	P.resize(n + 1);
	P[0] = 1;
	for(int i = 1; i <= n; i++){
		P[i] = partitionsP(i);
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, q, l, r;
	lli res;
	cin >> n >> q;
	calculateFunctionP(n);
	sums.resize(n + 1);
	prods.resize(n + 1, 1);
	for(int i = 1; i <= n; ++i){
		sums[i] = (sums[i - 1] + P[i]) % mod;
		prods[i] = prods[i - 1] * P[i] % mod;
	}
	while(q--){
		cin >> l >> r;
		res = (sums[r] - sums[l - 1]) * prods[r] % mod * inv(prods[l - 1], mod) % mod;
		if(res < 0) res += mod;
		cout << res << "\n";
	}
	return 0;
}