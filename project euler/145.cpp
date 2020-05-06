#include <bits/stdc++.h>
using namespace std;

int rev(int n){
	int m = 0;
	while(n){
		m = m * 10 + n % 10;
		n /= 10;
	}
	return m;
}

int odd(int n){
	while(n){
		if(n % 10 % 2 != 1) return false;
		n /= 10;
	}
	return true;
}

int main(){
	int cnt = 0;
	for(int n = 1; n <= int(1e9); ++n){
		if(n % 10 == 0) continue;
		int m = rev(n);
		if(odd(n + m)) cnt++;
	}
	cout << cnt << "\n";
	return 0;
}