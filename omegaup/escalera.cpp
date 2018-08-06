#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int n, k;
vector<lli> mem;

lli ans(int pos){
	if(pos > n){
		return 0;
	}else if(pos == n){
		return 1;
	}else{
		if(mem[pos] == -1){
			lli sum = 0;
			for(int i = 1; i <= k; i++){
				sum += ans(pos + i);
			}
			mem[pos] = sum;
		}
		return mem[pos];
	}
}

int main(){
	cin >> n >> k;
	mem.resize(n + 1, -1);
	cout << ans(0) << "\n";
}