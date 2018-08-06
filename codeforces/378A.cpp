#include <bits/stdc++.h>
using namespace std;

int main(){
	int a, b;
	cin >> a >> b;
	int ans1 = 0, ans2 = 0, ans3 = 0;
	for(int x = 1; x <= 6; x++){
		if(abs(a - x) < abs(b - x)) ans1++;
		if(abs(a - x) == abs(b - x)) ans2++;
		if(abs(a - x) > abs(b - x)) ans3++;
	}
	cout << ans1 << " " << ans2 << " " << ans3;
	return 0;
}