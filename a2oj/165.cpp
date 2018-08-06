#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

ull mod(ull a, ull b){
	ull r = a % b;
	if(r < 0) r += b;
	return r;
}

int main(){
	int t, k;
	ull c, n, m = 1000000007;
	cin >> t;
	for(int i = 1; i <= t; i++){
		cin >> n >> k;
		switch(k){
			case 0:{
				if(n % 2 == 0){
					cout << mod(n, m) << " 0";
				}else{
					cout << mod(n, m) << " " << mod(-1, m);
				}
				break;
			}
			case 1:{
				if(n % 2 == 0){
					cout << mod((n / 2) * (n + 1), m) << " " << mod(n / 2, m);
				}else{
					cout << mod((n + 1) / 2 * n, m) << " " << mod(-((n + 1) / 2), m);
				}
				break;
			}
			case 2:{
				if(n % 2 == 0){
					cout << mod((n / 2) * mod(((n + 1) * (2 * n + 1) / 3), m), m) << " " << mod((n / 2) * (n + 1), m);
				}else{
					cout << mod((n + 1) / 2 * mod(n * (2 * n + 1) / 3, m), m) << " " << mod(-((n + 1) / 2 * n), m);
				}
				break;
			}
			case 3:{
				if(n % 2 == 0){
						c = mod((n / 2) * (n + 1), m);
						cout << mod(c * c, m) << " " << mod(mod((n / 2) * (n / 2), m) * mod((2 * n + 3), m), m);
				}else{
						c = mod((n + 1) / 2 * n, m);
						cout << mod(c * c, m) << " " << mod(-(mod(((n + 1) / 2) * ((n + 1) / 2), m) * mod(2 * n - 1, m)), m);
				}
				break;
			}
		}
		if(i != t) cout << "\n";
	}
	return 0;
}