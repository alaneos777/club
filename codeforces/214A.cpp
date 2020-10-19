#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

int main(){
	int n, m;
	cin >> n >> m;
	int c = n*n - m;
	vector<pair<int, int>> sols;
	auto is = [&](lli x){
		return x*x*x*x - 2*n*x*x + x + c == 0;
	};
	if(c == 0){
		sols.emplace_back(0, n);
		if(n == 1){
			sols.emplace_back(1, 0);
		}
	}else{
		for(int d = 1; d*d <= c; ++d){
			if(c % d != 0) continue;
			int e = c / d;
			if(is(d) && n - d*d >= 0) sols.emplace_back(d, n - d*d);
			if(e != d && is(e) && n - e*e >= 0) sols.emplace_back(e, n - e*e);
		}
	}
	cout << sols.size() << "\n";
	return 0;
}