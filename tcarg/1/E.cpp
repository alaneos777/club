#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int ask(int i, int j){
	cout << "? " << i+1 << " " << j+1 << endl;
	int s;
	cin >> s;
	return s;
}

int main(){
	int n;
	cin >> n;
	vector<int> ans(n);
	int c = ask(0, 1);
	int b = ask(0, 2);
	int a = ask(1, 2);
	ans[0] = (-a + b + c) / 2;
	ans[1] = (a - b + c) / 2;
	ans[2] = (a + b - c) / 2;
	for(int i = 3; i < n; ++i){
		ans[i] = ask(0, i) - ans[0];
	}
	cout << "!";
	for(int ai : ans){
		cout << " " << ai;
	}
	cout << endl;
	return 0;
}