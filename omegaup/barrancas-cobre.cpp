#include <iostream>
#include <vector>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> nums(n);
	for(int i = 0; i < n; ++i){
		cin >> nums[i];
	}
	int ans = -(1 << 30);
	int i = 0, j = k - 1;
	while(j < n){
		ans = max(ans, nums[j] - nums[i]);
		++i, ++j;
	}
	cout << ans << "\n";
}