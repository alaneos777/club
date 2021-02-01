#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

ld f(lli n, ld p){
	ld ans = (n+1 - n*p / (1-p)) / (2*n + 1);
	return ans;
}

int main(){
	lli n = 1e11;
	ld p = 0.4999l;
	cout << fixed << setprecision(10) << f(n, p) << "\n";
	return 0;
}