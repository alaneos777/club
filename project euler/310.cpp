#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int mex(const vector<int> & a){
	int n = a.size();
	vector<bool> b(n);
	for(int ai : a){
		if(ai < n) b[ai] = true;
	}
	for(int i = 0; i < n; ++i){
		if(!b[i]) return i;
	}
	return n;
}

const int M = 1e5;

int main(){
	vector<int> mem(M+1, -1);
	function<int(int)> g = [&](int a){
		if(mem[a] != -1) return mem[a];
		vector<int> conj;
		for(int d = 1; d*d <= a; ++d){
			if(a-d*d >= 0){
				conj.push_back(g(a-d*d));
			}
		}
		return mem[a] = mex(conj);
	};
	int r = 0;
	for(int i = 0; i <= M; ++i){
		r = max(r, g(i));
	}
	vector<lli> freq(r+1);
	for(int i = 0; i <= M; ++i){
		freq[g(i)]++;
	}
	lli ans = 0;
	for(int i = 0; i <= r; ++i){
		for(int j = 0; j <= r; ++j){
			int k = (i ^ j);
			if(k <= r){
				ans += freq[i] * freq[j] * freq[k];
			}
		}
	}
	ans += 3ll * freq[0] * (M + 1) + 2ll * freq[0];
	assert(ans % 6 == 0);
	ans /= 6;
	cout << ans << "\n";
	return 0;
}