#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 100;

lli mem[2][M+1][11];

lli inc(int pos, int last){
	if(pos == M) return 1;
	lli &ans = mem[0][pos][last];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = last; d <= 9; ++d){
		ans += inc(pos+1, d);
	}
	return ans;
}

lli dec(int pos, int last){
	if(pos == M) return 1;
	lli &ans = mem[1][pos][last+1];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= (last == -1 ? 9 : last); ++d){
		ans += dec(pos+1, d == 0 && last == -1 ? -1 : d);
	}
	return ans;
}

int main(){
	memset(mem, -1, sizeof(mem));
	cout << inc(0, 0) + dec(0, -1) - 9*M - 2 << "\n";
	return 0;
}