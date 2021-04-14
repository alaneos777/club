#include <bits/stdc++.h>
using namespace std;

auto isSieve(int n){
	vector<bool> is(n+1, true);
	is[0] = is[1] = false;
	for(int i = 2; i*i <= n; ++i){
		if(is[i]){
			for(int j = i*i; j <= n; j += i){
				is[j] = false;
			}
		}
	}
	return is;
}

const auto is = isSieve(1e6);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	int x = 2, y = n-2;
	while(is[x] || is[y]){
		x++;
		y--;
	}
	cout << x << " " << y << "\n";
	return 0;
}