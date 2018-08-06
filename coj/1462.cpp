#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	string str;
	int sum = 0, x;
	while(n--){
		cin >> str;
		if(str.size() > 7){
			str = str.substr(str.size() - 7, 7);
		}
		stringstream(str) >> x;
		sum += x;
	}
	cout << (sum & ((1 << 7) - 1)) << "\n";
	return 0;
}