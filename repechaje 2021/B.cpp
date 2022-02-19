#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	int caso = 1;
	while(t--){
		cout << "Case " << caso++ << ": ";
		int cnt = 20;
		int i = 0;
		int acum = 0;
		while(i < cnt){
			char a, b, c;
			cin >> a >> b;
			assert(a == '(');
			int d = 0;
			if(b == '*'){
				cin >> c;
				d = 1;
			}
			acum = acum*2 + d;
			if(i == 1 || i == 5 || i == 8 || i == 12 || i == 15 || i == 19){
				cout << acum;
				acum = 0;
				if(i == 5 || i == 12 || i == 19){
					if(i != 19) cout << ":";
				}
			}
			i++;
		}
		cout << "\n";
	}
	return 0;
}