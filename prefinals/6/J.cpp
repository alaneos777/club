#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	int x = 1;
	while((1 << x)+1 <= n){
		x++;
	}
	--x;
	int a = (1<<x)+1, b = (1<<x) + (1<<(x-1)), c = b+1, d = (1<<(x+1));
	if(a <= n && n <= b){
		cout << 2*(x-1) << "\n";
	}else{
		cout << 2*x-1 << "\n";
	}
	return 0;
}