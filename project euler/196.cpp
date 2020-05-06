#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

__int128_t powerMod(__int128_t a, __int128_t b, __int128_t m){
	__int128_t ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

bool isPrime(__int128_t n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	__int128_t d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		__int128_t m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) continue;
		int k = 0;
		for(; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}

auto r(lli n){
	lli start = n*(n-1)/2+1, end = n*(n+1)/2;
	vector<bool> is(end - start + 1);
	for(int i = 0; i < is.size(); ++i){
		is[i] = isPrime(start + i);
	}
	return is;
}

const vector<pair<int, int>> movs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

lli s(lli n){
	vector<vector<bool>> is;
	for(int i = n-2; i <= n+2; ++i){
		is.push_back(r(i));
		is.back().resize(n+2);
	}
	vector<vector<int>> ids(5, vector<int>(n+2, -1));
	vector<int> sz;
	function<void(int, int, int, int&)> dfs = [&](int x, int y, int id, int & cnt){
		ids[x][y] = id;
		cnt++;
		for(auto mov : movs){
			int nx = x + mov.first, ny = y + mov.second;
			if(0 <= nx && nx < 5 && 0 <= ny && ny < n+2 && is[nx][ny] && ids[nx][ny] == -1){
				dfs(nx, ny, id, cnt);
			}
		}
	};
	int id = 0;
	for(int x = 0; x < 5; ++x){
		for(int y = 0; y < n+2; ++y){
			if(!is[x][y]) continue;
			if(ids[x][y] == -1){
				int cnt = 0;
				dfs(x, y, id++, cnt);
				sz.push_back(cnt);
			}
		}
	}
	lli sum = 0;
	for(int y = 0; y < n+2; ++y){
		if(ids[2][y] != -1 && sz[ids[2][y]] >= 3){
			sum += n*(n-1)/2 + 1 + y;
		}
	}
	return sum;
}

int main(){
	cout << s(5678027) + s(7208785) << "\n";
	return 0;
}