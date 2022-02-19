#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<lli> heads(n), tracks(m);
	for(lli& hi : heads){
		cin >> hi;
	}
	for(lli& ti : tracks){
		cin >> ti;
	}
	auto can = [&](lli t){
		int l = 0, r = 0;
		for(int i = 0; i < n; ++i){
			lli ans = abs(tracks[r] - tracks[l]) + min(abs(tracks[l]-heads[i]), abs(tracks[r]-heads[i]));
			while(r < m && ans <= t){
				++r;
				ans = abs(tracks[r] - tracks[l]) + min(abs(tracks[l]-heads[i]), abs(tracks[r]-heads[i]));
			}
			l = r;
			if(r == m) return true;
		}
		return false;
	};
	lli lo = 0, hi = 1e11, ans = -1;
	while(lo <= hi){
		lli mid = (lo + hi) / 2;
		if(can(mid)){
			ans = mid;
			hi = mid-1;
		}else{
			lo = mid+1;
		}
	}
	cout << ans << "\n";
	return 0;
}