#include <bits/stdc++.h>
using namespace std;
using ld = long double;

ld raiz(ld a, int k){
	ld x = 1;
	for(int i = 1; i <= 20; ++i){
		x = ((k-1) * powl(x, k) + a) / (k*powl(x, k-1));
		cout << fixed << setprecision(15) << x << "\n";
	}
	return x;
}

ld inverso(ld a){
	ld x = 0.001l;
	for(int i = 1; i <= 20; ++i){
		x = 2*x - x*x*a;
		cout << fixed << setprecision(15) << x << "\n";
	}
	return x;
}

int main(){
	ld a;
	cin >> a;
	cout << fixed << setprecision(15) << inverso(a) << "\n";
	return 0;
}