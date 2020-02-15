#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli piso(lli a, lli b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		return a / b;
	}else{
		if(a % b == 0) return a / b;
		else return a / b - 1;
	}
}

lli techo(lli a, lli b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		if(a % b == 0) return a / b;
		else return a / b + 1;
	}else{
		return a / b;
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	lli ans = 0;
	for(int x = 0; x < m; ++x){
		for(int y = 0; y < m; ++y){
			int z = (x*x + y*y) % m;
			if(z != 0) continue;
			lli l1 = techo(1 - x, m), r1 = piso(n - x, m);
			lli l2 = techo(1 - y, m), r2 = piso(n - y, m);
			ans += max(r1 - l1 + 1, 0ll) * max(r2 - l2 + 1, 0ll);
		}
	}
	cout << ans << "\n";
	return 0;
}