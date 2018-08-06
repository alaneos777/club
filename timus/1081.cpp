#include <bits/stdc++.h>
using namespace std;

vector<int> F(47);

int nearestF(int Fn){
	if(Fn == 1) return 2;
	int i = lower_bound(F.begin(), F.end(), Fn) - F.begin();
	if(F[i] != Fn) i--;
	return i;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	F[0] = 0, F[1] = 1;
	for(int i = 2; i <= 46; i++){
		F[i] = F[i - 1] + F[i - 2];
	}
	int n, k;
	cin >> n >> k;
	string ans = "";
	ans.append(n, '0');
	k--;
	if(k >= F[n + 2]){
		cout << "-1\n";
	}else{
		while(k > 0){
			int i = nearestF(k);
			ans[n - 1 - (i - 2)] = '1';
			k -= F[i];
		}
		cout << ans << "\n";
	}
	return 0;
}