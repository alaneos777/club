#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9+7;

int mem[3][111][3333];

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	memset(mem, -1, sizeof(mem));
	int n, sz;
	cin >> n >> sz;
	vector<vector<int>> a(2, vector<int>(n));
	for(int i = 0; i < n; ++i){
		cin >> a[0][i] >> a[1][i];
	}
	function<int(int, int, int)> f = [&](int giro, int last, int len) -> int{
		if(len == sz) return 1;
		int& ans = mem[giro+1][last+1][len];
		if(ans != -1) return ans;
		ans = 0;
		for(int i = 0; i < n; ++i){
			if(last == -1){
				if(len + a[0][i] <= sz){
					ans += f(1, i, len + a[0][i]);
					if(ans >= mod) ans -= mod;
				}
				if(a[0][i] != a[1][i] && len + a[1][i] <= sz){
					ans += f(0, i, len + a[1][i]);
					if(ans >= mod) ans -= mod;
				}
			}else{
				if(last == i) continue;
				if(a[giro][last] == a[0][i] && len + a[0][i] <= sz){
					ans += f(1, i, len + a[0][i]);
					if(ans >= mod) ans -= mod;
				}
				if(a[0][i] != a[1][i] && a[giro][last] == a[1][i] && len + a[1][i] <= sz){
					ans += f(0, i, len + a[1][i]);
					if(ans >= mod) ans -= mod;
				}
			}
		}
		return ans;
	};
	cout << f(-1, -1, 0) << "\n";
	return 0;
}