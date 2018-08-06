#include <iostream>
using namespace std;
typedef long long int lli;

lli c1, c2, x, y, p;

bool can(lli n){
	lli divByX = n / x;
	lli divByY = n / y;
	lli divByBoth = n / p;
	lli divByNone = n - (divByX + divByY - divByBoth);
	lli q1 = divByY - divByBoth;
	lli q2 = divByX - divByBoth;
	lli rem1 = max(c1 - q1, 0ll);
	lli rem2 = max(c2 - q2, 0ll);
	return rem1 + rem2 <= divByNone;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> c1 >> c2 >> x >> y;
	p = x * y;
	lli l = c1 + c2 - 2, r = 2 * (c1 + c2), n;
	while(r - l > 1){
		n = (l + r) / 2;
		if(can(n))
		    r = n;
		else
		    l = n;
	}
	cout << r << "\n";
	return 0;
}