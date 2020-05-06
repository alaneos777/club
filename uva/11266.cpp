#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 2e5 + 3;

map<int, int> mult(const map<int, int> & a, const map<int, int> & b){
	map<int, int> c;
	for(const auto & p1 : a){
		for(const auto & p2 : b){
			c[p1.first + p2.first] += (lli)p1.second * p2.second % mod;
			if(c[p1.first + p2.first] >= mod) c[p1.first + p2.first] -= mod;
		}
	}
	return c;
}

const int M = 2e5;
vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);

lli ncr(int n, int k){
	if(k < 0 || k > n) return 0;
	return (lli)fact[n] * invfact[k] % mod * invfact[n-k] % mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(lli i = 2; i <= M; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	int t;
	cin >> t;
	while(t--){
		int n, s;
		cin >> n >> s;
		int off = 0;
		map<int, int> num = {{0, 1}};
		for(int i = 0; i < n; ++i){
			int li, ri;
			cin >> li >> ri;
			if(li < 0){
				off -= li;
				ri -= li;
				li = 0;
			}
			// [x^(li) - x^(ri+1)] / (1 - x)
			num = mult(num, {{li, 1}, {ri+1, mod-1}});
		}
		s += off;
		int ans = 0;
		for(const auto & p : num){
			ans += (lli)p.second * ncr(s - p.first + n-1, n-1) % mod;
			if(ans >= mod) ans -= mod;
		}
		cout << ans << "\n";
	}
	return 0;
}