#include <iostream>
#include <vector>
using namespace std;
using lli = long long int;
const lli mod = 1e9+7;

lli solveRecurrence(const vector<lli> & P, const vector<lli> & init, lli n){
	int deg = P.size();
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				R[i + j + d] += ans[i] * ans[j] % mod;
		for(int i = 0; i < 2*deg; ++i) R[i] %= mod;
		for(int i = deg-1; i >= 0; i--){
			R[i + deg] %= mod;
			for(int j = 0; j < deg; j++)
				R[i + j] += R[i + deg] * P[j] % mod;
		}
		for(int i = 0; i < deg; i++) R[i] %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		nValue += ans[i] * init[i] % mod;
	return nValue % mod;
}

vector<vector<lli>> Ncr;
void ncrSieve(lli n){
	Ncr.resize(n + 1);
	Ncr[0] = {1};
	for(lli i = 1; i <= n; ++i){
		Ncr[i].resize(i + 1);
		Ncr[i][0] = Ncr[i][i] = 1;
		for(lli j = 1; j <= i / 2; j++)
			Ncr[i][i - j] = Ncr[i][j] = (Ncr[i - 1][j - 1] + Ncr[i - 1][j]) % mod;
	}
}

int main(){
	int n = 5000;
	lli m = 1000000000000ll;
	ncrSieve(n+10);
	vector<lli> row(n-1), init(n-1), P(n-1);
	row[0] = 1;
	for(int i = 0; i < n-1; ++i){
		for(int j = 0; j < n-1; ++j){
			init[i] = (init[i] + row[j]) % mod;
		}
		for(int j = 1; j < n-1; ++j){
			row[j] = (row[j-1] + row[j]) % mod;
		}
		reverse(row.begin(), row.end());
	}
	for(int k = n-2; k >= 0; --k){
		P[n-2-k] = Ncr[n-1-(k+1)/2][k/2];
	}
	for(int k = 0; k < n-1; ++k){
		if(k%4==2 || k%4==3) P[k] = (mod - P[k]) % mod;
	}
	reverse(P.begin(), P.end());
	lli ans = solveRecurrence(P, init, m);
	cout << ans << "\n";
	return 0;
}