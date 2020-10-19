#include <bits/stdc++.h>
using namespace std;

int mem[11][200][2];

int f(int pos, int diff, bool canUseAll, const string & num){
	if(pos == num.size()){
		return diff == 1;
	}
	int & ans = mem[pos][diff + 100][canUseAll];
	if(ans != -1) return ans;
	ans = 0;
	int limit = canUseAll ? 9 : num[pos] - '0';
	for(int d = 0; d <= limit; ++d){
		int newDiff = diff;
		if(((int)num.size() - pos) % 2 == 0){
			newDiff += d;
		}else{
			newDiff -= d;
		}
		ans += f(pos + 1, newDiff, canUseAll | d != limit, num);
	}
	return ans;
}

int f(int n){
	memset(mem, -1, sizeof(mem));
	string num = to_string(n);
	return f(0, 0, false, num);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int l, r;
		cin >> l >> r;
		int ans = f(r);
		if(l) ans -= f(l-1);
		cout << ans << "\n";
	}
	return 0;
}