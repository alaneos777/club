#include <bits/stdc++.h>
using namespace std;

struct AVLNode{
	AVLNode *left, *right;
	short int height;
	int size;
	int value;
	int freq;

	AVLNode(int value = 0): left(NULL), right(NULL), value(value), height(1), size(1), freq(1){}

	inline short int balance(){
		return (right ? right->height : 0) - (left ? left->height : 0);
	}

	inline void update(){
		height = 1 + max(left ? left->height : 0, right ? right->height : 0);
		size = freq + (left ? left->size : 0) + (right ? right->size : 0);
	}

	AVLNode *maxLeftChild(){
		AVLNode *ret = this;
		while(ret->left) ret = ret->left;
		return ret;
	}
};

AVLNode pool[2500000];
int cnt = 0;

struct AVLTree{
	AVLNode *root;

	AVLTree(): root(NULL){}

	inline int nodeSize(AVLNode *& pos){return pos ? pos->size: 0;}

	int size(){return nodeSize(root);}

	void leftRotate(AVLNode *& x){
		AVLNode *y = x->right, *t = y->left;
		y->left = x, x->right = t;
		x->update(), y->update();
		x = y;
	}

	void rightRotate(AVLNode *& y){
		AVLNode *x = y->left, *t = x->right;
		x->right = y, y->left = t;
		y->update(), x->update();
		y = x;
	}

	void updateBalance(AVLNode *& pos){
		short int bal = pos->balance();
		if(bal > 1){
			if(pos->right->balance() < 0) rightRotate(pos->right);
			leftRotate(pos);
		}else if(bal < -1){
			if(pos->left->balance() > 0) leftRotate(pos->left);
			rightRotate(pos);
		}
	}

	void insert(AVLNode *&pos, const int & value){
		if(pos){
			if(value < pos->value) insert(pos->left, value);
			else if(value > pos->value) insert(pos->right, value);
			else pos->freq++;
			pos->update(), updateBalance(pos);
		}else{
			pos = &pool[cnt++];
			pos->value = value;
		}
	}

	void erase(AVLNode *&pos, const int & value){
		if(!pos) return;
		if(value < pos->value) erase(pos->left, value);
		else if(value > pos->value) erase(pos->right, value);
		else{
			if(pos->freq > 1) pos->freq--;
			else{
				if(!pos->left) pos = pos->right;
				else if(!pos->right) pos = pos->left;
				else{
					pos->value = pos->right->maxLeftChild()->value;
					erase(pos->right, pos->value);
				}
			}
		}
		if(pos) pos->update(), updateBalance(pos);
	}

	void updateVal(int old, int New){
		erase(root, old), insert(root, New);
	}

	int ge(const int & x){
		int ans = 0;
		AVLNode *pos = root;
		while(pos){
			if(x < pos->value){
				ans += nodeSize(pos->right) + pos->freq;
				pos = pos->left;
			}else{
				pos = pos->right;
			}
		}
		return ans;
	}

	void build(AVLNode *& pos, vector<int> & arr, int i, int j){
		if(i > j) return;
		int m = i + ((j - i) >> 1);
		pos = &pool[cnt++];
		pos->value = arr[m];
		build(pos->left, arr, i, m - 1);
		build(pos->right, arr, m + 1, j);
		pos->update();
	}

	void build(vector<int> & arr){
		build(root, arr, 0, (int)arr.size() - 1);
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

void mergeAVLs(AVLTree & a, AVLTree & b, AVLTree & c){
	vector<int> arra(a.size()), arrb(b.size()), arrc(a.size() + b.size());
	a.output(arra);
	b.output(arrb);
	merge(arra.begin(), arra.end(), arrb.begin(), arrb.end(), arrc.begin());
	c.build(arrc);
}

struct SegmentTree{
	int N;
	vector<AVLTree> ST;

	SegmentTree(int N): N(N){
		ST.resize(N << 1);
	}

	void build(vector<int> & arr){
		for(int i = 0; i < N; ++i)
			ST[N + i].insert(ST[N + i].root, arr[i]);
		for(int i = N - 1; i > 0; --i)
			mergeAVLs(ST[i << 1], ST[i << 1 | 1], ST[i]);
	}

	void update(const int & oldVal, const int & newVal, int pos){
		ST[pos += N].updateVal(oldVal, newVal);
		while(pos >>= 1)
			ST[pos].updateVal(oldVal, newVal);
	}

	int ge(int l, int r, int k){
		int res = 0;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1){
				res += ST[l].ge(k);
				l++;
			}
			if(!(r & 1)){
				res += ST[r].ge(k);
				r--;
			}
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, type, q, i, v, l, r, k;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	SegmentTree st(n);
	st.build(a);
	cin >> q;
	while(q--){
		cin >> type;
		if(type == 0){
			cin >> i >> v;
			--i;
			st.update(a[i], v, i);
			a[i] = v;
		}else if(type == 1){
			cin >> l >> r >> k;
			--l, --r;
			cout << st.ge(l, r, k) << "\n";
		}
	}
	return 0;
}