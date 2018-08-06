#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 98765431;

int n;

void multiply(lli & a1, lli & a0, lli & b1, lli & b0){
	lli c0 = (a0 * b0) % mod;
	lli c1 = ((a0 * b1) % mod + (a1 * b0) % mod) % mod;
	lli c2 = (a1 * b1) % mod;
	a1 = (c2 * (n - 2) % mod + c1) % mod;
	a0 = (c2 * (n - 1) % mod + c0) % mod;
}

void powPoly(lli & a1, lli & a0, lli pot){
	lli ans0 = 1, ans1 = 0;
	lli acum0 = a0, acum1 = a1;
	while(pot){
		if(pot & 1) multiply(ans1, ans0, acum1, acum0);
		pot >>= 1;
		multiply(acum1, acum0, acum1, acum0);
	}
	a1 = ans1, a0 = ans0;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	lli t;
	cin >> n >> t;
	vector<lli> initial(n);
	lli acum = 0;
	for(int i = 0; i < n; i++){
		cin >> initial[i];
		acum = (acum + initial[i]) % mod;
	}
	lli a1 = 1, a0 = 0;
	powPoly(a1, a0, t);
	acum = (acum * a1) % mod;
	lli current, inc = a0 - a1;
	for(int i = 0; i < n; i++){
		current = (acum + inc * initial[i]) % mod;
		if(current < 0) current += mod;
		cout << current << "\n";
	}
	return 0;
}