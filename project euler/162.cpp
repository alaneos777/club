#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli mem[20][2][2][2][2];

lli dp(int idx, bool a, bool b, bool c, bool f){
	if(idx == -1){
		return a & b & c;
	}
	lli & ans = mem[idx][a][b][c][f];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 15; ++d){
		ans += dp(idx-1, a || (f && d == 0), b || (d == 1), c || (d == 10), f || (d != 0));
	}
	return ans;
}

int main(){
	memset(mem, -1, sizeof(mem));
	cout << hex << uppercase << dp(15, false, false, false, false) << "\n";
	return 0;
}