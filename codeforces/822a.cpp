#include <bits/stdc++.h>
using namespace std;

int main(){
	long int a, b, ans = 1;
	cin >> a >> b;
	for(long int i = 2; i <= min(a, b); i++){
		ans *= i;
	}
	cout << ans;
	return 0;
}