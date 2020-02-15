#include <bits/stdc++.h>
using namespace std;

const int p1 = 1009, p2 = 3643;
const int n = p1 * p2;
const int phi = (p1 - 1) * (p2 - 1);

int count(int e){
	int lhs = 1 + __gcd(p1 - 1, e - 1);
	int rhs = 1 + __gcd(p2 - 1, e - 1);
	return lhs * rhs;
}

int main(){
	int64_t sum = 0;
	int mini = 1<<30;
	for(int e = 2; e < phi; ++e){
		if(__gcd(e, phi) != 1) continue;
		int tmp = count(e);
		if(tmp < mini){
			mini = tmp;
			sum = e;
		}else if(tmp == mini){
			sum += e;
		}
	}
	cout << mini << " " << sum << "\n";
	return 0;
}