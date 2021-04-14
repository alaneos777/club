#include <bits/stdc++.h>
using namespace std;

int power(int a, int b, int m){
	a %= m;
	if(a == 0) return 0;
	int ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	int a, b, c;
	cin >> a >> b >> c;
	int x2 = power(a, power(b, c, 1), 2);
	int x5 = power(a, power(b, c, 4), 5);
	int d = (5*x2 + 6*x5) % 10;
	cout << d << "\n";
	return 0;
}