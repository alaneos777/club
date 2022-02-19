#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli piso(lli a, lli b){
	lli ans = a/b;
	if(a%b != 0 && a < 0) ans--;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli k, a, b;
	cin >> k >> a >> b;
	cout << piso(b, k) - piso(a-1, k) << "\n";
	return 0;
}