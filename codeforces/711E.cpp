#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e6 + 3;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, k;
	cin >> n >> k;
	if(n < log2l(k)){
		cout << "1 1\n";
		return 0;
	}
	lli p2 = 0, pow_2 = 2;
	for(lli i = 1; i <= n; ++i){
		if(k >= pow_2){
			p2 += (k + pow_2 - 1) / pow_2;
			pow_2 *= 2;
		}else{
			p2 += n - i + 1;
			break;
		}
	}
	lli p_den = (n % (mod-1)) * (k % (mod-1)) % (mod-1) - p2 % (mod-1);
	if(p_den < 0) p_den += mod-1;
	lli den = power(2, p_den);
	lli num = 0;
	//product from 2^n-(k-1) to 2^n , length=k
	if(k < mod){
		lli p_num = p2 % (mod-1);
		p_num = (mod-1 - p_num) % (mod-1);
		num = power(2, p_num);
		lli c = power(2, n);
		for(lli i = 0; i <= k-1; ++i){
			num = num * (c - i) % mod;
			if(num < 0) num += mod;
		}
	}
	num = den - num;
	if(num < 0) num += mod;
	cout << num << " " << den << "\n";
	return 0;
}