#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<pair<int, int>> jobs(n);
	for(int i = 0; i < n; ++i){
		cin >> jobs[i].second >> jobs[i].first;
	}
	int cnt = 0;
	sort(jobs.begin(), jobs.end());
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> st;
	for(int i = n-1; i >= 0; --i){
		lli t = jobs[i].first - (i ? jobs[i-1].first : 0);
		st.emplace(jobs[i].second, i);
		while(t && !st.empty()){
			int fi = st.top().first;
			int se = st.top().second;
			st.pop();
			if(fi <= t){
				t -= fi;
				cnt++;
			}else{
				st.emplace(fi - t, se);
				t = 0;
			}
		}
	}
	if(cnt == n) cout << "Yes\n";
	else cout << "No\n";
	return 0;
}