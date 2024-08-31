#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int N = 4;

lli mem[N][N][1<<(N*N)];

lli f(int r, int c, int mask){
	lli& ans = mem[r][c][mask];
	if(ans != -1) return ans;
	int pos = r*N + c;
	ans = 1;
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			if(i == r && j == c) continue;
			int di = i-r, dj = j-c;
			if(__gcd(abs(di), abs(dj)) > 1) continue;
			for(int n_i = i, n_j = j; 0 <= n_i && n_i < N && 0 <= n_j && n_j < N; n_i += di, n_j += dj){
				int n_pos = n_i*N + n_j;
				if(mask & (1 << n_pos)) continue;
				ans += f(n_i, n_j, mask | (1 << pos));
				break;
			}
		}
	}
	return ans;
}

int main(){
	memset(mem, -1, sizeof(mem));
	lli ans = 0;
	for(int r = 0; r < N; ++r){
		for(int c = 0; c < N; ++c){
			ans += f(r, c, 0) - 1;
		}
	}
	cout << ans << "\n";
	return 0;
}