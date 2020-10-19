#include <iostream>
using namespace std;
using lli = int64_t;

int main(){
	int N = 1e7;
	--N;
	lli ans = 0;
	for(int k = 1; k <= N; ++k){
		lli nk = N/k;
		ans += (-k * nk * nk + (2*N - k + 2) * nk)/2;
	}
	cout << ans << "\n";
	return 0;
}