#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<pair<int, int>> a(n);
	for(int i = 0; i < n; ++i){
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a.begin(), a.end(), greater<pair<int, int>>());
	lli sum = 0;
	vector<bool> vis(n);
	for(int i = 0; i < m*k; ++i){
		sum += a[i].first;
		vis[a[i].second] = true;
	}
	cout << sum << "\n";
	int acum = 0, cnt = 0;
	for(int i = 0; i < n; ++i){
		if(vis[i]){
			acum++;
			if(acum == m){
				acum = 0;
				cnt++;
				if(cnt < k) cout << i+1 << " ";
			}
		}
	}
	cout << "\n";
	return 0;
}