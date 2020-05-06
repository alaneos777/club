#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli mem[51][5];

lli f(int n, int cnt){
	if(n == 0) return cnt == 0 || cnt == 3;
	if(mem[n][cnt] != -1) return mem[n][cnt];
	if(cnt == 0 || cnt == 3){
		return mem[n][cnt] = f(n-1, 0) + f(n-1, min(3, cnt+1));
	}else{
		return mem[n][cnt] = f(n-1, min(3, cnt+1));
	}
}

int main(){
	memset(mem, -1, sizeof(mem));
	int n = 50;
	cout << f(n, 0) << "\n";
	return 0;
}