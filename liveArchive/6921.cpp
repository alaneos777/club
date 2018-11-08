#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		double w, H, x0, xe, ye, mu;
		cin >> w >> H >> x0 >> xe >> ye >> mu;
		double alpha = atan((xe - w) / (ye - H));
		double beta = asin(sin(alpha) / mu);
		double h = (x0 + H * tan(alpha) - w) / (tan(alpha) - tan(beta));
		if(h > -eps && (h - H) < eps){
			cout << fixed << setprecision(4) << h << "\n";
		}else{
			cout << "Impossible\n";
		}
	}
	return 0;
}