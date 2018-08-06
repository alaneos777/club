#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	int n, l;
	double w;
	while(cin >> n >> l >> w){
		vector<pair<double, double>> segments;
		for(int i = 0; i < n; i++){
			double c, r;
			cin >> c >> r;
			if(r > w / 2){
				double dist = sqrt(r * r - w * w / 4);
				segments.push_back(make_pair(c - dist, c + dist));
			}
		}
		sort(segments.begin(), segments.end());
		double pos = 0;
		bool found = false, change = true;
		int i = 0;
		int ans = 0;
		while(change){
			change = false;
			double rightMost = pos;
			while(i < segments.size() && segments[i].first <= pos){
				if(segments[i].second > rightMost){
					rightMost = segments[i].second;
					change = true;
				}
				i++;
			}
			pos = rightMost;
			if(change){
				ans++;
			}
			if(pos >= l){
				found = true;
				break;
			}
		}
		if(found){
			cout << ans << "\n";
		}else{
			cout << "-1\n";
		}
	}
	return 0;
}