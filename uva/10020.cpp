#include <bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin >> t;
	while(t--){
		int m, x, y;
		cin >> m;
		vector<pair<int, int>> segments, ans;
		while(cin >> x >> y){
			if(x == 0 && y == 0) break;
			segments.push_back(make_pair(x, y));
		}
		sort(segments.begin(), segments.end());
		int pos = 0;
		bool found = false, change = true;
		int i = 0;
		while(change){
			change = false;
			int rightMost = pos;
			int nuevo;
			while(i < segments.size() && segments[i].first <= pos){
				if(segments[i].second > rightMost){
					rightMost = segments[i].second;
					nuevo = i;
					change = true;
				}
				i++;
			}
			pos = rightMost;
			if(change){
				ans.push_back(segments[nuevo]);
			}
			if(pos >= m){
				found = true;
				break;
			}
		}
		if(!found){
			ans = vector<pair<int, int>>();
		}
		sort(ans.begin(), ans.end());
		cout << ans.size() << "\n";
		for(auto it = ans.begin(); it != ans.end(); ++it){
			cout << it->first << " " << it->second << "\n";
		}
		if(t > 0) cout << "\n";
	}
	return 0;
}