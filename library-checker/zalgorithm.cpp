#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(const string & s){
	int n = s.size();
	vector<int> z(n);
	for(int i = 1, l = 0, r = 0; i < n; ++i){
		if(i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while(i + z[i] < n && s[z[i]] == s[i + z[i]])
			++z[i];
		if(i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	return z;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s;
	cin >> s;
	auto z = z_function(s);
	z[0] = s.size();
	for(int zi : z){
		cout << zi << " ";
	}
	cout << "\n";
	return 0;
}