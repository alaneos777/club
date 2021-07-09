#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli f(lli a, lli b, lli c, lli n){
	lli m = (a*n + b)/c;
	if(n==0 || m==0) return b/c;
	if(n==1) return b/c + (a+b)/c;
	if(a<c && b<c) return m*n - f(c, c-b-1, a, m-1);
	else return (a/c)*n*(n+1)/2 + (b/c)*(n+1) + f(a%c, b%c, c, n);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n, m, a, b;
		cin >> n >> m >> a >> b;
		cout << f(a, b, m, n-1) << "\n";
	}
	return 0;
}