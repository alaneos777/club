#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;

int main(){
	ull r0, r1, ri, ans = 0;
	cin >> r0 >> r1;
	while(r1 != 0){
		ans += r0 / r1;
		ri = r0 % r1;
		r0 = r1;
		r1 = ri;
	}
	cout << ans;
	return 0;
}