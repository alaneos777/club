#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, p, q, v;
	set<int> s;
	cin >> n;
	cin >> p;
	for(int i=0;i<p;i++){
		cin >> v;
		s.insert(v);
	}
	cin >> q;
	for(int i=0;i<q;i++){
		cin >> v;
		s.insert(v);
	}
	if(s.size() == n) cout << "I become the guy.";
	else cout << "Oh, my keyboard!";
	return 0;
}