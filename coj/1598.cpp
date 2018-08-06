#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int f0, f1, f2;
	while(cin >> f0 >> f1 >> f2){
		int dif1 = f1 - f0;
		int dif2 = f2 - 2 * f1 + f0;
		int a = dif2 / 2, b = dif1 - a, c = f0;
		int f3 = 9 * a + 3 * b + c;
		int f4 = 16 * a + 4 * b + c;
		int f5 = 25 * a + 5 * b + c;
		cout << f3 << " " << f4 << " " << f5 << "\n";
	}
	return 0;
}