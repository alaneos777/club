#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 4321;

lli rec(const vector<lli> & P, const vector<lli> & init, lli n){
	int deg = P.size();
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				(R[i + j + d] += ans[i] * ans[j]) %= mod;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				(R[i + j] += R[i + deg] * P[j]) %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		(nValue += ans[i] * init[i]) %= mod;
	return nValue;
}

lli inverse(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(r0 == 1);
	if(s0 < 0) s0 += n;
	return s0;
}

vector<lli> BerlekampMassey(const vector<lli> & init){
	vector<lli> cur, ls;
	lli ld;
	for(int i = 0, m; i < init.size(); ++i){
		lli eval = 0;
		for(int j = 0; j < cur.size(); ++j)
			eval = (eval + init[i-j-1] * cur[j]) % mod;
		eval -= init[i];
		if(eval < 0) eval += mod;
		if(eval == 0) continue;
		if(cur.empty()){
			cur.resize(i + 1);
			m = i;
			ld = eval;
		}else{
			lli k = eval * inverse(ld, mod) % mod;
			vector<lli> c(i - m - 1);
			c.push_back(k);
			for(int j = 0; j < ls.size(); ++j)
				c.push_back((mod-ls[j]) * k % mod);
			if(c.size() < cur.size()) c.resize(cur.size());
			for(int j = 0; j < cur.size(); ++j){
				c[j] += cur[j];
				if(c[j] >= mod) c[j] -= mod;
			}
			if(i - m + ls.size() >= cur.size())
				ls = cur, m = i, ld = eval;
			cur = c;
		}
	}
	if(cur.empty()) cur.push_back(0);
	reverse(cur.begin(), cur.end());
	return cur;
}

const int five[2] = {1, 5};

inline int get(int msk, int pos){
	return msk/five[pos] % 5;
}

inline int put(int msk, int pos, int val){
	//assert(get(msk, pos) == 0);
	return msk + val*five[pos];
}

int mem[20][2][25][25][25][25];

int f(int col, int row, int a, int b, int c, int d){
	if(row == 2){
		if(col == 0){
			//assert(c == 0 && d == 0);
			return 1;
		}else{
			return f(col-1, 0, b, c, d, 0);
		}
	}
	int& ans = mem[col][row][a][b][c][d];
	if(ans != -1) return ans;
	ans = 0;
	if(get(b, row) != 0){
		ans += f(col, row+1, a, b, c, d);
		if(ans >= mod) ans -= mod;
	}else{
		bool flg = (get(a, 0) != get(a, 1)) && (b == 0);
		for(int color = 1; color <= 4; ++color){
			// 1*1
			if(!flg && get(b, row) == 0 && (row == 0 || get(b, row-1) != color) && (row == 1 || get(b, row+1) != color) && get(a, row) != color){
				ans += f(col, row+1, a, put(b, row, color), c, d);
				if(ans >= mod) ans -= mod;
			}
			// 1*2
			if(row == 0 && get(b, row) == 0 && get(b, row+1) == 0 && get(a, row) != color && get(a, row+1) != color){
				ans += f(col, row+2, a, put(put(b, row, color), row+1, color), c, d);
				if(ans >= mod) ans -= mod;
			}
			// 2*1
			if(!flg && col >= 1 && get(b, row) == 0 && get(c, row) == 0 && (row == 0 || (get(b, row-1) != color && get(c, row-1) != color)) && (row == 1 || (get(b, row+1) != color && get(c, row+1) != color)) && get(a, row) != color){
				ans += f(col, row+1, a, put(b, row, color), put(c, row, color), d);
				if(ans >= mod) ans -= mod;
			}
			// 3*1
			if(!flg && col >= 2 && get(b, row) == 0 && get(c, row) == 0 && get(d, row) == 0 && (row == 0 || (get(b, row-1) != color && get(c, row-1) != color && get(d, row-1) != color)) && (row == 1 || (get(b, row+1) != color && get(c, row+1) != color && get(d, row+1) != color)) && get(a, row) != color){
				ans += f(col, row+1, a, put(b, row, color), put(c, row, color), put(d, row, color));
				if(ans >= mod) ans -= mod;
			}
		}
	}
	return ans;
}

int main(){
	memset(mem, -1, sizeof(mem));
	vector<lli> init;
	for(int i = 1; i <= 20; ++i){
		init.push_back(f(i-1, 0, 0, 0, 0, 0));
	}
	vector<lli> P = BerlekampMassey(init);
	lli N = 1e16;
	cout << rec(P, init, N-1) << "\n";
	return 0;
}