#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<lli> mem;

bool isPerfectSquare(int n){
	int r = sqrt(n);
	return r * r == n;
}

int s(int n){
	int r = 1 + 24 * n;
	if(isPerfectSquare(r)){
		int j;
		r = sqrt(r);
		if((r + 1) % 6 == 0) j = (r + 1) / 6;
		else j = (r - 1) / 6;
		if(j & 1) return -1;
		else return 1;
	}else{
		return 0;
	}
}

lli Q(int n){
	if(n < 0) return 0;
	else if(n == 0 || n == 1) return 1;
	else{
		if(mem[n] == -1){
			lli sum = 0;
			int alt = 1;
			int r = sqrt(n);
			for(int k = 1; k <= r; k++){
				sum += alt * Q(n - k * k);
				alt *= -1;
			}
			sum <<= 1;
			sum += s(n);
			mem[n] = sum;
		}
		return mem[n];
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	mem.resize(n + 1, -1);
	cout << Q(n) - 1;
	return 0;
}