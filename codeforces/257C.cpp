#include <bits/stdc++.h>
using namespace std;
const long double pi = acosl(-1);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<long double> angs(n);
	for(int i = 0; i < n; ++i){
		int x, y;
		cin >> x >> y;
		angs[i] = atan2l(y, x);
	}
	sort(angs.begin(), angs.end());
	long double dif = 0;
	for(int i = 0; i < n-1; ++i){
		dif = max(dif, angs[i+1] - angs[i]);
	}
	dif = max(dif, 2*pi - (angs.back() - angs[0]));
	long double ans = 2*pi - dif;
	cout << fixed << setprecision(10) << ans*180/pi << "\n";
	return 0;
}