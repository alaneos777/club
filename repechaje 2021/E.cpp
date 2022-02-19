#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, m; char c;
	int caso = 1;
	while(cin >> n){
		if(n == -1) break;
		cin >> m >> c;
		vector<lli> steps;
		cout << "Case " << caso++ << ": " << n << " x " << m << " = ";
		if(n == 0 || m == 0){
			cout << "0\n";
			continue;
		}
		lli ans = 0;
		while(n){
			if(n & 1){
				ans += m;
				steps.push_back(m);
			}
			n >>= 1;
			m *= 2;
		}
		if(c == 'b'){
			reverse(steps.begin(), steps.end());
		}
		for(int i = 0; i < steps.size(); ++i){
			cout << steps[i];
			if(i+1 != steps.size()) cout << " + ";
		}
		cout << "\n";
	}
	return 0;
}