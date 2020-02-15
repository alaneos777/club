#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli a, b;
	cin >> a >> b;
	set<lli> st;
	for(lli d = 1; d*d <= a; ++d){
		if(a % d != 0) continue;
		if(d % b == 0) st.insert(d);
		lli e = a/d;
		if(e % b == 0) st.insert(e);
	}
	for(lli x : st){
		cout << x << " ";
	}
	cout << "\n";
	return 0;
}