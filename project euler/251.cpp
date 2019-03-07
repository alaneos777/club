#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
	vector<int> lp(n + 1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lp[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lp[j] == j) lp[j] = i;
	return lp;
}

const int L = 110000000;
const int M = 16224760;
const vector<int> lp = sieve(8*M);

void fact(int n, map<int, int> & f, int m){
	while(n > 1){
		int p = lp[n], pot=0;
		while(n%p == 0) pot++, n/=p;
		f[p] += pot*m;
	}
}

void dfs(map<int, int>::iterator it, map<int, int>::iterator fin, int a, lli b, __int128 n, int & cnt){
	if(it == fin){
		__int128 c = n/(b*b);
		if(a+b+c<=L){
			cnt++;
		}
		return;
	}
	lli p_pow = 1;
	int p = it->first, x = it->second;
	auto it2 = it;
	it2++;
	for(int i = 0; i <= x; ++i){
		if(a+b>L) break;
		dfs(it2, fin, a, b * p_pow, n, cnt);
		p_pow *= p;
	}
}

int main(){
	int ans = 0;
	for(int t = 1; t <= M; ++t){
		int cnt = 0;
		map<int, int> f, sq;
		fact(t, f, 2);
		fact(8*t-3, f, 1);
		for(auto p : f){
			if(p.second >= 2) sq[p.first] = p.second / 2;
		}
		dfs(sq.begin(), sq.end(), 3*t-1, 1, (__int128)t*t*(8*t-3), cnt);
		ans += cnt;
	}
	cout << ans << "\n";
	return 0;
}