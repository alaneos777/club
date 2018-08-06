#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

int main(){
	ios_base::sync_with_stdio(0);
	int t;
	ull g, l;
	cin >> t;
	while(t--){
		cin >> g >> l;
		if(l % g == 0){
			cout << g << " " << l << "\n";
		}else{
			cout << "-1\n";
		}
	}
	return 0;
}