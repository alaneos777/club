#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	lli N = lli(1e17) - 1;
	vector<lli> fib = {1, 2};
	while(fib.back() <= N){
		fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
	}
	while(fib.back() > N) fib.pop_back();
	vector<lli> block = {0, 1, 2, 5};
	while(block.size() < fib.size()){
		block.push_back(2*block[block.size()-1] + block[block.size()-2] - 2*block[block.size()-3] - block[block.size()-4]);
	}
	int b = upper_bound(fib.begin(), fib.end(), N+1) - fib.begin();
	b--;
	lli ans = block[b];
	N -= fib[b]-1;
	int cnt = 0;
	while(N){
		b = upper_bound(fib.begin(), fib.end(), N) - fib.begin();
		b--;
		N -= fib[b];
		ans += block[b+2] - block[b+1] + fib[b]*cnt;
		//cout << N << " " << b << " " << fib[b] << " " << block[b+2] - block[b+1] + fib[b]*cnt << "\n";
		cnt++;
	}
	cout << ans << "\n";
	return 0;
}