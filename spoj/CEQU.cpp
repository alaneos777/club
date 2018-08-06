#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b){
	int r;
	while(b != 0){
		r = a % b, a = b, b = r;
	}
	return a;
}

int main(){
	ios_base::sync_with_stdio(0);
	int t, a, b, c;
	cin >> t;
	for(int i = 1; i <= t; i++){
		cin >> a >> b >> c;
		cout << "Case " << i << ": ";
		if(c % gcd(a, b) == 0){
			cout << "Yes\n";
		}else{
			cout << "No\n";
		}
	}
	return 0;
}