#include <bits/stdc++.h>
using namespace std;

int sum(int n){
	int ans = 0;
	while(n > 0){
		int d = n % 10;
		ans += d * d;
		n /= 10;
	}
	return ans;
}

int limit = 1e7;
vector<int> chain(limit + 1, 0);

int ans(int n){
	int n0 = n;
	while(n != 1 && n != 89){
		if(chain[n] > 0){
			n = chain[n];
			break;
		}else{
			n = sum(n);
		}
	}
	chain[n0] = n;
	return n;
}

int main(){
	int count = 0;
	for(int i = 1; i <= limit; i++){
		if(ans(i) == 89) count++;
	}
	cout << count << "\n";
	return 0;
}