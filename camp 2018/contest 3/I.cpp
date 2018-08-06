#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<vector<lli>> ncr;
lli m = 1e9 + 7;

void pascal(int n){
	ncr.push_back({1});
	for(int i = 1; i <= n; i++){
		ncr.push_back(vector<lli>(i + 1));
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j <= i / 2; j++){
			ncr[i][j] = ncr[i][i - j] = (ncr[i - 1][j - 1] + ncr[i - 1][j]) % m;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	pascal(3000);
	int n;
	cin >> n;
	vector<int> powers(n + 1);
	int q = 0;
	for(int i = 1; i <= n; i++){
		cin >> powers[i];
		q += powers[i];
	}
	vector<lli> prod(q + 3);
	for(int i = 0; i <= q; i++){
		lli tmp = 1;
		for(int j = 1; j <= n; j++){
			tmp = (tmp * ncr[powers[j] + i][powers[j]]) % m;
		}
		prod[i] = tmp;
	}
	lli ans = 0;
	for(int j = 1; j <= q; j++){
		int alt = 1;
		for(int i = 0; i < j; i++){
			ans = (ans + alt * ncr[j][i] * prod[j - i - 1] % m) % m;
			alt *= -1;
		}
	}
	if(ans < 0) ans += m;
	cout << ans;
	return 0;
}