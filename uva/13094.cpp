#include <bits/stdc++.h>
using namespace std;

int inf = 1 << 30;

template<typename T>
struct AVLNode
{
	AVLNode<T> *left, *right;
	short int height;
	int size;
	T value;
	int freq;

	AVLNode(T value = 0): left(NULL), right(NULL), value(value), height(1), size(1), freq(1){}

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

template<typename T>
struct AVLTree
{
	AVLNode<T> *root;

	AVLTree(): root(NULL){}

	inline int nodeSize(AVLNode<T> *& pos){return pos ? pos->size: 0;}

	int size(){return nodeSize(root);}

	void leftRotate(AVLNode<T> *& x){
		AVLNode<T> *y = x->right, *t = y->left;
		y->left = x, x->right = t;
		x->update(), y->update();
		x = y;
	}

	void rightRotate(AVLNode<T> *& y){
		AVLNode<T> *x = y->left, *t = x->right;
		x->right = y, y->left = t;
		y->update(), x->update();
		y = x;
	}

	void updateBalance(AVLNode<T> *& pos){
		short int bal = pos->balance();
		if(bal > 1){
			if(pos->right->balance() < 0) rightRotate(pos->right);
			leftRotate(pos);
		}else if(bal < -1){
			if(pos->left->balance() > 0) leftRotate(pos->left);
			rightRotate(pos);
		}
	}

	void insert(AVLNode<T> *&pos, const T & value){
		if(pos){
			if(value < pos->value) insert(pos->left, value);
			else if(value > pos->value) insert(pos->right, value);
			else pos->freq++;
			pos->update(), updateBalance(pos);
		}else{
			pos = new AVLNode<T>(value);
		}
	}

	void erase(AVLNode<T> *&pos, const T & value){
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

	void updateVal(T old, T New){
		erase(root, old), insert(root, New);
	}

	int lessThanOrEqual(const T & x){
		int ans = 0;
		AVLNode<T> *pos = root;
		while(pos){
			if(x < pos->value){
				pos = pos->left;
			}else{
				ans += nodeSize(pos->left) + pos->freq;
				pos = pos->right;
			}
		}
		return ans;
	}

	void build(AVLNode<T> *& pos, vector<T> & arr, int i, int j){
		if(i > j) return;
		int m = i + ((j - i) >> 1);
		pos = new AVLNode<T>(arr[m]);
		build(pos->left, arr, i, m - 1);
		build(pos->right, arr, m + 1, j);
		pos->update();
	}

	void build(vector<T> & arr){
		build(root, arr, 0, (int)arr.size() - 1);
	}

	void output(AVLNode<T> *pos, vector<T> & arr, int & i){
		if(pos){
			output(pos->left, arr, i);
			arr[++i] = pos->value;
			output(pos->right, arr, i);
		}
	}

	void output(vector<T> & arr){
		int i = -1;
		output(root, arr, i);
	}
};

template<typename T>
AVLTree<T>* mergeAVLs(AVLTree<T> *a, AVLTree<T> *b){
	AVLTree<T>* c = new AVLTree<T>();
	vector<T> arra(a->size()), arrb(b->size()), arrc(a->size() + b->size());
	a->output(arra);
	b->output(arrb);
	merge(arra.begin(), arra.end(), arrb.begin(), arrb.end(), arrc.begin());
	c->build(arrc);
	return c;
}

struct SegmentTree{
	int N;
	vector<AVLTree<int>*> ST;

	SegmentTree(int N): N(N){
		ST.resize(N << 1);
		for(int i = 0; i < ST.size(); ++i)
			ST[i] = new AVLTree<int>();
	}

	void build(vector<int> & arr){
		for(int i = 0; i < N; ++i)
			ST[N + i]->insert(ST[N + i]->root, arr[i]);
		for(int i = N - 1; i > 0; --i)
			ST[i] = mergeAVLs<int>(ST[i << 1], ST[i << 1 | 1]);
	}

	void update(const int & oldVal, const int & newVal, int pos){
		ST[pos += N]->updateVal(oldVal, newVal);
		while(pos >>= 1)
			ST[pos]->updateVal(oldVal, newVal);
	}

	int leq(int l, int r, int k){
		int res = 0;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1){
				res += ST[l]->lessThanOrEqual(k);
				l++;
			}
			if(!(r & 1)){
				res += ST[r]->lessThanOrEqual(k);
				r--;
			}
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, t, pos, val, l, r, k;
	while(cin >> n >> m && !(n == 0 && m == 0)){
		vector<int> arr(n, inf);
		SegmentTree st(n);
		st.build(arr);
		while(m--){
			cin >> t;
			if(t == 0){
				cin >> pos >> val;
				st.update(arr[pos], val, pos);
				arr[pos] = val;
			}else{
				cin >> l >> r >> k;
				cout << st.leq(l, r, k) << "\n";
			}
		}
	}
	return 0;
}