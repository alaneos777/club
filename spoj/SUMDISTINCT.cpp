#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef pair<int, int> pii;

struct AVLNode
{
	AVLNode *left;
	AVLNode *right;
	short int height;
	pii info; //first:next, second: original
	lli sum;

	AVLNode(const pii & value){
		left = right = NULL;
		this->info = value;
		height = 1, sum = value.second;
	}

	inline short int balance(){
		return (right ? right->height : 0) - (left ? left->height : 0);
	}

	inline void updateHeight(){
		height = 1 + max(left ? left->height : 0, right ? right->height : 0);
	}

	inline void updateSum(){
		sum = info.second + (left ? left->sum : 0) + (right ? right->sum : 0);
	}

	AVLNode *maxLeftChild(){
		AVLNode *ret = this;
		while(ret->left) ret = ret->left;
		return ret;
	}
};

struct AVLTree
{
	AVLNode *root;
	int size;

	AVLTree(){
		root = NULL;
		size = 0;
	}

	inline lli nodeSum(AVLNode *& pos){
		return pos ? pos->sum : 0;
	}

	void leftRotate(AVLNode *& x){
		AVLNode *y = x->right;
		AVLNode *t = y->left;
		y->left = x;
		x->right = t;
		x->updateHeight(), x->updateSum();
		y->updateHeight(), y->updateSum();
		x = y;
	}

	void rightRotate(AVLNode *& y){
		AVLNode *x = y->left;
		AVLNode *t = x->right;
		x->right = y;
		y->left = t;
		y->updateHeight(), y->updateSum();
		x->updateHeight(), x->updateSum();
		y = x;
	}

	void updateBalance(AVLNode *& pos){
		short int bal = pos->balance();
		if(bal > 1){
			if(pos->right->balance() < 0){
				rightRotate(pos->right);
				leftRotate(pos);
			}else{
				leftRotate(pos);
			}
		}else if(bal < -1){
			if(pos->left->balance() > 0){
				leftRotate(pos->left);
				rightRotate(pos);
			}else{
				rightRotate(pos);
			}
		}
	}

	void build(AVLNode *& pos, const vector<pii> & arr, int i, int j){
		if(i > j) return;
		int m = i + ((j - i) >> 1);
		pos = new AVLNode(arr[m]);
		build(pos->left, arr, i, m - 1);
		build(pos->right, arr, m + 1, j);
		pos->updateHeight(), pos->updateSum();
	}

	void build(const vector<pii> & arr){
		size = arr.size();
		build(root, arr, 0, size - 1);
	}

	void insert(AVLNode *&pos, const pii & value){
		if(pos){
			value < pos->info ? insert(pos->left, value) : insert(pos->right, value);
			pos->updateHeight(), pos->updateSum();
			updateBalance(pos);
		}else{
			pos = new AVLNode(value);
		}
	}

	void insert(const pii & value){
		insert(root, value);
		++size;
	}

	void erase(AVLNode *&pos, const pii & info){
		AVLNode *tmp, *next;
		if(!pos) return;
		if(info < pos->info){
			erase(pos->left, info);
		}else if(info > pos->info){
			erase(pos->right, info);
		}else{
			if(!pos->left){
				pos = pos->right;
			}else if(!pos->right){
				pos = pos->left;
			}else{
				next = pos->right->maxLeftChild(); //pos->left->maxRightChild();
				pos->info = next->info;
				erase(pos->right, pos->info);     //erase(pos->left, pos->value);
			}
		}
		if(pos){
			pos->updateHeight(), pos->updateSum();
			updateBalance(pos);
		}
	}

	void erase(const pii & info){
		erase(root, info);
		--size;
	}

	lli getSum(const int & x){
		lli ans = 0;
		AVLNode *pos = root;
		while(pos){
			if(x < pos->info.first){
				ans += nodeSum(pos->right) + pos->info.second;
				pos = pos->left;
			}else{
				pos = pos->right;
			}
		}
		return ans;
	}

	void output(AVLNode *pos, vector<pii> & arr, int & i){
		if(pos){
			output(pos->left, arr, i);
			arr[++i] = pos->info;
			output(pos->right, arr, i);
		}
	}

	void output(vector<pii> & arr){
		int i = -1;
		output(root, arr, i);
	}
};

