#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

int main(){
	ull a, b;
	cin >> a >> b;
	if(a < b){
		cout << "0";
	}else if(a == b){
		cout << "infinity";
	}else{
		ull d = a - b;
		ull limit = sqrt(d);
		ull ans = 0;
		for(ull i = 1; i <= limit; i++){
			if(d % i == 0){
				if(i > b) ans ++;
				if(d / i != i && d / i > b) ans++;
			}
		}
		cout << ans;
	}
	return 0;
}