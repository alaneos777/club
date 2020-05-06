#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

auto lpSieve(int n){
	vector<int> lp(n+1, 2);
	for(int i = 1; i <= n; i += 2) lp[i] = i;
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j){
					lp[j] = i;
				}
			}
		}
	}
	return lp;
}

const int M = 1e7;
const auto lp = lpSieve(M/10);

auto getDivs(int n){
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n], e = 0;
		while(n % p == 0){
			n /= p;
			e += 2;
		}
		f.emplace_back(p, e);
	}
	vector<lli> divs;
	function<void(int, lli)> dfs = [&](int pos, lli d){
		if(pos == f.size()){
			divs.push_back(d);
		}else{
			lli p_pow = 1;
			int p, e;
			tie(p, e) = f[pos];
			for(int i = 0; i <= e; ++i){
				dfs(pos + 1, d * p_pow);
				p_pow *= p;
			}
		}
	};
	dfs(0, 1);
	sort(divs.begin(), divs.end());
	return divs;
}

int main(){
	lli sum = 0;
	set<tuple<int, int, int>> st;
	for(int r = 1; r < lp.size(); ++r){
		auto divs = getDivs(r);
		lli R = (lli)r * r;
		vector<pair<int, int>> pos;
		for(lli e : divs){
			lli d = R / e;
			if(d <= e) break;
			lli side = (d - e) / 2;
			lli bis = (d + e) / 2;
			if((d - e) % 2 == 0 && side <= M) pos.push_back({bis, side});
		}
		int sz = pos.size();
		for(int i = 0; i < sz; ++i){
			for(int j = 0; j < sz; ++j){
				int ai = pos[i].first, bi = pos[j].first;
				int x = pos[i].second, y = pos[j].second;
				__int128 num = __int128(R) * (x + y), den = (lli)x*y - R;
				if(den <= 0) continue;
				if(num % den > 0) continue;
				lli z = num / den;
				if(z > M) continue;
				int ci = sqrt(z*z + R);
				int a = y + z, b = x + z, c = x + y;
				vector<int> arr = {a, b, c}; sort(arr.begin(), arr.end());
				a = arr[0], b = arr[1], c = arr[2];
				int s = a + b + c;
				if(s <= M && !st.count({a, b, c})){
					st.emplace(a, b, c);
					//cout << r << " " << s << " (" << a << ", " << b << ", " << c << ") (" << ai << ", " << bi << ", " << ci << ") " << s+ai+bi+ci << "\n";
					sum += s+ai+bi+ci;
				}
			}
		}
	}
	cout << sum << "\n";
	return 0;
}