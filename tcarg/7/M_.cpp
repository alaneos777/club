#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int conv(int n){
	int ans = 0;
	int p_pow = 1;
	while(n){
		int d = n%2;
		ans += d*p_pow;
		n /= 2;
		p_pow *= 7;
	}
	return ans;
}

int xor7(int m, int n){
	int ans = 0;
	int p_pow = 1;
	while(m > 0 || n > 0){
		int a = m%7, b = n%7;
		int c = a+b;
		if(c >= 7) c -= 7;
		ans += c*p_pow;
		p_pow *= 7;
		m /= 7, n /= 7;
	}
	return ans;
}

using poly = unordered_map<int, int>;

int cnt = 0;
poly operator*(const poly& a, const poly& b){
	poly ans;
	for(auto[i, c1] : a){
		for(auto[j, c2] : b){
			int k = xor7(i,j);
			ans[k] += (lli)c1*c2 % mod;
			cnt++;
			if(ans[k] >= mod) ans[k] -= mod;
		}
	}
	return ans;
}

poly power(poly a, lli b){
	poly ans = {{0, 1}};
	while(b){
		if(b&1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	lli k;
	cin >> n >> k;
	poly freq;
	for(int i = 0; i < n; ++i){
		int ai, ci;
		cin >> ai;
		ci = conv(ai);
		freq[ci]++;
	}
	freq = power(freq, k);
	cout << cnt << "\n";
	cout << freq[0] << "\n";
	return 0;
}