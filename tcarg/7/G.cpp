#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, a, b;
	cin >> n >> a >> b;
	vector<lli> hp(n), dmg(n);
	for(int i = 0; i < n; ++i){
		cin >> hp[i] >> dmg[i];
	}
	vector<int> pos(n);
	iota(pos.begin(), pos.end(), 0);
	sort(pos.begin(), pos.end(), [&](int i, int j){
		int lhs = hp[i]-dmg[i];
		int rhs = hp[j]-dmg[j];
		if(lhs != rhs) return lhs > rhs;
		return i < j;
	});
	auto f = [&](int i){
		return hp[i] <= dmg[i] ? dmg[i] : hp[i];
	};
	lli ans = 0, sum = 0;
	for(int i = 0; i < n; ++i){
		int id = pos[i];
		if(i < b) sum += f(id);
		else sum += dmg[id];
	}
	ans = sum;
	if(b == 0){
		cout << ans << "\n";
	}else{
		for(int i = 0; i < n; ++i){
			int id = pos[i];
			lli tmp = sum;
			if(i < b){
				tmp -= f(id);
				tmp += (hp[id]<<a);
				ans = max(ans, tmp);
			}else{
				tmp -= dmg[id];
				tmp += (hp[id]<<a);
				int ID = pos[b-1];
				tmp -= f(ID);
				tmp += dmg[ID];
				ans = max(ans, tmp);
			}
		}
		cout << ans << "\n";
	}
	return 0;
}