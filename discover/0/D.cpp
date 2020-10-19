#include <bits/stdc++.h>
using namespace std;

int main(){
	//ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	int l = 1, r = n, ans;
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