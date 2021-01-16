#include <bits/stdc++.h>
using namespace std;

const int MX = 4000;
vector<int> mem(MX + 1);
vector<bool> calc(MX + 1);
int a, b, c;
int infinity = 1e9;

int f(int n){
	if(n == 0) return 0;
	if(n < a && n < b && n < c) return -infinity;
	if(calc[n]){
		return mem[n];
	}
	int ans = -infinity;
	if(n-a >= 0) ans = max(ans, f(n-a));
	if(n-b >= 0) ans = max(ans, f(n-b));
	if(n-c >= 0) ans = max(ans, f(n-c));
	mem[n] = 1 + ans;
	calc[n] = true;
	return mem[n];
}

int main(){
	int n;
	cin >> n >> a >> b >> c;
	cout << f(n) << "\n";
	return 0;
}