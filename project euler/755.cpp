#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	lli N = 1e13;
	vector<lli> F = {1, 2};
	while(F.back() <= N){
		F.push_back(F[F.size()-1] + F[F.size()-2]);
	}
	F.pop_back();
	reverse(F.begin(), F.end());
	vector<lli> sums(F.size());
	partial_sum(F.begin(), F.end(), sums.begin());
	map<pair<int, lli>, lli> mem;
	function<lli(int, lli)> f = [&](int pos, lli rem){
		if(pos == F.size()) return 1ll;
		if(sums.back() - (pos ? sums[pos-1] : 0) <= rem) return 1ll<<(F.size()-pos);
		auto key = make_pair(pos, rem);
		if(mem.count(key)) return mem[key];
		lli ans = f(pos+1, rem);
		if(rem >= F[pos]) ans += f(pos+1, rem-F[pos]);
		return mem[key] = ans;
	};
	cout << f(0, N) << "\n";
	return 0;
}