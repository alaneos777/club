#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, m;
	cin >> n >> m;
	while(n != 0 && m != 0){
		if(n >= 2*m){
			// n >= 2*m*k --> k <= floor(n/(2*m))
			n -= (n/(2*m)) * 2*m;
		}else if(m >= 2*n){
			m -= (m/(2*n)) * 2*n;
		}else{
			break;
		}
	}
	cout << n << " " << m << "\n";
	return 0;
}