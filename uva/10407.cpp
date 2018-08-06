#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

int main(){
	ull ans, n;
	while(true){
		cin >> n;
		if(n == 0) break;
		vector<ull> numeros;
		numeros.push_back(n);
		while(true){
			cin >> n;
			if(n == 0) break;
			numeros.push_back(n);
		}
		ans = 0;
		for(size_t i = 0; i < numeros.size(); i++){
			ans = __gcd(ans, abs(numeros[i] - numeros[(i + 1) % numeros.size()]));
		}
		cout << ans << "\n";
	}
	return 0;
}