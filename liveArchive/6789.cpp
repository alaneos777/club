#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	lli k;
	while(cin >> n >> k && !(n == 0 && k == 0)){
		vector<int> lengths(n);
		for(int i = 0; i < n; ++i){
			cin >> lengths[i];
		}
		sort(lengths.begin(), lengths.end());

		int l = -1;
		for(int i = 1; i < n; ++i){
			if(i == 1 || lengths[i]-lengths[i-1] < l){
				l = lengths[i]-lengths[i-1];
			}
		}
		int r = lengths.back()-lengths[0], m;

		auto findPos = [&](int dif){
			vector<pair<int, int>> eq_pos;
			lli cnt = 0, eq = 0;
			for(int m = 0; m < n; ++m){
				cnt += lower_bound(lengths.begin() + m+1, lengths.end(), lengths[m] + dif) - (lengths.begin() + m+1);
				auto s = equal_range(lengths.begin() + m+1, lengths.end(), lengths[m] + dif);
				for(auto it = s.first; it != s.second; ++it){
					eq_pos.emplace_back(lengths[m], *it);
				}
				eq += s.second - s.first;
			}
			return make_pair(eq_pos, make_pair(cnt + 1, cnt + eq));
		};

		while(true){
			m = (l + r) / 2;
			auto s = findPos(m);
			auto eq_pos = s.first;
			auto range = s.second;
			if(range.first <= k && k <= range.second){
				cout << eq_pos[k-range.first].first << " " << eq_pos[k-range.first].second << "\n";
				break;
			}else if(k < range.first){
				r = m - 1;
			}else{
				l = m + 1;
			}
		}
	}
	return 0;
}