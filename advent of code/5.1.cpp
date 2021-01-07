#include <bits/stdc++.h>
using namespace std;

int conv(const string & s){
	int ans = 0;
	for(int i = 0; i < s.size(); ++i){
		if(s[i] == 'B' || s[i] == 'R'){
			ans += (1 << (s.size()-1 - i));
		}
	}
	return ans;
}

int main(){
	string seat;
	int ans = 0;
	while(cin >> seat){
		int row = conv(seat.substr(0, 7));
		int col = conv(seat.substr(7));
		int seat = row*8 + col;
		ans = max(ans, seat);
	}
	cout << ans << "\n";
	return 0;
}