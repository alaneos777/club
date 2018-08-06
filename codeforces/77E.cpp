#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin >> t;
	while(t--){
		long double R, r, k;
		cin >> R >> r >> k;
		cout << fixed << setprecision(10) << R*r*(R-r)/(R*r+k*k*(R-r)*(R-r)) << "\n";
	}
	return 0;
}