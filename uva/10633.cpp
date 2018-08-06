#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

ull techo(ull num, ull den){
	if(num % den == 0)
		return num / den;
	else
		return num / den + 1;
}

int main(){
	ios_base::sync_with_stdio(0);
	ull d, lower, upper, n;
	while(true){
		cin >> d;
		if(d == 0) break;
		lower = techo(8 * d, 9);
		upper = 1 + 8 * d / 9;
		bool first = true;
		for(ull k = upper; k >= lower; --k){
			n = 2 * d - k;
			if(first){
				first = false;
			}else{
				cout << " ";
			}
			cout << n;
		}
		cout << "\n";
	}
	return 0;
}