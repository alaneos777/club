#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	string cad;
	cin >> cad;
	sort(cad.begin(), cad.end());
	char prev = 0;
	int cnt = 0;
	int ans = 0;
	for(int i = 0; i < n; ++i){
		if(cad[i] - prev > 1){
			ans += cad[i] - 'a' + 1;
			cnt++;
			prev = cad[i];
		}
		if(cnt == k) break;
	}
	if(cnt == k) cout << ans << "\n";
	else cout << "-1\n";
	return 0;
}