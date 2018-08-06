#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

ull LPD(ull n){
	ull ans = -1;
	ull primeFactors = 0;
	for(ull i = 2; i <= sqrt(n); ++i){
		if(n % i == 0){
			while(n % i == 0){
				n /= i;
			}
			ans = i;
			++primeFactors;
		}
	}
	if(n > 1){
		++primeFactors;
		ans = n;
	}
	if(primeFactors == 1){
		return -1;
	}else{
		return ans;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	ull n;
	while(true){
		cin >> n;
		if(n == 0) break;
		cout << LPD(abs(n)) << "\n";
	}
	return 0;
}