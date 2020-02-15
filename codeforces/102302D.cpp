#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s, t;
	cin >> s >> t;
	int i = 0, j = 0;
	for(; i < s.size() && j < t.size(); ++i){
		if(s[i] == t[j]) ++j;
	}
	if(j == t.size()){
		cout << "YES\n";
	}else{
		cout << "NO\n";
	}
	return 0;
}