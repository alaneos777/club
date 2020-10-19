#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;

auto getFact(int n){
	vector<pair<int, int>> f;
	for(int p = 2; p*p <= n; ++p){
		int pot = 0;
		while(n % p == 0){
			++pot;
			n /= p;
		}
		if(pot) f.emplace_back(p, pot);
	}
	if(n > 1) f.emplace_back(n, 1);
	return f;
}

lli P1(lli n){
	n %= mod;
	return n * (n +1) % mod * inv2 % mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	auto f = getFact(k);
	int ans = 0;
	function<void(int, int, int)> dfs = [&](int pos, int divi, int func){
		if(pos == f.size()){
			ans += (lli)func * P1(n / divi) % mod;
			if(ans >= mod) ans -= mod;
			if(ans < 0) ans += mod;
		}else{
			int p, a;
			tie(p, a) = f[pos];
			int p_pow = 1;
			for(int i = 0; i <= a; ++i){
				dfs(pos + 1, divi * p_pow, i ? func * (1 - p) : func);
				p_pow *= p;
			}
		}
	};
	dfs(0, 1, 1);
	ans = (lli)ans * k % mod;
	cout << ans << "\n";
	return 0;
}