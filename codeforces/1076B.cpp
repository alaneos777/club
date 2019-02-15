#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli smallest(lli n){
	if(n == 1) return 1;
	for(lli d = 2; d*d <= n; ++d){
		if(n % d == 0) return d;
	}
	return n;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n;
	cin >> n;
	if(n & 1){
		cout << 1 + (n - smallest(n)) / 2 << "\n";
	}else{
		cout << n/2 << "\n";
	}
	return 0;
}