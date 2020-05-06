#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int m = 50;

lli mem[10000][m+1];

lli f(int n, int cnt){
	if(n == 0) return cnt == 0 || cnt == m;
	if(mem[n][cnt] != -1) return mem[n][cnt];
	if(cnt == 0 || cnt == m){
		return mem[n][cnt] = f(n-1, 0) + f(n-1, min(m, cnt+1));
	}else{
		return mem[n][cnt] = f(n-1, min(m, cnt+1));
	}
}

int main(){
	memset(mem, -1, sizeof(mem));
	for(int n = 1; ; ++n){
		if(f(n, 0) > 1e6){
			cout << n << "\n";
			break;
		}
	}
	return 0;
}