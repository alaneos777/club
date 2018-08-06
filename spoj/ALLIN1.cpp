#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct AVLNode
{
	AVLNode<T> *left, *right;
	short int height;
	int size;
	T value;

	AVLNode(T value): left(NULL), right(NULL), value(value), height(1), size(1){}

	inline short int balance(){
		return (right ? right->height : 0) - (left ? left->height : 0);
	}

	inline void update(){
		height = 1 + max(left ? left->height : 0, right ? right->height : 0);
		size = 1 + (left ? left->size : 0) + (right ? right->size : 0);
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

	AVLTree(): root(NULL), size(0){}

	inline int nodeSize(AVLNode<T> *& pos){
		return pos ? pos->size: 0;
	}

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

	void insert(AVLNode<T> *&pos, const T & value){
		if(pos){
			value < pos->value ? insert(pos->left, value) : insert(pos->right, value);
			pos->update();
			updateBalance(pos);
		}else{
			pos = new AVLNode<T>(value);
			++size;
		}
	}

	void insert(T value){
		insert(root, value);
	}

	AVLNode<T> *search(const T & value){
		AVLNode<T> *pos = root;
		while(pos){
			if(value == pos->value) break;
			pos = (value < pos->value ? pos->left : pos->right);
		}
		return pos;
	}

	void erase(AVLNode<T> *&pos, const T & value){
		AVLNode<T> *tmp, *next;
		if(!pos) return;
		if(value < pos->value){
			erase(pos->left, value);
		}else if(value > pos->value){
			erase(pos->right, value);
		}else{
			if(!pos->left) pos = pos->right;
			else if(!pos->right) pos = pos->left;
			else{
				next = pos->right->maxLeftChild();
				pos->value = next->value;
				erase(pos->right, pos->value);
			}
		}
		if(pos){
			pos->update();
			updateBalance(pos);
		}
	}

	bool erase(T value){
		if(search(value)){
			erase(root, value);
			--size;
			return true;
		}
		return false;
	}

	int lessThan(const T & x){
		int ans = 0;
		AVLNode<T> *pos = root;
		while(pos){
			if(x > pos->value){
				ans += nodeSize(pos->left) + 1;
				pos = pos->right;
			}else{
				pos = pos->left;
			}
		}
		return ans;
	}

	T kth(int i){
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
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t, n;
	AVLTree<int> avl;
	while(cin >> t && t != -1){
		cin >> n;
		if(t == 1) avl.insert(n);
		else if(t == 2) avl.erase(n);
		else if(t == 3){
			if(avl.search(n)) cout << 1+avl.lessThan(n) << "\n";
			else cout << "-1\n";
		}else{
			if(1 <= n && n <= avl.size) cout << avl.kth(n-1) << "\n";
			else cout << "-1\n";
		}
	}
	return 0;
}