#include <bits/stdc++.h>
using namespace std;

bool IsZero(double x){
	return abs(x) < 1e-9;
}

double solucion(int p, int q, int r, int s, int t, int u){
	double a = 0, b = 1, x;
	while(a < b){
		x = (a + b) / 2;
		double m = p * exp(-x) + r * cos(x);
		double n = q * sin(x) + s * tan(x) + t * x * x;
		if(IsZero(m + n + u)){
			return x;
		}else if(m + n + u < 0){
			b = x;
		}else{
			a = x;
		}
	}
	return -1;
}

int main(){
	ios_base::sync_with_stdio(0);
	int p, q, r, s, t, u;
	while(cin >> p >> q >> r >> s >> t >> u){
		double ans = solucion(p, q, r, s, t, u);
		if(ans == -1){
			cout << "No solution\n";
		}else{
			cout << fixed << setprecision(4) << ans << "\n";
		}
	}
	return 0;
}