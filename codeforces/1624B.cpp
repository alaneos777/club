#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli a, b, c;
		cin >> a >> b >> c;
		// a+c = 2b
		// am+c = 2b -> m=(2b-c)/a
		// a+cm = 2b -> m=(2b-a)/c
		// a+c = 2bm -> m=(a+c)/(2b)
		if(((2*b-c)%a == 0 && (2*b-c)/a > 0) || ((2*b-a)%c == 0 && (2*b-a)/c > 0) || ((a+c)%(2*b) == 0 && (a+c)/(2*b) > 0)){
			cout << "YES\n";
		}else{
			cout << "NO\n";
		}
	}
	return 0;
}