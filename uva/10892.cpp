#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

ull ans(ull n){
	ull pares = 1;
	for(ull i = 2; i <= sqrt(n); i++){
		if(n % i == 0){
			ull pot = 0;
			while(n % i == 0){
				pot++;
				n /= i;
			}
			pares *= 2 * pot + 1;
		}
	}
	if(n > 1) pares *= 3;
	return (pares + 1) / 2;
}

int main(){
	ull n;
	while(true){
		cin >> n;
		if(n == 0) break;
		cout << n << " " << ans(n) << "\n";
	}
	return 0;
}