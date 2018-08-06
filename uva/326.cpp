#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli gcd(lli a, lli b){
	lli r;
	while(b != 0){
		r = a % b, a = b, b = r;
	}
	return a;
}

struct fraccion{
	lli num, den;
	fraccion(){
		num = 0, den = 1;
	}
	fraccion(lli a, lli b){
		if(b < 0){
			a *= -1;
			b *= -1;
		}
		lli d = gcd(abs(a), b);
		num = a / d, den = b / d;
	}
	fraccion sumar(fraccion f){
		lli d = gcd(den, f.den);
		return fraccion(num * (f.den / d) + f.num * (den / d), den * (f.den / d));
	}
	fraccion multiplicar(fraccion f){
		lli d1 = gcd(abs(num), f.den), d2 = gcd(abs(f.num), den);
		return fraccion((num / d1) * (f.num / d2), (den / d2) * (f.den / d1));
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	lli n, k;
	while(true){
		cin >> n;
		if(n == 0) break;
		vector<lli> puntos(n);
		for(lli i = 0; i < n; i++){
			cin >> puntos[i];
		}
		cin >> k;
		lli x = n + k;
		fraccion ans;
		for(lli i = 1; i <= n; i++){
			fraccion tmp(puntos[i - 1], 1);
			for(lli j = 1; j <= n; j++){
				if(j != i){
					tmp = tmp.multiplicar(fraccion(x - j, i - j));
				}
			}
			ans = ans.sumar(tmp);
		}
		cout << "Term " << x << " of the sequence is " << ans.num << "\n";
	}
	return 0;
}