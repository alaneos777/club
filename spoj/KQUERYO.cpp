#include <bits/stdc++.h>
using namespace std;

struct AVLNode
{
	AVLNode *left;
	AVLNode *right;
	short int height;
	int size;
	int value;

	AVLNode(int value){
		left = right = NULL;
		this->value = value;
		height = 1, size = 0;
	}

	short int balance(){
		return (right ? right->height : 0) - (left ? left->height : 0);
	}

	void updateHeight(){
		height = 1 + max(left ? left->height : 0, right ? right->height : 0);
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
	int size = 0;

	AVLTree(){
		root = NULL;
	}

	void leftRotate(AVLNode *& x){
		AVLNode *y = x->right;
		AVLNode *t = y->left;
		y->left = x;
		x->right = t;
		x->updateHeight();
		y->updateHeight();
		int size = t ? t->size + 1 : 0;
		x->size = x->size - (y->size + 1) + size;
		y->size = y->size - size + (x->size + 1);
		x = y;
	}

	void rightRotate(AVLNode *& y){
		AVLNode *x = y->left;
		AVLNode *t = x->right;
		x->right = y;
		y->left = t;
		y->updateHeight();
		x->updateHeight();
		int size = t ? t->size + 1 : 0;
		y->size = y->size - (x->size + 1) + size;
		x->size = x->size - size + (y->size + 1);
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

	void build(AVLNode *& pos, const vector<int> & arr, int i, int j){
		if(i > j) return;
		int m = i + ((j - i) >> 1);
		pos = new AVLNode(arr[m]);
		build(pos->left, arr, i, m - 1);
		build(pos->right, arr, m + 1, j);
		pos->size = j - i;
		pos->updateHeight();
	}

	void build(const vector<int> & arr){
		size = arr.size();
		build(root, arr, 0, size - 1);
	}

	void insert(AVLNode *&pos, const int & value){
		if(pos){
			value < pos->value ? insert(pos->left, value) : insert(pos->right, value);
			++pos->size;
			pos->updateHeight();
			updateBalance(pos);
		}else{
			pos = new AVLNode(value);
			++size;
		}
	}

	void insert(int value){
		insert(root, value);
	}

	int greaterThan(const int & x){
		int ans = 0;
		AVLNode *pos = root;
		while(pos){
			int size = pos->right ? pos->right->size + 1: 0;
			if(x < pos->value){
				ans += size + 1;
				pos = pos->left;
			}else if(x >= pos->value){
				pos = pos->right;
			}
		}
		return ans;
	}

	void output(AVLNode *pos, vector<int> & arr, int & i){
		if(pos){
			output(pos->left, arr, i);
			arr[++i] = pos->value;
			output(pos->right, arr, i);
		}
	}

	void output(vector<int> & arr){
		int i = -1;
		output(root, arr, i);
	}
};

AVLTree* mergeAVLs(AVLTree *a, AVLTree *b){
	AVLTree* c = new AVLTree();
	vector<int> arra(a->size), arrb(b->size), arrc(a->size + b->size);
	a->output(arra);
	b->output(arrb);
	merge(arra.begin(), arra.end(), arrb.begin(), arrb.end(), arrc.begin());
	c->build(arrc);
	return c;
}

struct SegmentTree{
	int N;
	vector<AVLTree*> ST;

	SegmentTree(int N){
		this->N = N;
		ST.assign(N << 1, NULL);
		for(int i = 0; i < ST.size(); ++i)
			ST[i] = new AVLTree();
	}

	void build(vector<int> & arr){
		for(int i = 0; i < N; ++i)
			ST[N + i]->insert(arr[i]);
		for(int i = N - 1; i > 0; --i)
			ST[i] = mergeAVLs(ST[i << 1], ST[i << 1 | 1]);
	}

	int query(int l, int r, int x){
		++r;
		int res = 0;
		for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
			if(l & 1){
				res += ST[l]->greaterThan(x);
				++l;
			}
			if(r & 1){
				--r;
				res += ST[r]->greaterThan(x);
			}
		}
		return res;
	}
};

int main(){
	int n, q, l, r, k;
	int lastAns = 0;
	scanf("%d", &n);
	vector<int> arr(n);
	SegmentTree *st = new SegmentTree(n);
	for(int i = 0; i < n; ++i){
		scanf("%d", &arr[i]);
	}
	st->build(arr);
	scanf("%d", &q);
	while(q--){
		scanf("%d %d %d", &l, &r, &k);
		l ^= lastAns, r ^= lastAns, k ^= lastAns;
		if(l < 1) l = 1;
		if(r > n) r = n;
		lastAns = st->query(l - 1, r - 1, k);
		printf("%d\n", lastAns);
	}
	return 0;
}