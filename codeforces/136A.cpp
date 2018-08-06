#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, tmp;
	cin >> n;
	vector<int> info(n+1);
	for(int i=1;i<=n;i++){
		cin >> tmp;
		info[tmp] = i;
	}
	for(int i=1;i<=n;i++) cout << info[i] << " ";
	return 0;
}