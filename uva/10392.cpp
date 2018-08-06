#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

void factorizar(ull n){
	for(ull i = 2; i <= sqrt(n); ++i){
		while(n % i == 0){
			cout << "    " << i << "\n";
			n /= i;
		}
	}
	if(n > 1) cout << "    " << n << "\n";
}

int main(){
	ios_base::sync_with_stdio(0);
	ull n;
	while(true){
		cin >> n;
		if(n < 0) break;
		factorizar(n);
		cout << "\n";
	}
	return 0;
}