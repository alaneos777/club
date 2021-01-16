#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
		if(ai >= 0){
			ai = -ai - 1;
		}
	}
	if(n & 1){
		int i = min_element(a.begin(), a.end()) - a.begin();
		a[i] = -a[i] - 1;
	}
	for(int ai : a){
		cout << ai << " ";
	}
	cout << "\n";
	return 0;
}