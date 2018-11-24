#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	set<string> unique;
	for(int i = 0; i < n; ++i){
		string str;
		cin >> str;
		int pos = str.find("@");
		string part1 = str.substr(0, pos);
		string domain = str.substr(pos + 1);
		string username = "";
		for(char c : part1){
			if(c == '+') break;
			if(c != '.'){
				username += string(1, c);
			}
		}
		unique.insert(username + "@" + domain);
	}
	cout << unique.size() << "\n";
	return 0;
}