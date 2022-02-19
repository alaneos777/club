#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	if(n&1){
		bool win = false;
		for(int d = 1; d*d <= m; ++d){
			if(m%d > 0) continue;
			int e = m/d;
			if((k <= d && d < m) || (k <= e && e < m)) win = true;
		}
		if(win) cout << "Timur\n";
		else cout << "Marsel\n";
	}else{
		cout << "Marsel\n";
	}
	return 0;
}