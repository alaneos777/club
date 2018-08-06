#include <bits/stdc++.h>

using namespace std;

typedef long long int ull;

bool IsPerfectSquare(ull n){
	double raiz = sqrt(n);
	return abs(raiz - floor(raiz)) < 1e-8;
}

int main(){
	ull n, b = 1, actual, init;
	cin >> n;
	init = 8*n + 1;
	do{
		actual = init - 4 * b * (b + 1);
		b++;
	}while(actual >= 2 && !IsPerfectSquare(actual));
	if(actual >= 2){
		cout << "YES";
	}else{
		cout << "NO";
	}
	return 0;
}