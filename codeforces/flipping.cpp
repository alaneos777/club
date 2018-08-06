#include <bits/stdc++.h>
using namespace std;

vector<vector<double>> f;
int c, k;

double answer(int coins, int rem){
	if(rem == 0)
		return coins;
	double & ans = f[coins][rem];
	if(ans != -1)
		return ans;
	if(coins == c)
		ans = (answer(coins, rem - 1) + answer(coins - 1, rem - 1)) / 2.0;
	else
		ans = (answer(coins, rem - 1) + answer(coins + 1, rem - 1)) / 2.0;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> c >> k;
	f.resize(c + 1, vector<double>(k + 1, -1));
	cout << fixed << setprecision(10) << answer(0, k) << "\n";
	return 0;
}