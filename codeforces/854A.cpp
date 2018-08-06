#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	if(n & 1){
		cout << (n + 1) / 2 - 1 << " " << (n + 1) / 2 << "\n";
	}else{
		int a = n / 2, b = a;
		while(__gcd(a, b) != 1) a--, b++;
		cout << a << " " << b << "\n";
	}
	return 0;
}