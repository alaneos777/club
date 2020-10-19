#include <bits/stdc++.h>
using namespace std;

bool is(char c){
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	string s, ans;
	cin >> n >> s;
	int cnt = 0;
	for(char c : s){
		if(is(c)){
			cnt++;
			if(cnt == 1){
				ans += c;
			}
		}else{
			cnt = 0;
			ans += c;
		}
	}
	cout << ans << "\n";
	return 0;
}