AVLTree* mergeAVLs(AVLTree *a, AVLTree *b){
	AVLTree* c = new AVLTree();
	vector<pii> arra(a->size), arrb(b->size), arrc(a->size + b->size);
	a->output(arra);
	b->output(arrb);
	merge(arra.begin(), arra.end(), arrb.begin(), arrb.end(), arrc.begin());
	c->build(arrc);
	return c;
}

int inf = 1 << 29;

struct args{
	int pos;
	pii New;
};

struct SegmentTree{
	int N;
	vector<AVLTree*> ST;
	vector<int> arr, prev, next;
	unordered_map<int, set<int>> positions;
	stack<args> pending;

	SegmentTree(int N){
		this->N = N;
		arr.assign(N, 0);
		prev.assign(N, -inf);
		next.assign(N, inf);
		ST.assign(N << 1, NULL);
		for(int i = 0; i < ST.size(); ++i)
			ST[i] = new AVLTree();
	}

	void build(){
		for(int i = 0; i < N; ++i){
			ST[N + i]->insert(make_pair(next[i], arr[i]));
			positions[arr[i]].insert(i);
		}
		for(int i = N - 1; i > 0; --i)
			ST[i] = mergeAVLs(ST[i << 1], ST[i << 1 | 1]);
	}

	lli query(int l, int r, int x){
		++r;
		lli res = 0;
		for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
			if(l & 1){
				res += ST[l]->getSum(x);
				++l;
			}
			if(r & 1){
				--r;
				res += ST[r]->getSum(x);
			}
		}
		return res;
	}

	void update(int pos, const pii & info, bool ins){
		pos += N;
		if(ins){
			ST[pos]->insert(info);
			while(pos > 1){
				ST[pos >> 1]->insert(info);
				pos >>= 1;
			}
		}else{
			ST[pos]->erase(info);
			while(pos > 1){
				ST[pos >> 1]->erase(info);
				pos >>= 1;
			}
		}
	}

	void update(int pos, int value){
		int old = arr[pos];
		arr[pos] = value;
		if(prev[pos] != -inf){
			update(prev[pos], make_pair(next[prev[pos]], old), false);
			pending.push({prev[pos], make_pair(next[pos], old)});
			next[prev[pos]] = next[pos];
		}
		if(next[pos] != inf){
			prev[next[pos]] = prev[pos];
		}
		positions[old].erase(pos);
		auto it = positions[value].lower_bound(pos);
		if(it != positions[value].end()){
			int nextPos = *it;
			update(pos, make_pair(next[pos], old), false);
			pending.push({pos, make_pair(nextPos, value)});
			next[pos] = nextPos;
			prev[nextPos] = pos;
		}else{
			update(pos, make_pair(next[pos], old), false);
			pending.push({pos, make_pair(inf, value)});
			next[pos] = inf;
		}
		if(it != positions[value].begin()){
			--it;
			int prevPos = *it;
			update(prevPos, make_pair(next[prevPos], value), false);
			pending.push({prevPos, make_pair(pos, value)});
			prev[pos] = prevPos;
			next[prevPos] = pos;
		}else{
			prev[pos] = -inf;
		}
		positions[value].insert(pos);
		while(!pending.empty()){
			update(pending.top().pos, pending.top().New, true);
			pending.pop();
		}
	}
};

int main(){
	int n, q, x, y;
	char op;
	scanf("%d", &n);
	SegmentTree *st = new SegmentTree(n);
	for(int i = 0; i < n; ++i){
		scanf("%d", &st->arr[i]);
	}
	unordered_map<int, int> last, first;
	for(int i = n - 1; i >= 0; --i){
		if(last.count(st->arr[i])){
			st->next[i] = last[st->arr[i]];
		}
		last[st->arr[i]] = i;
	}
	for(int i = 0; i < n; ++i){
		if(first.count(st->arr[i])){
			st->prev[i] = first[st->arr[i]];
		}
		first[st->arr[i]] = i;
	}
	st->build();
	scanf("%d", &q);
	while(q--){
		scanf(" %c %d %d", &op, &x, &y);
		if(op == 'Q'){
			printf("%lld\n", st->query(x - 1, y - 1, y - 1));
		}else{
			st->update(x - 1, y);
		}
	}
	return 0;
}