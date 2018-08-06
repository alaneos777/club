#include <bits/stdc++.h>

using namespace std;

typedef long long int ull;

ull fast_pow(ull a, ull b){
	ull ans = 1;
	while(b){
		if(b & 1){
			ans *= a;
		}
		b >>= 1;
		a *= a;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	string n;
	int i = 1;
	ull j, k, fija, repetida, num, den, d;
	while(true){
		cin >> j;
		if(j == -1) break;
		cin >> n;
		k = n.size() - 2 - j;
		if(k == 0)
			fija = 0;
		else
			stringstream(n.substr(2, k)) >> fija;
		if(j == 0)
			repetida = 0;
		else
			stringstream(n.substr(n.size() - j, j)) >> repetida;
		if(j == 0){
			num = fija;
			den = fast_pow(10, k);
		}else{
			num = fija * fast_pow(10, j) + repetida - fija;
			den = fast_pow(10, j + k) - fast_pow(10, k);
		}
		d = __gcd(num, den);
		num /= d;
		den /= d;
		cout << "Case " << i << ": " << num << "/" << den << "\n";
		i++;
	}
	return 0;
}