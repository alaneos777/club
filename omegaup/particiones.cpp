#include <bits/stdc++.h>
using namespace std;
typedef int lli;

vector<lli> P;

lli partitionsP(int n){
	if(n < 0) return 0;
	if(P[n]) return P[n];
	int pos1 = 1, pos2 = 2, inc1 = 4, inc2 = 5;
	lli ans = 0;
	for(int k = 1; k <= n; k++){
		lli tmp = (n >= pos1 ? P[n - pos1] : 0) + (n >= pos2 ? P[n - pos2] : 0);
		if(k & 1) ans += tmp;
		else ans -= tmp;
		if(n < pos2) break;
		pos1 += inc1, pos2 += inc2;
		inc1 += 3, inc2 += 3;
	}
	return ans;
}

void calculateFunctionP(int n){
	P.resize(n + 1);
	P[0] = 1;
	for(int i = 1; i <= n; i++)
		P[i] = partitionsP(i);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n;
	cin >> n;
	calculateFunctionP(n);
	cout << P[n] << "\n";
	return 0;
}