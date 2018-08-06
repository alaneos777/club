#include <bits/stdc++.h>

using namespace std;

int main(){
	int n;
	int x = 0, y = 0, z = 0, xi, yi, zi;
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> xi >> yi >> zi;
		x += xi, y += yi, z += zi;
	}
	if(x == 0 && y == 0 && z == 0) cout << "YES";
	else cout << "NO";
	return 0;
}