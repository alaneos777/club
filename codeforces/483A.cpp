#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long int ull;

ull gcd(ull a, ull b){
	ull r;
	while(b != 0){
		r = a % b;
		a = b, b = r;
	}
	return a;
}

int main(){
	ull l, r;
	cin >> l >> r;
	bool exists = false;
	for(ull a = l; a <= r; a++){
		if(exists) break;
		for(ull b = a + 1; b <= r; b++){
			if(exists) break;
			for(ull c = b + 1; c <= r; c++){
				if(exists) break;
				if(gcd(a, b) == 1 && gcd(b, c) == 1 && gcd(a, c) != 1){
					cout << a << " " << b << " " << c;
					exists = true;
					break;
				}
			}
		}
	}
	if(!exists) cout << "-1";
	return 0;
}