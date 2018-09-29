#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	double r;
	cin >> n >> r;
	double PI = 3.14159265;
	cout << fixed << setprecision(4) << r * (1.0 / sin(PI / n) - 1) << "\n";
	return 0;
}