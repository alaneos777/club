#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const int B = 60, W = 40;
lli mem[B+1][W+1][B+1][W+1];

lli dp(int m_a, int m_b, int n_a, int n_b){
	if(m_a == 0 && m_b == 0 && n_a == 0 && n_b == 0) return 1;
	if(n_a == 0 && n_b == 0) return 1;
	if(m_a == 0 && m_b == 0) return 0;
	lli& ans = mem[m_a][m_b][n_a][n_b];
	if(ans != -1) return ans;
	ans = 0;
	for(int i = 0; i <= n_a; ++i){
		for(int j = 0; j <= n_b; ++j){
			if((m_a-i)*logl(2) + (m_b-j)*logl(3) >= 0){
				ans += dp(i, j, n_a - i, n_b - j);
			}
		}
	}
	return ans;
}

int main(){
	memset(mem, -1, sizeof(mem));
	cout << dp(B, W, B, W) << "\n";
	return 0;
}