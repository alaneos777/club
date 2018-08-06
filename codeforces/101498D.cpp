#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<lli> factorial;
vector<lli> inversos;
lli m = 1000000007;

lli inv(lli a, lli n){
	lli q, r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1 != 0){
		q = r0 / r1;
		ri = r0 % r1, r0 = r1, r1 = ri;
		si = s0 - s1 * q, s0 = s1, s1 = si;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

void calcular(lli n){
	factorial.resize(n + 1);
	inversos.resize(n + 1);
	factorial[0] = inversos[0] = 1;
	for(lli i = 1; i <= n; i++){
		factorial[i] = (factorial[i - 1] * i) % m;
		inversos[i] = inv(factorial[i], m);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	calcular(100000);
	int t;
	lli a, b;
	cin >> t;
	while(t--){
		cin >> a >> b;
		lli ans = (((2 * factorial[a - 1]) % m) * ((inversos[b] * inversos[a - 1 - b]) % m)) % m;
		cout << ans << "\n";
	}
	return 0;
}