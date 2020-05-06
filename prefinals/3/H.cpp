#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;
const ld pi = acosl(-1);

lli Sqrt(lli x){
	lli r = sqrt(x);
	for(lli i = max(0ll, r-1); i <= r+1; ++i){
		if(i*i > x) return i-1;
	}
	assert(0);
	return -1;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	map<lli, int> events;
	set<pair<int, int>> cells;
	vector<pair<lli, lli>> ranges;
	for(int r = 0; r < n; ++r){
		lli x, y, w, h;
		cin >> x >> y >> w >> h;
		for(int i = 0; i < w; ++i){
			for(int j = 0; j < h; ++j){
				lli A = (x+i)*(x+i) + (y+j)*(y+j);
				lli B = (x+i+1)*(x+i+1) + (y+j)*(y+j);
				lli C = (x+i)*(x+i) + (y+j+1)*(y+j+1);
				lli D = (x+i+1)*(x+i+1) + (y+j+1)*(y+j+1);
				lli a = min({A, B, C, D});
				lli b = max({A, B, C, D});
				ranges.emplace_back(a, b);
				if(!cells.count({x+i, y+j})){
					events[a]++;
					events[b]--;
					cells.emplace(x+i, y+j);
					lli ra = Sqrt(a), rb = Sqrt(b);
					if(ra*ra != a){
						if(!events.count(ra*ra)) events[ra*ra] = 0;
						if(!events.count((ra+1)*(ra+1))) events[(ra+1)*(ra+1)] = 0;
					}
					if(rb*rb != b){
						if(!events.count(rb*rb)) events[rb*rb] = 0;
						if(!events.count((rb+1)*(rb+1))) events[(rb+1)*(rb+1)] = 0;
					}
				}
			}
		}
	}
	cout << events.size() << "\n";

	sort(ranges.begin(), ranges.end());
	ranges.resize(distance(ranges.begin(), unique(ranges.begin(), ranges.end())));
	int idx = 0;
	for(int i = 1; i < ranges.size(); ++i){
		if(ranges[idx].second >= ranges[i].first){
			ranges[idx].second = max(ranges[idx].second, ranges[i].second);  
			ranges[idx].first = min(ranges[idx].first, ranges[i].first);  
		}else{
			ranges[++idx] = ranges[i];
		}
	}
	ranges.resize(idx+1);
	lli total = 0;
	for(const auto & range : ranges){
		total += range.second - range.first;
	}

	lli black = 0;
	lli active = 0;
	for(auto it = events.begin(); it != events.end(); ++it){
		lli r; int inc;
		tie(r, inc) = *it;
		active += inc;
		lli cnt = 8*Sqrt(r)+4;
		if(cnt == active){
			auto it2 = it; ++it2;
			black += it2->first - r;
		}
		//cout << sqrt(r) << " " << inc << "\n";
	}
	cout << fixed << setprecision(9) << black*pi << "\n" << (total-black)*pi << "\n";
	return 0;
}