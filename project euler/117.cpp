#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli mem[51][5];

lli f(int n, int rem){
	if(n < rem) return 0;
	if(n == rem) return 1;
	if(mem[n][rem] != -1) return mem[n][rem];
	if(rem == 0){
		return mem[n][rem] = f(n-1, 0) + f(n-1, 1) + f(n-1, 2) + f(n-1, 3);
	}else{
		return mem[n][rem] = f(n-1, rem-1);
	}
}

int main(){
	memset(mem, -1, sizeof(mem));
	int n = 50;
	cout << f(n, 0) << "\n";
	return 0;
}