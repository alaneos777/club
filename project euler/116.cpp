#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli mem[51][5][5];

lli f(int n, int rem, int p){
	if(n == p-1) return 1;
	if(mem[n][rem][p] != -1) return mem[n][rem][p];
	if(rem == 0){
		return mem[n][rem][p] = f(n-1, 0, p) + f(n-1, p-1, p);
	}else{
		return mem[n][rem][p] = f(n-1, rem-1, p);
	}
}

int main(){
	memset(mem, -1, sizeof(mem));
	int n = 50;
	cout << f(n, 0, 2)-1 + f(n, 0, 3)-1 + f(n, 0, 4)-1 << "\n";
	return 0;
}