#include <bits/stdc++.h>
using namespace std;
using lli = __uint128_t;

ostream &operator<<(ostream &os, const lli & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	lli tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

const lli inf = numeric_limits<lli>::max();
lli ten[10][39];

lli ans(int n, int lo, int hi){
	if(n <= 101) return n;
	lli res = inf;
	for(int a = 0; a <= 9; ++a){
		for(int b = 0; b <= 9; ++b){
			if(a == 0 && b == 0) continue;
			lli ans = inf;
			for(int sz = lo; sz <= hi; ++sz){
				lli ans_ = inf;
				for(lli msk = 0; msk < (1ll << sz); ++msk){
					lli tmp = 0;
					for(int d = 0; d < sz; ++d){
						if(msk & (1ll << d)){
							tmp += ten[a][d];
						}else{
							tmp += ten[b][d];
						}
					}
					if(tmp && tmp % n == 0){
						ans_ = min(ans_, tmp);
					}
				}
				if(ans_ != inf){
					ans = min(ans, ans_);
					break;
				}
			}
			res = min(res, ans);
		}
	}
	if(res == inf) return ans(n, hi+1, hi + to_string(n).size());
	return res;
}

lli ans(int n){
	return ans(n, to_string(n).size(), 2*to_string(n).size());
}

int main(){
	for(int i = 1; i <= 9; ++i){
		ten[i][0] = i;
	}
	for(int i = 1; i <= 38; ++i){
		ten[1][i] = ten[1][i-1] * 10;
		for(int j = 2; j <= 9; ++j){
			ten[j][i] = ten[1][i] * j;
		}
	}
	lli sum = 0;
	for(int i = 1; i <= 50000; ++i){
		lli di = ans(i);
		sum += di;
		cout << "f(" << i << ") = " << di << ", " << sum << "\n";
	}
	int lg = log10l(sum);
	cout << sum << "\n" << fixed << setprecision(12) << sum/powl(10, lg) << "e" << lg << "\n";
	return 0;
}