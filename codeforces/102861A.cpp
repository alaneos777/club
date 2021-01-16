#include <bits/stdc++.h>
using namespace std;
using ld = double;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int N, a, b;
	cin >> N >> a >> b;
	vector<ld> mem_f(N+1), mem_g(N+1);
	vector<bool> calc_f(N+1), calc_g(N+1);

	function<ld(int)> f, g;

	f = [&](int n){
		if(n == 0) return ld(0);
		ld & ans = mem_f[n];
		if(calc_f[n]) return ans;
		calc_f[n] = true;
		ans = 1 + (g(n - max(1, a)) - g(n - b - 1)) / ld(b-a+1);
		if(a == 0) ans *= ld(b+1) / b;
		return ans;
	};

	g = [&](int n){
		if(n < 0) return ld(0);
		if(n >= N-1) n = N-1;
		ld & ans = mem_g[n];
		if(calc_g[n]) return ans;
		calc_g[n] = true;
		ans = f(n) + g(n-1);
		return ans;
	};

	cout << fixed << setprecision(10) << f(N) << "\n";
	return 0;
}