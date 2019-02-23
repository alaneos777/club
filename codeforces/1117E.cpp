#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

string ask(const string & s){
	cout << "? " << s << endl;
	string t;
	cin >> t;
	return t;
}

void answer(const string & s){
	cout << "! " << s << endl;
}

int main(){
	string t;
	cin >> t;
	int n = t.size();
	string a(n, ' '), b(n, ' '), c(n, ' '), s(n, ' ');
	for(int i = 0; i < n; ++i){
		a[i] = (i/1)%26 + 'a';
		b[i] = (i/26)%26 + 'a';
		c[i] = (i/676)%26 + 'a';
	}
	a = ask(a);
	b = ask(b);
	c = ask(c);
	for(int i = 0; i < n; ++i){
		s[(a[i]-'a') + (b[i]-'a')*26 + (c[i]-'a')*676] = t[i];
	}
	answer(s);
	return 0;
}