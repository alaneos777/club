#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	string s;
	cin >> n >> s;
	s += 'b';
	int run = 0, ans = 0;
	for(int i = 0; i <= n; ++i){
		if(s[i] == 'a'){
			run++;
		}else{
			ans += run>=2 ? run : 0;
			run = 0;
		}
	}
	cout << ans << "\n";
	return 0;
}