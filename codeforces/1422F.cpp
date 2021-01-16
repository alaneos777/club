#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using lli = int64_t;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

struct TreapNode{
	TreapNode *left, *right;
	pii value;
	int key;

	int prod;

	TreapNode(const pii & value): value(value), key(rand()), left(NULL), right(NULL), prod(value.second){}
};

struct Treap{
	TreapNode *root;

	Treap(): root(NULL) {}

	inline int nodeProd(TreapNode* t){return t ? t->prod : 1;}

	inline void update(TreapNode* &t){
		if(!t) return;
		t->prod = (lli)t->value.second * nodeProd(t->left) % mod * nodeProd(t->right) % mod;
	}

	void merge(TreapNode* &t, TreapNode* t1, TreapNode* t2){
		if(!t1) t = t2;
		else if(!t2) t = t1;
		else if(t1->key > t2->key)
			merge(t1->right, t1->right, t2), t = t1;
		else
			merge(t2->left, t1, t2->left), t = t2;
		update(t);
	}

	void split(TreapNode* t, const pii & x, TreapNode* &t1, TreapNode* &t2){
		if(!t)
			return void(t1 = t2 = NULL);
		if(x < t->value)
			split(t->left, x, t1, t->left), t2 = t;
		else
			split(t->right, x, t->right, t2), t1 = t;
		update(t);
	}

	void insert(TreapNode* &t, TreapNode* x){
		if(!t) t = x;
		else if(x->key > t->key)
			split(t, x->value, x->left, x->right), t = x;
		else
			insert(x->value < t->value ? t->left : t->right, x);
		update(t);
	}

	void insert(const pii & x){insert(root, new TreapNode(x));}

	int getProd(int x){
		lli ans = 1;
		TreapNode *pos = root;
		while(pos){
			if(x < pos->value.first){
				ans = ans * nodeProd(pos->right) % mod * pos->value.second % mod;
				pos = pos->left;
			}else{
				pos = pos->right;
			}
		}
		return ans;
	}

	void output(TreapNode *pos, function<void(const pii&)> f){
		if(pos){
			output(pos->left, f);
			f(pos->value);
			output(pos->right, f);
		}
	}

	void output(function<void(const pii&)> f){
		output(root, f);
	}
};

Treap* mergeTreaps(Treap *a, Treap *b){
	Treap* c = new Treap();
	auto f = [&](const pii & x){
		c->insert(x);
	};
	a->output(f);
	b->output(f);
	return c;
}

struct SegmentTree{
	int N;
	vector<Treap*> ST;

	SegmentTree(int N, const vector<int> & a, const vector<int> & next): N(N){
		ST.resize(N << 1);
		for(int i = 0; i < N; ++i){
			ST[N + i] = new Treap();
			ST[N + i]->insert({next[i], a[i]});
		}
		for(int i = N - 1; i > 0; --i){
			ST[i] = mergeTreaps(ST[i << 1], ST[i << 1 | 1]);
		}
	}

	int query(int l, int r, int x){
		lli res = 1;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res = res * ST[l++]->getProd(x) % mod;
			if(!(r & 1)) res = res * ST[r--]->getProd(x) % mod;
		}
		return res;
	}
};

struct SparseTable{
	vector<vector<int8_t>> ST;
	vector<int8_t> logs;
	int K, N;

	SparseTable(const vector<int8_t> & arr){
		N = arr.size();
		K = log2(N) + 2;
		ST.assign(K + 1, vector<int8_t>(N));
		logs.assign(N + 1, 0);
		for(int i = 2; i <= N; ++i)
			logs[i] = logs[i >> 1] + 1;
		for(int i = 0; i < N; ++i)
			ST[0][i] = arr[i];
		for(int j = 1; j <= K; ++j)
			for(int i = 0; i + (1 << j) <= N; ++i)
				ST[j][i] = max(ST[j - 1][i], ST[j - 1][i + (1 << (j - 1))]);
	}

	int query(int l, int r){
		int j = logs[r - l + 1];
		return max(ST[j][l], ST[j][r - (1 << j) + 1]);
	}
};

auto sieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return primes;
}

const int M = 2e5;
const auto primes = sieve(sqrt(M));

int main(){
	srand(time(0));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	vector<SparseTable> tables;
	for(int p : primes){
		vector<int8_t> cnt_p(n);
		for(int i = 0; i < n; ++i){
			while(a[i] % p == 0){
				a[i] /= p;
				cnt_p[i]++;
			}
		}
		tables.emplace_back(cnt_p);
	}
	vector<int> next(n, n), tmp(M + 1, n);
	for(int i = n - 1; i >= 0; --i){
		if(tmp[a[i]] != n){
			next[i] = tmp[a[i]];
		}
		tmp[a[i]] = i;
	}
	SegmentTree st(n, a, next);
	cin >> q;
	int prev = 0;
	while(q--){
		int x, y;
		cin >> x >> y;
		int l = (prev + x) % n, r = (prev + y) % n;
		if(l > r) swap(l, r);
		lli ans = st.query(l, r, r);
		for(int k = 0; k < primes.size(); ++k){
			int p = primes[k];
			ans = ans * power(p, tables[k].query(l, r)) % mod;
		}
		cout << ans << "\n";
		prev = ans;
	}
	return 0;
}