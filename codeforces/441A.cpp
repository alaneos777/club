#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, v, ki, sij;
	cin >> n >> v;
	vector<int> ans;
	for(int i = 0; i < n; i++){
		cin >> ki;
		bool trato = false;
		for(int j = 0; j < ki; j++){
			cin >> sij;
			trato = trato || (v > sij);
		}
		if(trato) ans.push_back(i + 1);
	}
	cout << ans.size() << "\n";
	for(size_t i = 0; i < ans.size(); i++) cout << ans[i] << " ";
	return 0;
}