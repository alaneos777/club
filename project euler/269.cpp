#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

bool check(lli n, int r){
	lli eval = 0;
	lli r_pow = 1;
	while(n){
		lli d = n % 10;
		eval += d * r_pow;
		r_pow *= r;
		n /= 10;
	}
	//if(eval) assert(!(eval % 1009 == 0 && eval % 1013 == 0 && eval % 101 == 0));
	return eval == 0;
}

int main(){
	int cnt = 0;
	for(lli n = 1; n <= 1e8; ++n){
		//if(n % 10 == 0) continue;
		bool ans = 0;
		for(int r = 0; r <= 9; ++r){
			if(check(n, -r)){
				ans = 1;
				break;
			}
		}
		cnt += ans;
	}
	cout << cnt << "\n";
	return 0;
}