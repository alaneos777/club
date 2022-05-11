#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	int N = 1e6+3;
	vector<lli> S = {290797};
	while(S.size() < N){
		S.push_back(S.back()*S.back() % 50515093);
	}
	sort(S.begin(), S.end());

	auto leq = [&](lli x) -> lli{
		lli total = 0;
		int i = 0, j = N-1;
		while(i < j){
			while(i < j && S[i]*S[j] > x) --j;
			total += j-i;
			++i;
		}
		return total;
	};

	lli pairs = (lli)N*(N-1)/2;

	lli lo = 1, hi = S.back()*S.back(), ans = -1;
	while(lo <= hi){
		lli mid = (lo+hi)/2;
		if(leq(mid) >= pairs/2+1){
			ans = mid;
			hi = mid-1;
		}else{
			lo = mid+1;
		}
	}

	cout << ans << "\n";
	return 0;
}