#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, t, pos = 1;
	cin >> n >> t;
	vector<int> info(n);
	for(int i = 1; i <= n - 1; i++){
		cin >> info[i];
	}
	while(pos < t){
		pos = pos + info[pos];
	}
	if(pos == t) cout << "YES";
	else cout << "NO";
	return 0;
}