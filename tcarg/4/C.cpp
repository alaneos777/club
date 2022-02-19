#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<vector<int>> table(2, vector<int>(n+1));
	for(int i = 1; i <= n; ++i){
		int w;
		cin >> w;
		table[w-1][i]++;
	}
	partial_sum(table[0].begin(), table[0].end(), table[0].begin());
	partial_sum(table[1].begin(), table[1].end(), table[1].begin());
	vector<pair<int, int>> ans;
	for(int t = 1; t <= n; ++t){
		int p0 = 0, p1 = 0;
		int s0 = 0, s1 = 0;
		int l = -1;
		bool test = true;
		while(true){
			int o0 = table[0][p0];
			int o1 = table[1][p1];
			p0++, p1++;
			int f0 = lower_bound(table[0].begin()+p0, table[0].end(), t+o0) - table[0].begin();
			int f1 = lower_bound(table[1].begin()+p1, table[1].end(), t+o1) - table[1].begin();
			if(f0 > n && f1 > n){
				test = false;
				break;
			}
			if(f0 <= f1){
				s0++;
				l = 0;
				p0 = f0, p1 = f0;
			}else{
				s1++;
				l = 1;
				p0 = f1, p1 = f1;
			}
			if(min(f0, f1) == n) break;
		}
		if(test && s0 != s1 && (s0 > s1 ? l==0 : l==1)){
			ans.emplace_back(max(s0, s1), t);
		}
	}
	sort(ans.begin(), ans.end());
	cout << ans.size() << "\n";
	for(auto[s, t] : ans){
		cout << s << " " << t << "\n";
	}
	return 0;
}