#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	int ans = -1;
	int l = 1, r = n;
	while(l <= r){
		int m = (l + r) / 2;
		cout << "? " << m << endl;
		string res;
		cin >> res;
		if(res == ">="){
			ans = m;
			l = m+1;
		}else{
			r = m-1;
		}
	}
	cout << "! " << ans << endl;
	return 0;
}