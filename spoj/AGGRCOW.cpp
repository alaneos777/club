#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t, n, c;
	cin >> t;
	while(t--){
		cin >> n >> c;
		vector<int> stalls(n);
		for(int i = 0; i < n; ++i){
			cin >> stalls[i];
		}
		sort(stalls.begin(), stalls.end());
		auto can = [&](int dif){
			int prev = 0;
			int cows = 0;
			for(int i = 0; i < n; ++i){
				if(i == 0 || stalls[i] - prev >= dif){
					cows++;
					prev = stalls[i];
				}
			}
			return cows >= c;
		};
		int l = 0, r = stalls.back() + 10, m = 0;
		while(true){
			m = l + ((r - l) >> 1);
			if(can(m)){
				if(!can(m + 1)) break;
				l = m + 1;
			}else{
				r = m - 1;
			}
		}
		cout << m << "\n";
	}
	return 0;
}