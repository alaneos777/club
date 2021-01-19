#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e18;

struct FenwickTree{
	int N;
	vector<lli> bit;

	FenwickTree(int N): N(N){
		bit.resize(N);
	}

	void update(int pos, lli value){
		while(pos < N){
			bit[pos] += value;
			if(bit[pos] >= mod) bit[pos] -= mod;
			pos |= pos + 1;
		}
	}

	lli query(int r){
		lli res = 0;
		while(r >= 0){
			res += bit[r];
			if(res >= mod) res -= mod;
			r = (r & (r + 1)) - 1;
		}
		return res;
	}

	lli query(int l, int r){
		lli ans = query(r) - query(l - 1);
		if(ans < 0) ans += mod;
		return ans;
	}
};

auto divsSieve(int n){
	vector<int> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j]++;
		}
	}
	return divs;
}

const int N = 6e7;
const auto divs = divsSieve(N+1);

int main(){
	vector<int> dT(N+1);
	for(int i = 1; i <= N; ++i){
		if(i & 1){
			dT[i] = divs[i] * divs[(i+1)/2];
		}else{
			dT[i] = divs[i/2] * divs[i+1];
		}
	}
	int M = *max_element(dT.begin(), dT.end());
	int k = 3;
	vector<FenwickTree> bit(k-1, FenwickTree(M+1));
	lli ans = 0;
	for(int i = 1; i <= N; ++i){
		int a = dT[i];
		bit[0].update(a, 1);
		for(int j = 1; j < k - 1; ++j){
			bit[j].update(a, bit[j - 1].query(a + 1, M));
		}
		ans += bit[k - 2].query(a + 1, M);
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}