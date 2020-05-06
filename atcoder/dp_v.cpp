#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int MX = 1e5 + 10;
vector<int> adj[MX];
int ans[MX];
lli mod;

struct node{
	node *left, *right;
	short int height;
	int size;
	int value, prod;

	node(int value = 1): left(NULL), right(NULL), value(value), prod(value), height(1), size(1){}

	inline short int balance(){
		return (right ? right->height : 0) - (left ? left->height : 0);
	}

	node *maxLeftChild(){
		node *ret = this;
		while(ret->left) ret = ret->left;
		return ret;
	}
};

struct Tree{
	node *root;

	Tree(): root(NULL){}

	inline int nodeSize(node *& pos){return pos ? pos->size: 0;}
	inline int nodeHeight(node *& pos){return pos ? pos->height: 0;}
	inline int nodeProd(node *& pos){return pos ? pos->prod : 1;}

	inline void update(node *& pos){
		if(!pos) return;
		pos->height = 1 + max(nodeHeight(pos->left), nodeHeight(pos->right));
		pos->size = 1 + nodeSize(pos->left) + nodeSize(pos->right);
		pos->prod = (lli)pos->value * nodeProd(pos->left) % mod * nodeProd(pos->right) % mod;
	}

	void leftRotate(node *& x){
		node *y = x->right, *t = y->left;
		y->left = x, x->right = t;
		update(x), update(y);
		x = y;
	}

	void rightRotate(node *& y){
		node *x = y->left, *t = x->right;
		x->right = y, y->left = t;
		update(y), update(x);
		y = x;
	}

	void updateBalance(node *& pos){
		if(!pos) return;
		short int bal = pos->balance();
		if(bal > 1){
			if(pos->right->balance() < 0) rightRotate(pos->right);
			leftRotate(pos);
		}else if(bal < -1){
			if(pos->left->balance() > 0) leftRotate(pos->left);
			rightRotate(pos);
		}
	}

	void insert(node *&pos, int value){
		if(pos){
			value < pos->value ? insert(pos->left, value) : insert(pos->right, value);
			update(pos), updateBalance(pos);
		}else{
			pos = new node(value);
		}
	}

	void erase(node *&pos, int value){
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
		update(pos), updateBalance(pos);
	}

	void multiply(int value){insert(root, value);}
	void divide(int value){erase(root, value);}
	int get(){return nodeProd(root);}
};

Tree mem[MX];

inline int g(int x){
	return (1 + x) % mod;
}

Tree dfs(int u, int p){
	for(int v: adj[u]){
		if(v == p) continue;
		mem[u].multiply(g(dfs(v, u).get()));
	}
	return mem[u];
}

void dfs2(int u, int p){
	ans[u] = mem[u].get();
	for(int v : adj[u]){
		if(v == p) continue;
		int old_u = mem[u].get(), old_v = mem[v].get();
		int div_u = g(old_v);
		mem[u].divide(div_u);
		int mult_v = g(mem[u].get());
		mem[v].multiply(mult_v);
		dfs2(v, u);
		mem[v].divide(mult_v);
		mem[u].multiply(div_u);
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n >> mod;
	for(int i = 1; i <= n-1; ++i){
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 0);
	dfs2(1, 0);
	for(int v = 1; v <= n; ++v){
		cout << ans[v] << "\n";
	}
	return 0;
}