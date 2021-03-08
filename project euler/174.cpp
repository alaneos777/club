#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto divsSieve(int n){
	vector<vector<int>> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j].push_back(i);
		}
	}
	return divs;
}

const int N = 1e6;
const auto divs = divsSieve(N);

int main(){
	int T = 10;
	vector<int> freq(T+1);
	for(int n = 1; n <= N; ++n){
		int cnt = 0;
		for(int d : divs[n]){
			int e = n/d;
			if(d >= e) break;
			if((d + e) % 2 == 1) continue;
			int a = (e+d)/2;
			int b = (e-d)/2;
			if((a-b) % 2 == 0){
				cnt++;
			}
		}
		if(cnt <= T){
			freq[cnt]++;
		}
	}
	int ans = 0;
	for(int i = 1; i <= T; ++i){
		ans += freq[i];
	}
	cout << ans << "\n";
	return 0;
}