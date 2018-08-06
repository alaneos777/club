#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, a, b;
	cin >> n;
	if(n<0){
		n *= -1;
		a = n % 10;
		n /= 10;
		b = n % 10;
		n /= 10;
		n = - n*10 - min(a, b);
	}
	cout << n;
	return 0;
}