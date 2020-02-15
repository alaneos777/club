#include <bits/stdc++.h>
using namespace std;
using ld = long double;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int d;
		cin >> d;
		if(d > 0 && d < 4){
			cout << "N\n";
		}else{
			ld a = (d + sqrtl(d*d - 4*d)) / 2;
			ld b = (d - sqrtl(d*d - 4*d)) / 2;
			cout << fixed << setprecision(10) << "Y " << a << " " << b << "\n";
		}
	}
	return 0;
}