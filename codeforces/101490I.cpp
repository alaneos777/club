#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	vector<pair<int, int>> f;
	for(int i = 2; i * i <= n; ++i){
		int pot = 0;
		while(n % i == 0){
			pot++;
			n /= i;
		}
		if(pot) f.emplace_back(i, pot);
	}
	if(n > 1) f.emplace_back(n, 1);
	if(f.size() == 1){
		cout << "yes\n";
	}else{
		cout << "no\n";
	}
	return 0;
}