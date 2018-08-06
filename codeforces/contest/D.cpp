#include <bits/stdc++.h>
using namespace std;

int mod(int a, int b){
	int r = a % b;
	if(r < 0) r += b;
	return r;
}

int main(){
	int n, k;
	cin >> n >> k;
	vector<int> acum(200);
	int pos = 0;
	while(k--){
		string command;
		cin >> command;
		if(command == "undo"){
			int m;
			cin >> m;
			pos -= m;
		}else{
			int p;
			stringstream(command) >> p;
			acum[pos + 1] = mod(acum[pos] + p, n);
			pos++;
		}
	}
	cout << acum[pos] << "\n";
	return 0;
}