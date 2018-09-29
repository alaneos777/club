#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli ans(lli n, lli x, lli y){
	if((x + y) & 1){
		if(x & 1){
			return (n * n + 1) / 2 + y / 2 + ((x - 1) / 2) * n;
		}else{
			return (n * n + 1) / 2 + n / 2 + (y + 1) / 2 + (x / 2 - 1) * n;
		}
	}else{
		if(x & 1){
			return ((y + 1) / 2) + ((x - 1) / 2) * n;
		}else{
			return (n + 1) / 2 + y / 2 + (x / 2 - 1) * n;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, q, x, y;
	cin >> n >> q;
	while(q--){
		cin >> x >> y;
		cout << ans(n, x, y) << "\n";
	}
	return 0;
}