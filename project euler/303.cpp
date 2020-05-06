#include <bits/stdc++.h>
using namespace std;
using lli = uint64_t;

const lli inf = numeric_limits<lli>::max();
lli ten[10][20];
lli three[20];

lli ans(int n){
	lli res = inf;
	if(n == 9999) return 1111333355557778ll * n;
	int len = to_string(n).size();
	for(int sz = len; sz <= 19; ++sz){
		lli ans = inf;
		for(lli msk = 0; msk < three[sz]; ++msk){
			lli tmp = 0;
			for(int i = 0; i < sz; ++i){
				int bit = msk / three[i] % 3;
				tmp += ten[bit][i];
			}
			if(tmp && tmp % n == 0){
				ans = min(ans, tmp);
			}
		}
		res = min(res, ans);
		if(res != inf){
			break;
		}
	}
	return res;
}

int main(){
	three[0] = 1;
	for(int i = 1; i <= 9; ++i){
		ten[i][0] = i;
	}
	for(int i = 1; i <= 19; ++i){
		three[i] = three[i-1] * 3;
		ten[1][i] = ten[1][i-1] * 10;
		for(int j = 2; j <= 9; ++j){
			ten[j][i] = ten[1][i] * j;
		}
	}
	lli sum = 0;
	for(int i = 1; i <= 10000; ++i){
		lli di = ans(i);
		sum += di/i;
		cout << "f(" << i << ") = " << di << ", " << sum << "\n";
	}
	cout << sum << "\n";
	return 0;
}