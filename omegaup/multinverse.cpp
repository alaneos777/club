#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(r0 != 1) return -1;
	if(s0 < 0) s0 += m;
	return s0;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	lli a, n;
	cin >> a >> n;
	cout << inv(a, n) << "\n";
	return 0;
}