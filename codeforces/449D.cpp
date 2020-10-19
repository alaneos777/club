#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const int p = 1e9 + 7;

void fwt(vector<int> & A){
	int n = A.size();
	for(int k = 1; k < n; k <<= 1)
		for(int i = 0; i < n; i += k << 1)
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = A[i + j + k];
				A[i + j] = u + v;
			}
}

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

const int M = 1e6 + 10;

int main(){
	vector<int> power(M+1);
	power[0] = 1;
	for(int i = 1; i <= M; ++i){
		power[i] = power[i-1] << 1;
		if(power[i] >= p) power[i] -= p;
	}
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> A;
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		if(ai >= A.size()) A.resize(ai+1);
		A[ai]++;
	}
	A.resize(nearestPowerOfTwo(A.size()));
	n = A.size();
	fwt(A);
	int ans = 0;
	for(int x = 0; x < n; ++x){
		if(__builtin_popcount(x) & 1){
			ans -= (power[A[x]] - 1);
			if(ans < 0) ans += p;
		}else{
			ans += (power[A[x]] - 1);
			if(ans >= p) ans -= p;
		}
	}
	cout << ans << "\n";
	return 0;
}