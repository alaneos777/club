#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int p, q;
	cin >> p >> q;
	int d = __gcd(p, q);
	lli num = p/d, den = q/d;
	lli a1 = num/den;
	cout << (int64_t)a1 << " ";
	num %= den;
	lli fact = 1, i = 2;
	while(num){
		fact = fact * (i++);
		lli g = __gcd(fact, den);
		fact /= g, den /= g;
		lli ak = num * fact / den;
		cout << (int64_t)ak << " ";
		lli next_num = num*fact - den*ak;
		lli next_den = den*fact;
		g = __gcd(next_num, next_den);
		num = next_num/g, den = next_den/g;
		//x = num/den - ak/fact
	}
	cout << "\n";
	return 0;
}