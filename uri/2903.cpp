#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string r, n;
	cin >> r;
	for(char c : r){
		if(c != '.')
			n += string(1, c);
	}
	int R = stoi(n);
	cout << 36000 / __gcd(36000, R) << "\n";
	return 0;
}