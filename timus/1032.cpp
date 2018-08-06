#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	vector<int> nums(n+1), acum(n+1), seen(n, -1);
	for(int i = 1; i <= n; ++i){
		cin >> nums[i];
		acum[i] = (acum[i - 1] + nums[i]) % n;
	}
	for(int i = 0; i <= n; ++i){
		if(seen[acum[i]] == -1){
			seen[acum[i]] = i;
		}else{
			cout << i-seen[acum[i]] << "\n";
			for(int j = seen[acum[i]]+1; j <= i; ++j){
				cout << nums[j] << "\n";
			}
			break;
		}
	}
	return 0;
}