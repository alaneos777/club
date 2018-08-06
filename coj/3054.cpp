#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0);
	lli m = 1000003;
	int limit = 1000000;
	vector<lli> acum(limit + 1);
	acum[1] = 1;
	for(int i = 1; i <= limit; i++){
		acum[i] = (i * acum[i - 1] + 1) % m;
	}
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		cout << acum[n] << "\n";
	}
	return 0;
}