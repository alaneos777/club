#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool isPrime(int n){
	for(int d = 2; d*d <= n; ++d){
		if(n % d == 0) return false;
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		lli p = n;
		while(!isPrime(p)){
			p--;
		}
		lli q = n+1;
		while(!isPrime(q)){
			q++;
		}
		lli num = 2*(n-1) + (p-2)*(q-2);
		lli den = 2*p*q;
		lli d = __gcd(num, den);
		num /= d;
		den /= d;
		cout << num << "/" << den << "\n";
	}
	return 0;
}