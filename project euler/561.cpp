#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const lli m = 904961;
const lli n = 1e12;

int main(){
	lli ans1 = 0, ans2 = 0;
	for(int b = 1; b <= 60; ++b){
		ans1 += b * (((n+1) >> (b+2)) - ((n+1) >> (b+3)));
		ans2 += b * ((n >> (b+2)) - (n >> (b+3)));
	}
	ans1 += (n+1)/4;
	ans2 += n/4;
	cout << ans1*m+ans2 << "\n";
	return 0;
}