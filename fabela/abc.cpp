#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j]++;
		}
	}
	lli ans = 0;
	for(int c = 1; c < n; ++c){
		ans += divs[n-c];
	}
	cout << ans << "\n";
	return 0;
}