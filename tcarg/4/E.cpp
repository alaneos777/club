#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	int M = 0;
	for(int& ai : a){
		cin >> ai;
		M = max(M, ai);
	}
	sort(a.begin(), a.end());
	vector<bool> calc(M+1);
	int ans = 0;
	for(int aj : a){
		if(calc[aj]) continue;
		for(int d = aj; d <= 2*M; d += aj){
			int pos = lower_bound(a.begin(), a.end(), d) - a.begin();
			pos--;
			if(0 <= pos && pos < n && a[pos] >= aj){
				ans = max(ans, a[pos] % aj);
			}
		}
		calc[aj] = true;
	}
	cout << ans << "\n";
	return 0;
}