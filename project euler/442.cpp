#include <bits/stdc++.h>
using namespace std;
using lli = uint64_t;

const int M = 10;
struct node{
	vector<int> child;
	int p = -1;
	char c = 0;
	int suffixLink = -1, endLink = -1;
	int id = -1;

	node(int p = -1, char c = 0) : p(p), c(c){
		child.resize(M, -1);
	}
};

struct AhoCorasick{
	vector<node> t;
	vector<int> lenghts;
	int wordCount = 0;

	AhoCorasick(){
		t.emplace_back();
	}

	void add(const string & s){
		int u = 0;
		for(char c : s){
			if(t[u].child[c-'0'] == -1){
				t[u].child[c-'0'] = t.size();
				t.emplace_back(u, c);
			}
			u = t[u].child[c-'0'];
		}
		t[u].id = wordCount++;
		lenghts.push_back(s.size());
	}

	void link(int u){
		if(u == 0){
			t[u].suffixLink = 0;
			t[u].endLink = 0;
			return;
		}
		if(t[u].p == 0){
			t[u].suffixLink = 0;
			if(t[u].id != -1) t[u].endLink = u;
			else t[u].endLink = t[t[u].suffixLink].endLink;
			return;
		}
		int v = t[t[u].p].suffixLink;
		char c = t[u].c;
		while(true){
			if(t[v].child[c-'0'] != -1){
				t[u].suffixLink = t[v].child[c-'0'];
				break;
			}
			if(v == 0){
				t[u].suffixLink = 0;
				break;
			}
			v = t[v].suffixLink;
		}
		if(t[u].id != -1) t[u].endLink = u;
		else t[u].endLink = t[t[u].suffixLink].endLink;
	}

	void build(){
		queue<int> Q;
		Q.push(0);
		while(!Q.empty()){
			int u = Q.front(); Q.pop();
			link(u);
			for(int v = 0; v < M; ++v)
				if(t[u].child[v] != -1)
					Q.push(t[u].child[v]);
		}
	}

	int curr = 0;

	bool match(char c){
		int i = c - '0';
		while(true){
			if(t[curr].child[i] != -1){
				curr = t[curr].child[i];
				break;
			}
			if(curr == 0) break;
			curr = t[curr].suffixLink;
		}
		int v = curr;
		bool ans = false;
		while(true){
			v = t[v].endLink;
			if(v == 0) break;
			ans = true;
			v = t[v].suffixLink;
		}
		return ans;
	}
};

lli mem[30][1000][2];

int main(){
	AhoCorasick aho;
	__int128_t eleven = 11;
	while(eleven < __int128_t(1.8e19)){
		aho.add(to_string(lli(eleven)));
		eleven *= 11;
	}
	aho.build();

	vector<int> digits;
	function<lli(int, int, int)> f = [&](int pos, int u, bool flag){
		if(pos == digits.size()){
			return lli(1);
		}
		lli & ans = mem[pos][u][flag];
		if(ans != -1) return ans;
		ans = 0;
		int lim = 9;
		if(flag) lim = digits[pos];
		for(int d = 0; d <= lim; ++d){
			int prev = aho.curr;
			bool can = aho.match(d + '0');
			if(!can) ans += f(pos + 1, aho.curr, flag & (d == lim));
			aho.curr = prev;
		}
		return ans;
	};

	auto cnt = [&](lli n){
		memset(mem, -1, sizeof(mem));
		digits = vector<int>();
		do{
			digits.push_back(n % 10);
			n /= 10;
		}while(n);
		reverse(digits.begin(), digits.end());
		aho.curr = 0;
		return f(0, 0, true) - 1;
	};

	lli l = 1, r = 1e19, target = 1e18, ans = -1;
	while(l <= r){
		lli n = (l + r) / 2;
		if(cnt(n) >= target){
			ans = n;
			r = n - 1;
		}else{
			l = n + 1;
		}
	}
	cout << ans << "\n";
	return 0;
}