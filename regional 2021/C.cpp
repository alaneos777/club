#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> arr(n);
	int sum = 0;
	for(int& ai : arr){
		cin >> ai;
		sum += ai;
	}
	int x = sum / n;
	lli res = 1e18;
	auto b = arr;
	reverse(b.begin(), b.end());
	for(auto a : vector<vector<int>>{arr, b}){
		set<int> pending;
		for(int i = 0; i < n; ++i){
			if(a[i] - x < 0){
				pending.insert(i);
			}
		}
		lli ans = 0;
		for(int i = 0; i < n; ++i){
			if(pending.empty()) break;
			int bal_i = a[i] - x;
			if(bal_i > 0){
				a[i] -= bal_i;
				auto it = pending.upper_bound(i);
				if(it == pending.end()){
					it = pending.begin();
				}
				while(bal_i > 0){
					int j = *it;
					int bal_j = a[j] - x;
					if(bal_j < 0){
						int give = min(-bal_j, bal_i);
						bal_i -= give;
						a[j] += give;
						bal_j += give;
						if(bal_j == 0){
							pending.erase(j);
						}
						lli dist = j-i;
						if(dist < 0) dist += n;
						ans += dist*give;
					}
					if(pending.empty()) break;
					it = pending.upper_bound(j);
					if(it == pending.end()){
						it = pending.begin();
					}
				}
			}
		}
		res = min(res, ans);
	}
	cout << res << "\n";
	return 0;
}