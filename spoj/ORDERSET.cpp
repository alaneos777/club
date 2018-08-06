#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct AVLNode
{
	AVLNode<T> *left, *right;
	short int height;
	int size;
	T value;

	AVLNode(T value = 0): left(NULL), right(NULL), value(value), height(1), size(1){}

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

	void insert(AVLNode<T> *&pos, T & value){
		if(pos){
			value < pos->value ? insert(pos->left, value) : insert(pos->right, value);
			pos->update();
			updateBalance(pos);
		}else
			pos = new AVLNode<T>(value);
	}

	AVLNode<T> *search(T & value){
		AVLNode<T> *pos = root;
		while(pos){
			if(value == pos->value) break;
			pos = (value < pos->value ? pos->left : pos->right);
		}
		return pos;
	}

	void erase(AVLNode<T> *&pos, T & value){
		if(!pos) return;
		if(value < pos->value) erase(pos->left, value);
		else if(value > pos->value) erase(pos->right, value);
		else{
			if(!pos->left) pos = pos->right;
			else if(!pos->right) pos = pos->left;
			else{
				pos->value = pos->right->maxLeftChild()->value;
				erase(pos->right, pos->value);
			}
		}
		if(pos) pos->update(), updateBalance(pos);
	}

	void insert(T value){insert(root, value);}

	void erase(T value){erase(root, value);}

	T kth(int i){
		if(i < 0 || i >= nodeSize(root)) return -1;
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

	int lessThan(T & x){
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
};

int main(){
	int q, x;
	char op;
	AVLTree<int>* avl = new AVLTree<int>();
	scanf("%d", &q);
	while(q--){
		scanf(" %c", &op); scanf("%d", &x);
		if(op == 'I'){
			if(!avl->search(x)) avl->insert(x);
		}else if(op == 'D'){
			avl->erase(x);
		}else if(op == 'C'){
			printf("%d\n", avl->lessThan(x));
		}else if(op == 'K'){
			if(x > avl->size() || x < 1){
				printf("invalid\n");
			}else{
				printf("%d\n", avl->kth(x - 1));
			}
		}
	}
	return 0;
}