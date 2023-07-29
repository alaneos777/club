#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	bool correct = true;
	for(int i = 0; i < 8; ++i){
		int ni;
		cin >> ni;
		correct &= (ni != 9);
	}
	if(correct) cout << "S\n";
	else cout << "F\n";
	return 0;
}