#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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
				R[i + j + d] += ans[i] * ans[j];
		for(int i = deg-1; i >= 0; i--){
			for(int j = 0; j < deg; j++)
				R[i + j] += R[i + deg] * P[j];
		}
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		nValue += ans[i] * init[i];
	return nValue;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<lli> P(k, 1), init(k, 1);
	for(int i = 2; i < k; ++i){
		init[i] = init[i-1] * 2;
	}
	cout << solveRecurrence(P, init, n) << "\n";
}