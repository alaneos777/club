#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, alpha;
	cin >> n >> alpha;
	int rhs = alpha*n / 180.0;
	int mini = 1e9, diff;
	for(int x = max(1, rhs-2); x <= min(rhs+2, n-2); ++x){
		if(abs(alpha*n - 180*x) < mini){
			mini = abs(alpha*n - 180*x);
			diff = x;
		}
	}
	cout << 2 << " " << 1 << " " << diff+2 << "\n";
	return 0;
}