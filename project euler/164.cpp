#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 20;

lli mem[M][10][10][10];

lli f(int idx, int a, int b, int c){
	if(idx == -1){
		return 1;
	}
	lli & ans = mem[idx][a][b][c];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		if(d == 0 && idx == M-1) continue;
		if(b+c+d <= 9) ans += f(idx-1, b, c, d);
	}
	return ans;
}

int main(){
	memset(mem, -1, sizeof(mem));
	cout << f(M-1, 0, 0, 0) << "\n";
	return 0;
}