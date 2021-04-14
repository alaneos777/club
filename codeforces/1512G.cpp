#include <bits/stdc++.h>
using namespace std;

auto divsSieve(int n){
	vector<int> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j] += i;
		}
	}
	return divs;
}

const int M = 1e7;
const auto divs = divsSieve(M);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> ans(M+1, -1);
	for(int i = M; i >= 0; --i){
		if(divs[i] <= M) ans[divs[i]] = i;
	}
	int t;
	cin >> t;
	while(t--){
		int c;
		cin >> c;
		cout << ans[c] << "\n";
	}
	return 0;
}