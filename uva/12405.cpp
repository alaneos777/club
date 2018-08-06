#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	int t, c = 1;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<char> piso(n + 2);
		for(int i = 0; i < n; i++){
			cin >> piso[i];
		}
		piso[n] = piso[n + 1] = '#';
		int ans = 0;
		bool between = false;
		int i = 0;
		while(i < n){
			if(piso[i] == '.'){
				if((piso[i + 1] == '.' && piso[i + 2] == '.') || (piso[i + 1] == '#' && piso[i + 2] == '.') || (piso[i + 1] == '#' && piso[i + 2] == '#') || (piso[i + 1] == '.' && piso[i + 2] == '#')){
					ans++;
					i += 3;
				}
			}else{
				i++;
			}
		}
		cout << "Case " << (c++) << ": " << ans << "\n";
	}
	return 0;
}