#include <bits/stdc++.h>
using namespace std;
using ld = long double;

/*const int M = 45;
double mem[M+1][M+1][M+1][M+1][M+1];
bool calc[M+1][M+1][M+1][M+1][M+1];

double f(int a, int b, int c, int d, int e){
	if(a > 0 && b > 0 && c > 0 && d > 0 && e > 0) return 0;
	if(a > M || b > M || c > M || d > M || e > M) return 0;
	double & ans = mem[a][b][c][d][e];
	if(calc[a][b][c][d][e]) return ans;
	calc[a][b][c][d][e] = true;
	return ans = 1 + 0*(a+b+c+d+e) + (f(a+1, b, c, d, e) + f(a, b+1, c, d, e) + f(a, b, c+1, d, e) + f(a, b, c, d+1, e) + f(a, b, c, d, e+1)) / 5;
}*/

const int N = 1e8;

ld f(int n){
	ld s = 0, ans = 0;
	for(int i = 1; i <= n; ++i){
		s += 1.0l / i;
		ans += s / i;
	}
	return ans * n;
}

int main(){
	cout << fixed << setprecision(10) << f(N) << endl;
	return 0;
}