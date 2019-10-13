#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	vector<lli> t = {1, 4};
	vector<lli> b = {1, 3};
	int n = 1;
	while(1){
		n++;
		t.push_back(6*t[n-1]-t[n-2]-2);
		b.push_back(6*b[n-1]-b[n-2]-2);
		if(t[n] >= 1e12) break;
	}
	cout << b[n] << "\n";
	return 0;
}