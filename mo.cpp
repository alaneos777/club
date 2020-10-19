#include <bits/stdc++.h>
using namespace std;

struct AVLNode{
	AVLNode *left, *right;
	short int height;
	int size, value, freq;

	AVLNode(int value = 0): left(NULL), right(NULL), value(value), height(1), size(1), freq(1){}

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

	void insert(AVLNode *&pos, int value){
		if(pos){
			if(value < pos->value) insert(pos->left, value);
			else if(value > pos->value) insert(pos->right, value);
			else pos->freq++;
			pos->update(), updateBalance(pos);
		}else{
			pos = new AVLNode(value);
		}
	}

	void erase(AVLNode *&pos, int value){
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

	void insert(int value){insert(root, value);}
	void erase(int value){erase(root, value);}

	int leq(int x){
		int ans = 0;
		AVLNode *pos = root;
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
};

struct query{
	int l, r, x, y, index, S;
	bool operator<(const query & q) const{
		int c_o = l / S, c_q = q.l / S;
		if(c_o == c_q)
			return r < q.r;
		return c_o < c_q;
	}
};

vector<int> MO(const vector<int> & A, vector<query> & queries){
	AVLTree st;
	vector<int> ans(queries.size());
	sort(queries.begin(), queries.end());
	int prevL = 0, prevR = -1;
	int i, j;
	for(const query & q : queries){
		for(i = prevL, j = min(prevR, q.l - 1); i <= j; ++i){
			st.erase(A[i]);
		}
		for(i = prevL - 1; i >= q.l; --i){
			st.insert(A[i]);
		}
		for(i = max(prevR + 1, q.l); i <= q.r; ++i){
			st.insert(A[i]);
		}
		for(i = prevR; i >= q.r + 1; --i){
			st.erase(A[i]);
		}
		prevL = q.l, prevR = q.r;
		ans[q.index] = st.leq(q.y) - st.leq(q.x-1);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> A(n);
	for(int & ai : A){
		cin >> ai;
	}
	int S = n / sqrt(q);
	vector<query> queries(q);
	for(int i = 0; i < q; ++i){
		cin >> queries[i].l >> queries[i].r >> queries[i].x >> queries[i].y;
		--queries[i].l;
		--queries[i].r;
		queries[i].S = S;
		queries[i].index = i;
	}
	auto ans = MO(A, queries);
	for(int a : ans){
		cout << a << "\n";
	}
	return 0;
}