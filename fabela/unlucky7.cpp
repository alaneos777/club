#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool valid(int n, int b){
	while(n){
		int d = n % b;
		if(d == 7) return false;
		n /= b;
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	int ans = 0;
	for(int i = 1; i <= n; ++i){
		if(valid(i, 8) && valid(i, 10)){
			ans++;
		}
	}
	cout << ans << "\n";
	return 0;
}