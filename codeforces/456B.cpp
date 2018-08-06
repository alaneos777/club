#include <bits/stdc++.h>

using namespace std;

int main(){
	string s;
	stringstream ss;
	int n, ans;
	cin >> s;
	if(s.size() <= 2){
		ss << s;
	}else{
		ss << s[s.size() - 2] << s[s.size() - 1];
	}
	ss >> n;
	n = n % 4;
	ans = 1 + pow(2, n) + pow(3, n) + pow(4, n);
	cout << (ans % 5);
	return 0;
}