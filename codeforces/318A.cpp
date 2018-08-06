#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;

int main(){
	ull n, k, m;
	cin >> n >> k;
	m = (n+1)/2;
	if(k <= m){
		cout << (2*k-1);
	}else{
		cout << 2*(k-m);
	}
	return 0;
}