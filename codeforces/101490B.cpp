#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	map<char, char> mapa = {{'R', 'S'}, {'B', 'K'}, {'L', 'H'}};
	string s, t;
	cin >> s;
	int n = s.size();
	for(int i = 0; i < n; ++i){
		set<char> tmp;
		if(i+2 < n){
			tmp = {s[i], s[i+1], s[i+2]};
		}
		if(tmp.size() == 3){
			t += 'C';
			i += 2;
		}else{
			t += mapa[s[i]];
		}
	}
	cout << t << "\n";
	return 0;
}