#include <bits/stdc++.h>
using namespace std;

bool vocal(char c){
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool cons(char c){
	return !vocal(c);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s, t;
	cin >> s >> t;
	if(s.size() != t.size()){
		cout << "No\n";
		return 0;
	}
	bool test = true;
	for(int i = 0; i < s.size(); ++i){
		if((vocal(s[i]) && vocal(t[i])) || (cons(s[i]) && cons(t[i]))){
			test = test & true;
		}else{
			test = test & false;
		}
	}
	if(test) cout << "Yes\n";
	else cout << "No\n";
	return 0;
}