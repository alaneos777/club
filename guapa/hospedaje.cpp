#include <bits/stdc++.h>
using namespace std;

int mod = 986444689;
const int M = 1e5;
vector<int> primes = {0, 2, 5, 7, 11, 17};
int mem[6][M+10];

int dp(int prev, int m){
	if(m < 0) return 0;
	if(m == 0) return 1;
	int &ans = mem[prev][m];
	if(ans != -1) return ans;
	ans = 0;
	for(int i = 1; i < primes.size(); ++i){
		if(prev != i){
			ans += dp(i, m - primes[i]);
			if(ans >= mod) ans -= mod;
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	memset(mem, -1, sizeof(mem));
	while(t--){
		int n;
		cin >> n;
		cout << dp(0, n) << "\n";
	}
	return 0;
}