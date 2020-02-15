#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	auto b = a;
	sort(b.begin(), b.end());
	int l = n, r = -1;
	for(int i = 0; i < n; ++i){
		if(a[i] != b[i]){
			l = min(l, i);
			r = max(r, i);
		}
	}
	if(r == -1){
		cout << "yes\n1 1\n";
	}else{
		reverse(b.begin() + l, b.begin() + r + 1);
		if(a == b){
			cout << "yes\n" << l+1 << " " << r+1 << "\n";
		}else{
			cout << "no\n";
		}
	}
	return 0;
}