#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	int p;
	cin >> p;
	int n = p/2;
	double ans = 0.0;
	for(int i = 1; i <= n; ++i){
		ans += (2.0*i - 1.0) / (2.0*i + 1.0);
	}
	cout << fixed << setprecision(3) << ans << "\n";
	return 0;
}