#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<lli> coins(n);
		for(int i = 0; i < n; i++){
			cin >> coins[i];
		}
		lli sum = coins[0];
		int ans = 1;
		for(int i = 1; i < n; i++){
			if(i == n - 1 || sum + coins[i] < coins[i + 1]){
				sum += coins[i];
				ans++;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}