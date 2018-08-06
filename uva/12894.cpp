#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	int t;
	cin >> t;
	int x0, y0, x1, y1, h, k, r;
	while(t--){
		cin >> x0 >> y0 >> x1 >> y1 >> h >> k >> r;
		int l = x1 - x0, w = y1 - y0;
		if((3 * l == 5 * w) && (l == 5 * r) && (20 * x0 + 9 * l == 20 * h) && (2 * y0 + w == 2 * k)){
			cout << "YES\n";
		}else{
			cout << "NO\n";
		}
	}
	return 0;
}