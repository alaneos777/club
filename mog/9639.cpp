#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const int MX = 5e3 + 2;
const lli mod = 1e9 + 7;

lli mem_f[MX][MX];
lli mem_g[MX][MX];

lli f(int b, int s);
lli g(int b, int s);

lli f(int b, int s){
	if(b == 0) return 1;
	if(b < 0 || s < 0) return 0;
	if(mem_f[b][s] != -1) return mem_f[b][s];
	lli ans = f(b, s-1) + g(b, s);
	if(ans >= mod) ans -= mod;
	return mem_f[b][s] = ans;
}

lli g(int b, int s){
	if(b < 0 || s <= 0) return 0;
	if(mem_g[b][s] != -1) return mem_g[b][s];
	lli ans = g(b, s-1) + f(b-s, s);
	if(ans >= mod) ans -= mod;
	return mem_g[b][s] = ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	memset(mem_f, -1, sizeof(mem_f));
	memset(mem_g, -1, sizeof(mem_g));
	int s, b;
	cin >> s >> b;
	cout << f(b-s, s) << "\n";
	return 0;
}