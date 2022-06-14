#include <bits/stdc++.h>
using namespace std;
using tup = tuple<int, int, int>;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for(int& ai : a){
		cin >> ai;
	}

	auto leq = [&](int l, int r, int pos) -> int{
		if(l <= pos && pos <= r) return pos-l+1;
		else if(pos < l) return 0;
		else return r-l+1;
	};

	auto get = [&](const vector<tup>& plan, lli pos) -> int{
		int low = 0, high = n-1, ans;
		while(low <= high){
			int mid = (low+high)/2;
			lli cnt = 0;
			for(auto[l, r, x] : plan){
				cnt += leq(l, r, mid) * (lli)x;
			}
			if(cnt >= pos){
				ans = a[mid];
				high = mid-1;
			}else{
				low = mid+1;
			}
		}
		return ans;
	};

	while(q--){
		int k;
		cin >> k;
		vector<tup> plan(k);
		lli len = 0;
		for(auto&[l, r, x] : plan){
			cin >> l >> r >> x;
			--l, --r;
			len += (lli)x * (r-l+1);
		}
		if(len&1){
			cout << get(plan, (len+1)/2) << "\n";
		}else{
			cout << fixed << setprecision(1) << (get(plan, len/2) + get(plan, len/2+1)) / 2.0 << "\n";
		}
	}
	return 0;
}