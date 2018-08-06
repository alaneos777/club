#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct AVLNode
{
	AVLNode<T> *left;
	AVLNode<T> *right;
	short int height;
	int size;
	T value;

	AVLNode(T value){
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

template<typename T>
struct AVLTree
{
	AVLNode<T> *root;
	int size;

	AVLTree(){
		root = NULL;
		size = 0;
	}

	int nodeSize(AVLNode<T> *& pos){
		return pos ? pos->size + 1: 0;
	}

	void leftRotate(AVLNode<T> *& x){
		AVLNode<T> *y = x->right;
		AVLNode<T> *t = y->left;
		y->left = x;
		x->right = t;
		x->updateHeight();
		y->updateHeight();
		int size = nodeSize(t);
		x->size = x->size - (y->size + 1) + size;
		y->size = y->size - size + (x->size + 1);
		x = y;
	}

	void rightRotate(AVLNode<T> *& y){
		AVLNode<T> *x = y->left;
		AVLNode<T> *t = x->right;
		x->right = y;
		y->left = t;
		y->updateHeight();
		x->updateHeight();
		int size = nodeSize(t);
		y->size = y->size - (x->size + 1) + size;
		x->size = x->size - size + (y->size + 1);
		y = x;
	}

	void updateBalance(AVLNode<T> *& pos){
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

	void build(AVLNode<T> *& pos, const vector<T> & arr, int i, int j){
		if(i > j) return;
		int m = i + ((j - i) >> 1);
		pos = new AVLNode<T>(arr[m]);
		build(pos->left, arr, i, m - 1);
		build(pos->right, arr, m + 1, j);
		pos->size = j - i;
		pos->updateHeight();
	}

	void build(const vector<T> & arr){
		size = arr.size();
		build(root, arr, 0, size - 1);
	}

	void insert(AVLNode<T> *&pos, const T & value){
		if(pos){
			value < pos->value ? insert(pos->left, value) : insert(pos->right, value);
			++pos->size;
			pos->updateHeight();
			updateBalance(pos);
		}else{
			pos = new AVLNode<T>(value);
			++size;
		}
	}

	void insert(T value){
		insert(root, value);
	}

	int lessThanOrEqual(const T & x){
		int ans = 0;
		AVLNode<T> *pos = root;
		while(pos){
			if(x < pos->value){
				pos = pos->left;
			}else{
				ans += nodeSize(pos->left) + 1;
				pos = pos->right;
			}
		}
		return ans;
	}

	T index(int i){
		AVLNode<T> *pos = root;
		while(i != nodeSize(pos->left)){
			if(i < nodeSize(pos->left)){
				pos = pos->left;
			}else{
				i -= nodeSize(pos->left) + 1;
				pos = pos->right;
			}
		}
		return pos->value;
	}
};

int main(){
	int n, q, d, x;
	scanf("%d %d", &n, &q);
	AVLTree<int> * tree = new AVLTree<int>();
	for(int i = 0; i < n; ++i){
		 scanf("%d", &x);
		 tree->insert(x);
	}
	while(q--){
		scanf("%d %d", &d, &x);
		if(d == 1){
			tree->insert(tree->lessThanOrEqual(x) + x);
		}else if(d == 2){
			printf("%d\n", tree->lessThanOrEqual(x));
		}else{
			if(x > tree->size){
				printf("invalid\n");
			}else{
				printf("%d\n", tree->index(x - 1));
			}
		}
	}
	return 0;
}