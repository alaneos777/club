#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, m;
	cin >> n >> k >> m;
	deque<pair<lli, int>> a(n);
	for(int i = 0; i < n; ++i) cin >> a[i].first;
	lli tot = 0;
	for(int i = 0; i < n; ++i) tot += a[i].first, a[i].second = 0;
	sort(a.begin(), a.end());
	int operations = 0;
	while(operations < m){
		int sz = a.size();
		if(sz == 1 || (tot + 1) * (sz - 1) > (tot - a.front().first) * sz){
			int idx = -1;
			for(int i = sz-1; i >= 0; --i){
				if(a[i].second < k){
					idx = i;
					break;
				}
			}
			if(idx == -1) break;
			tot++;
			a[idx].first++;
			a[idx].second++;
			operations++;
		}else{
			tot -= a.front().first;
			a.erase(a.begin());
			operations++;
		}
	}
	cout << fixed << setprecision(10) << (long double)tot / a.size() << "\n";
	return 0;
}