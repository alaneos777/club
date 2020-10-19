#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

lli mem[40][40][40][40][2][2];

bool small[40];

lli f(int pos, int a, int b, int c, bool canUseAll, bool prefixZeros, const vector<int> & num){
	if(pos == num.size()){
		return small[a] && small[b] && small[c];
	}
	lli & ans = mem[pos][a][b][c][canUseAll][prefixZeros];
	if(ans != -1) return ans;
	ans = 0;
	int start = prefixZeros ? 0 : 1;
	int lim = canUseAll ? 3 : num[pos];
	for(int d = start; d <= lim && d <= 3; ++d){
		ans += f(pos+1, a + (d == 1), b + (d == 2), c + (d == 3), canUseAll | (d < lim), prefixZeros & (d == 0), num);
	}
	return ans;
}

const lli mod = 123123123;

int main(){
	for(int x : {0,1,2,3,11,12,13,21,22,23,31,32,33}){
		small[x] = true;
	}
	lli N = 111111111111222333ll;
	lli l = 1, r = lli(1e19) * lli(1e19), ans = -1;
	while(l <= r){
		lli m = l + (r - l) / 2;
		memset(mem, -1, sizeof(mem));
		lli m_ = m;
		vector<int> num;
		while(m_){
			num.push_back(m_ % 10);
			m_ /= 10;
		}
		reverse(num.begin(), num.end());
		lli cnt = f(0, 0, 0, 0, false, true, num) - 1;
		if(cnt >= N){
			r = m-1;
			ans = m;
		}else{
			l = m+1;
		}
	}
	cout << ans << endl;
	cout << (int64_t)(ans % mod) << endl;
	return 0;
}