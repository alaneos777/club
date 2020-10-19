#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool is(lli n){
	lli x = n * n;
	vector<int> digs;
	while(x){
		digs.push_back(x % 10);
		x /= 10;
	}
	reverse(digs.begin(), digs.end());
	vector<vector<lli>> mem(digs.size());
	function<vector<lli>(int)> dp = [&](int i){
		if(i == digs.size()) return vector<lli>{0};
		if(mem[i].size()) return mem[i];
		lli acum = 0;
		vector<lli> ans = {};
		for(int j = i; j < digs.size(); ++j){
			acum = acum * 10 + digs[j];
			if(acum > n) break;
			auto rhs = dp(j+1);
			for(lli y : rhs){
				if(acum + y <= n) ans.push_back(acum + y);
			}
		}
		return mem[i] = ans;
	};
	auto arr = dp(0);
	sort(arr.begin(), arr.end());
	return binary_search(arr.begin(), arr.end(), n);
}

int main(){
	int N = 1e6;
	lli ans = 0;
	for(lli i = 2; i <= N; ++i){
		if((i % 9 == 0 || i % 9 == 1) && is(i)) ans += i*i;
	}
	cout << ans << "\n";
	return 0;
}