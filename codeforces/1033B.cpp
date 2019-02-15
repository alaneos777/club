#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool isPrime(lli n){
	if(n == 1) return false;
	for(lli d = 2; d*d <= n; ++d){
		if(n % d == 0) return false;
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli a, b;
		cin >> a >> b;
		if(a-b != 1){
			cout << "NO\n";
		}else{
			if(isPrime(a + b)){
				cout << "YES\n";
			}else{
				cout << "NO\n";
			}
		}
	}
	return 0;
}