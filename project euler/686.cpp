#include <bits/stdc++.h>
using namespace std;
using ld = long double;

ld frac(ld x){
	return x - floor(x);
}

int main(){
	int cnt = 0;
	for(long long int j = 1; ; ++j){
		if(floor(powl(10, 2 + frac(j*log10l(2)))) == 123){
			cnt++;
			if(cnt == 678910){
				cout << j << "\n";
				break;
			}
		}
	}
	return 0;
}