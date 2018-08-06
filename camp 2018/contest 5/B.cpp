#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string F = "FIRST", S = "SECOND", D = "DRAW";
	lli x1, x2, a, b;
	cin >> x1 >> x2 >> a >> b;
	lli d = x2 - x1;
	lli sgn = 1;
	if(a <= 0 && 0 <= b){
		if(a <= d && d <= b){
			cout << F << "\n" << x2 << "\n";
		}else{
			cout << D << "\n";
		}
	}else{
		if(a <= b && b < 0){
			d *= -1, a *= -1, b *= -1;
			swap(a, b);
			sgn *= -1;
		}
		if(d < 0){
			cout << D << "\n";
		}else if(d % (a + b) == 0){
			cout << S << "\n";
		}else if(a <= d % (a + b) && d % (a + b) <= b){
			cout << F << "\n" << x2 - sgn * d / (a + b) * (a + b) << "\n";
		}else{
			cout << D << "\n";
		}
	}
	return 0;
}