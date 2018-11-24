#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	int t;
	lli A, B;
	while(n--) cin >> t >> A >> B;
	vector<pair<lli, int>> a(m);
	for(int i = 0; i < m; ++i){
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a.begin(), a.end(), greater<pair<lli, int>>());
	vector<int> pos(k);
	for(int i = 0; i < k; ++i){
		pos[i] = a[i].second;
	}
	sort(pos.begin(), pos.end());
	for(int & p : pos) cout << p+1 << " ";
	cout << "\n";
	return 0;
}