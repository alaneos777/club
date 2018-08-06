#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, d, ti, total = 0;
	cin >> n >> d;
	for(int i = 0; i < n; i++){
		cin >> ti;
		total += ti;
	}
	if((total + (n - 1) * 10) > d){
		cout << "-1";
	}else{
		cout << ((d - total) / 5);
	}
	return 0;
}