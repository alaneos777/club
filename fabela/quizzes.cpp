#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, x;
	string s;
	cin >> n >> x >> s;
	for(char c : s){
		if(c == 'o') x++;
		else{
			if(x > 0) x--;
		}
	}
	cout << x << "\n";
	return 0;
}