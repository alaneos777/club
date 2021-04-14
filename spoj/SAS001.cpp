#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct FenwickTree{
	int N;
	vector<lli> bit;

	FenwickTree(int N): N(N){
		bit.resize(N);
	}

	void update(int pos, lli value){
		while(pos < N){
			bit[pos] += value;
			pos |= pos + 1;
		}
	}

	lli query(int r){
		lli res = 0;
		while(r >= 0){
			res += bit[r];
			r = (r & (r + 1)) - 1;
		}
		return res;
	}

	lli query(int l, int r){
		return query(r) - query(l - 1);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, p;
	cin >> n >> p;
	map<int, vector<int>> mp;
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		mp[ai].push_back(i);
	}
	int dis = mp.size();
	vector<int> b(n);
	int pos = 0;
	for(const auto& par : mp){
		for(int i : par.second){
			b[i] = pos;
		}
		pos++;
	}
	FenwickTree bit(dis);
	lli invs = 0;
	for(int i = 0; i < p; ++i){
		bit.update(b[i], 1);
		invs += bit.query(b[i]+1, dis-1);
	}
	lli ans = invs;
	int start = 0;
	for(int i = 1; i+p <= n; ++i){
		// [i-1, i+p-2] -> [i, i+p-1]
		invs -= bit.query(0, b[i-1]-1);
		bit.update(b[i-1], -1);
		bit.update(b[i+p-1], 1);
		invs += bit.query(b[i+p-1]+1, dis-1);
		if(invs > ans){
			ans = invs;
			start = i;
		}
	}
	cout << start+1 << " " << ans << "\n";
	return 0;
}