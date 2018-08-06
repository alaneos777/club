#include <bits/stdc++.h>
using namespace std;
typedef double ld;

int main(){
	ios_base::sync_with_stdio(0);
	vector<ld> ans(10000001);
	for(int i = 1; i <= 10000000; i++){
		ans[i] = ans[i - 1] + log10(i);
	}
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		cout << (int)floor(ans[n]) + 1 << "\n";
	}
	return 0;
}