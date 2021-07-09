#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int nxt(int n){
	n++;
	while(n % 10 == 0) n /= 10;
	return n;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	set<int> vis;
	while(1){
		vis.insert(n);
		n = nxt(n);
		if(vis.count(n)) break;
	}
	cout << vis.size() << "\n";
	return 0;
}