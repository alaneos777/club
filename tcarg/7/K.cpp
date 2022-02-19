#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<lli> a(n), sums(n);
	for(lli& ai : a){
		cin >> ai;
	}
	sort(a.begin(), a.end());
	partial_sum(a.begin(), a.end(), sums.begin());
	int maxi = -1e9, where = 2e9;
	for(int i = 0; i < n; ++i){
		auto can = [&](int f){
			return a[i]*f - (sums[i] - (i-f>=0 ? sums[i-f] : 0)) <= k;
		};
		int lo = 1, hi = i+1, ans = -1;
		while(lo <= hi){
			int mid = (lo + hi) / 2;
			if(can(mid)){
				lo = mid+1;
				ans = mid;
			}else{
				hi = mid-1;
			}
		}
		if(ans == -1) continue;
		if(ans > maxi){
			maxi = ans;
			where = a[i];
		}else if(ans == maxi){
			if(a[i] < where){
				where = a[i];
			}
		}
	}
	cout << maxi << " " << where << "\n";
	return 0;
}