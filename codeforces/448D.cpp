#include <iostream>
#include <algorithm>
using namespace std;
typedef long long lli;

void S(lli m, lli n, lli x, lli & k1, lli & k2){
	lli sum = 0, rep = 0, q, r;
	for(lli i = 1; i <= m; i++){
		q = x / i;
		if(q <= n && (x % i == 0)){
			rep++;
		}
		sum += min(n, q);
	}
	k1 = sum - rep + 1, k2 = sum;
}

lli ans(lli m, lli n, lli k){
	lli left = 1, right = m * n, x, k1, k2;
	while(left <= right){
		x = (left + right) >> 1;
		S(m, n, x, k1, k2);
		if(k1 <= k && k <= k2){
			return x;
		}else if(k2 >= k){
			right = x - 1;
		}else if(k1 <= k){
			left = x + 1;
		}
	}
}

int main(){
	lli m, n, k;
	cin >> m >> n >> k;
	if(m > n) swap(m, n);
	cout << ans(m, n, k) << "\n";
	return 0;
}