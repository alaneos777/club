#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n){
	if(n == 1) return false;
	for(int d = 2; d*d <= n; ++d){
		if(n % d == 0) return false;
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	if(n == 2 || n == 3) cout << "1\n";
	else if(n%2 == 0) cout << "2\n";
	else{
		if(isPrime(n)) cout << "1\n";
		else if(isPrime(n - 2)) cout << "2\n";
		else cout << "3\n";
	}
	return 0;
}