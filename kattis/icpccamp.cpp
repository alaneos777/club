#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, p, q, s;
	cin >> n >> p >> q >> s;
	vector<int> left(p), right(q);
	for(int & x : left){
		cin >> x;
	}
	for(int & y : right){
		cin >> y;
	}
	if(p > q){
		swap(p, q);
	}
	sort(left.begin(), left.end(), greater<int>());

	multiset<int> st_original(right.begin(), right.end());
	auto len = [&](int d){
		multiset<int> st = st_original;
		int cnt = 0;
		for(int pi : left){
			int lower = pi - d, upper = min(s - pi, d + pi);
			if(lower > upper) continue;
			auto it = st.lower_bound(upper);
			int qi = -1;
			if(it != st.end() && *it == upper){
				qi = *it;
			}else if(it != st.begin()){
				--it;
				qi = *it;
			}
			if(qi == -1) continue;
			if(lower > qi) continue;
			st.erase(it);
			cnt++;
		}
		return cnt;
	};

	int l = 0, r = 1e9, ans = -1;
	while(l <= r){
		int m = (l + r) / 2;
		if(len(m) >= n){
			ans = m;
			r = m-1;
		}else{
			l = m+1;
		}
	}
	cout << ans << "\n";
	return 0;
}