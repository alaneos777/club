#include <bits/stdc++.h>
using namespace std;

const regex pattern("(\\d+)-(\\d+)\\s([a-z]):\\s([a-z]+)");

int main(){
	string linea;
	int ans = 0;
	while(getline(cin, linea)){
		smatch m;
		regex_search(linea, m, pattern);
		int l = stoi(m[1]), r = stoi(m[2]);
		char letter = m.str(3)[0];
		string pass = m[4];
		int cnt = 0;
		for(char c : pass){
			cnt += (c == letter);
		}
		ans += (l <= cnt && cnt <= r);
	}
	cout << ans << "\n";
	return 0;
}