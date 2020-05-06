#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli mem[18][163][163][137];

int digit_sum(int n){
	int ans = 0;
	while(n){
		ans += n%10;
		n /= 10;
	}
	return ans;
}

const int len = 18;

lli dp(int idx, int sum, int sum2, int carry){
	if(idx == len){
		if(sum == sum2 + digit_sum(carry)){
			return 1;
		}else{
			return 0;
		}
	}
	if(mem[idx][sum][sum2][carry] != -1) return mem[idx][sum][sum2][carry];
	lli ans = 0;
	for(int d = 0; d <= 9; ++d){
		ans += dp(idx + 1, sum + d, sum2 + (carry + 137*d)%10, (carry + 137*d)/10);
	}
	return mem[idx][sum][sum2][carry] = ans;
}

int main(){
	memset(mem, -1, sizeof(mem));
	cout << dp(0, 0, 0, 0) << "\n";
	return 0;
}