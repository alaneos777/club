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

	void erase(AVLNode *&pos, const int & value){
		AVLNode *tmp, *next;
		if(!pos) return;
		if(value < pos->value){
			erase(pos->left, value);
			--pos->size;
		}else if(value > pos->value){
			erase(pos->right, value);
			--pos->size;
		}else{
			--size;
			if(!pos->left){
				pos = pos->right;
			}else if(!pos->right){
				pos = pos->left;
			}else{
				++size;
				next = pos->right->maxLeftChild(); //pos->left->maxRightChild();
				pos->value = next->value;
				erase(pos->right, pos->value);     //erase(pos->left, pos->value);
				--pos->size;
			}
		}
		if(pos){
			pos->updateHeight();
			updateBalance(pos);
		}
	}

	void erase(int value){
		erase(root, value);
	}

	void update(int old, int New){
		erase(old);
		insert(New);
	}

	int greaterThanOrEqual(const int & x){
		int ans = 0;
		AVLNode *pos = root;
		while(pos){
			int size = pos->right ? pos->right->size + 1: 0;
			if(x < pos->value){
				ans += size + 1;
				pos = pos->left;
			}else if(x > pos->value){
				pos = pos->right;
			}else{
				ans += size + 1;
				break;
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
	vector<int> arr;
	vector<AVLTree*> ST;

	SegmentTree(int N){
		this->N = N;
		arr.assign(N, 0);
		ST.assign(N << 1, NULL);
		for(int i = 0; i < ST.size(); ++i)
			ST[i] = new AVLTree();
	}

	void build(){
		for(int i = 0; i < N; ++i)
			ST[N + i]->insert(arr[i]);
		for(int i = N - 1; i > 0; --i)
			ST[i] = mergeAVLs(ST[i << 1], ST[i << 1 | 1]);
	}

	void update(int pos, int value){
		int old = arr[pos];
		arr[pos] = value;
		pos += N;
		ST[pos]->update(old, value);
		while(pos > 1){
			ST[pos >> 1]->update(old, value);
			pos >>= 1;
		}
	}

	int query(int l, int r, int x){
		++r;
		int res = 0;
		for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
			if(l & 1){
				res += ST[l]->greaterThanOrEqual(x);
				++l;
			}
			if(r & 1){
				--r;
				res += ST[r]->greaterThanOrEqual(x);
			}
		}
		return res;
	}
};

int main(){
	int n, q, t, a, b, c;
	scanf("%d", &n);
	SegmentTree * st = new SegmentTree(n);
	for(int i = 0; i < n; ++i){
		scanf("%d", &st->arr[i]);
	}
	st->build();
	scanf("%d", &q);
	while(q--){
		scanf("%d", &t);
		if(t == 0){
			scanf("%d %d %d", &a, &b, &c);
			printf("%d\n", st->query(a - 1, b - 1, c));
		}else{
			scanf("%d %d", &a, &b);
			st->update(a - 1, b);
		}
	}
	return 0;
}