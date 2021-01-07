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
		ans += ((pass[l-1] == letter) ^ (pass[r-1] == letter));
	}
	cout << ans << "\n";
	return 0;
}