#include <bits/stdc++.h>
using namespace std;
typedef pair<int, char> pii;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int m, n, h = 1, v = 1;
	cin >> m >> n;
	vector<pii> info(m + n - 2);
	for(int i = 0; i < m - 1; ++i){
		cin >> info[i].first;
		info[i].second = 'V';
	}
	for(int i = 0; i < n - 1; ++i){
		cin >> info[m - 1 + i].first;
		info[m - 1 + i].second = 'H';
	}
	int ans = 0;
	sort(info.begin(), info.end(), greater<pair<int, char>>());
	for(auto & b : info){
		if(b.second == 'H'){
			ans += v * b.first;
			++h;
		}else{
			ans += h * b.first;
			++v;
		}
	}
	cout << ans;
	return 0;
}