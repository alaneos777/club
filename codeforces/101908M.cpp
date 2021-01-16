#include <bits/stdc++.h>
using namespace std;

struct bs{
	vector<uint64_t> a;
	size_t sz;

	bs(){}
	bs(size_t sz): sz(sz), a((sz + 63) >> 6) {}

	bool operator[](size_t i) const{
		return (a[i >> 6] >> (63-(i & 63))) & 1;
	}

	bool operator>(const bs& rhs) const{
		return a > rhs.a;
	}

	void set(size_t i){
		a[i >> 6] |= (1ll << (63-(i & 63)));
	}

	void flip(size_t i){
		a[i >> 6] ^= (1ll << (63-(i & 63)));
	}

	bs& operator^=(const bs& rhs){
		for(size_t i = 0; i < a.size(); ++i){
			a[i] ^= rhs.a[i];
		}
		return *this;
	}
};

int gauss(vector<bs> & A){
	int m = A.size(), n = A[0].sz, i = 0, j = 0;
	while(i < m && j < n){
		if(A[i][j] == 0){
			for(int k = i + 1; k < m; k++){
				if(A[k][j] != 0){
					swap(A[i], A[k]);
					break;
				}
			}
		}
		if(A[i][j] != 0){
			for(int k = 0; k < m; k++){
				if(k != i && A[k][j] != 0){
					A[k] ^= A[i];
				}
			}
			i++;
		}
		j++;
	}
	return i;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int m, n;
	cin >> m >> n;
	cin.ignore();
	vector<bs> equations(m, bs(n+1));
	for(int i = 0; i < m; ++i){
		equations[i].flip(n);
		string s;
		getline(cin, s);
		s = s.substr(1, s.find(")")-1);
		int pos = 0;
		char c = s[pos++];
		bool neg = 0;
		while(pos < s.size()){
			if(c == ' '){
				c = s[pos++];
			}else if(c == 'x'){
				int id = 0;
				while(pos < s.size() && isdigit(c = s[pos++])){
					id = id*10 + (c - '0');
				}
				equations[i].flip(id-1);
				if(neg) equations[i].flip(n);
				neg = 0;
			}else if(c == 'o'){
				c = s[pos++]; c = s[pos++];
			}else if(c == 'n'){
				c = s[pos++]; c = s[pos++]; c = s[pos++];
				neg = 1;
			}
		}
	}
	int rank = 0;
	int rank_augmented = gauss(equations);
	vector<int> pivot(m);
	vector<bool> is_free(n, true);
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			if(equations[i][j]){
				pivot[i] = j;
				is_free[j] = false;
				rank++;
				break;
			}
		}
	}
	pivot.resize(rank);
	if(rank < rank_augmented){
		cout << "impossible\n";
	}else{
		bs ans(n);
		for(int i = 0; i < rank; ++i){
			if(equations[i][n]){
				ans.set(pivot[i]);
			}
		}
		int nullity = n - rank;
		if(nullity > 0){
			vector<bs> kernel(nullity, bs(n));
			int sz = 0;
			for(int j = 0; j < n; ++j){
				if(is_free[j]){
					int idx_col = 0;
					for(int i = 0; i < n; ++i){
						if(is_free[i]){
							if(i == j) kernel[sz].set(i);
						}else{
							if(equations[idx_col][j]) kernel[sz].set(i);
							idx_col++;
						}
					}
					sz++;
				}
			}
			int dis = gauss(kernel);
			for(int i = 0; i < dis; ++i){
				bs curr = ans;
				curr ^= kernel[i];
				if(curr > ans){
					ans = curr;
				}
			}
		}
		for(int i = 0; i < n; ++i){
			if(ans[i]) cout << "T";
			else cout << "F";
		}
		cout << "\n";
	}
	return 0;
}