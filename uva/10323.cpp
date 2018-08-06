#include <bits/stdc++.h>
using namespace std;
int main(){
	ios_base::sync_with_stdio(0);
	int n;
	while(cin >> n){
		if((0 <= n && n <= 7) || (n < 0 && n % 2 == 0)) cout << "Underflow!";
		else if(n == 8) cout << "40320";
		else if(n == 9) cout << "362880";
		else if(n == 10) cout << "3628800";
		else if(n == 11) cout << "39916800";
		else if(n == 12) cout << "479001600";
		else if(n == 13) cout << "6227020800";
		else cout << "Overflow!";
		cout << "\n";
	}
	return 0;
}