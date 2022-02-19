#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli inf = 1e18;

lli mem[5055][5055];

int main(){
	memset(mem, -1, sizeof(mem));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, x;
	cin >> n >> k >> x;
	vector<int> a(n);
	for(int& ai : a){
		cin >> ai;
	}
	a.insert(a.begin(), 0);
	function<lli(int, int)> f = [&](int pos, int rep) -> lli{
		if(pos == 0){
			if(rep == x) return 0;
			else return -inf;		
		}else{
			lli& ans = mem[pos][rep];
			if(ans != -1) return ans;
			ans = -inf;
			for(int d = 1; d <= k && d <= pos; ++d){
				if(f(pos - d, rep + 1) != -inf) ans = max(ans, f(pos - d, rep + 1) + a[pos]);
			}
			return ans;
		}
	};
	lli ans = -inf;
	for(int i = n-k+1; i <= n; ++i){
		for(int j = 0; j <= x; ++j){
			ans = max(ans, f(i, j));
		}
	}
	if(ans == -inf) ans = -1;
	cout << ans << "\n";
	return 0;
}