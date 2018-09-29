#include <iostream>
using namespace std;
typedef long long int lli;
lli mod = 1e9+7;

lli inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

const lli inv_2 = inv(2, mod), inv_3 = inv(3, mod);

inline void modula(lli & n){
	if(n < 0) n += mod;
	if(n >= mod) n -= mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	if(n < 3) cout << "0\n";
	else{
		lli sum = 0, squares = 0, cubes = 0;
		lli ai;
		for(int i = 0; i < n; ++i){
			cin >> ai;
			sum += ai;
			squares += ai*ai;
			cubes += ai*ai*ai;
			modula(sum), modula(squares), modula(cubes);
		}
		lli duos = (sum*sum%mod - squares) * inv_2 % mod;
		lli trios = (cubes - sum*sum%mod*sum%mod + 3*sum*duos%mod) * inv_3 % mod;
		modula(trios);
		cout << trios << "\n";
	}
	return 0;
}