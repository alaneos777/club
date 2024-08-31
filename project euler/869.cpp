#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i%p == 0) break;
		}
	}
	return primes;
}

#define node_cnt(n) ((n) ? (n)->cnt : 0)
#define node_score(n) ((n) ? (n)->score : 0)

struct node{
	node* left;
	node* right;
	int cnt;
	lli score;
	bool isNumber;
	node(): left(NULL), right(NULL), cnt(0), score(0), isNumber(false) {}

	void update(){
		cnt = isNumber + node_cnt(left) + node_cnt(right);
		score = node_score(left) + node_score(right) + max(node_cnt(left), node_cnt(right));
	}
};

void insert(node* n, int val){
	if(val == 0){
		n->isNumber = true;
	}else{
		if(val&1){
			if(!n->right) n->right = new node();
			insert(n->right, val>>1);
		}else{
			if(!n->left) n->left = new node();
			insert(n->left, val>>1);
		}
	}
	n->update();
}

ld E(int N){
	vector<int> primes = sieve(N);
	node* tree = new node();
	for(int p : primes){
		insert(tree, p);
	}
	return ld(tree->score) / ld(primes.size());
}

int main(){
	int N = 1e8;
	cout << fixed << setprecision(8) << E(N) << "\n";
	return 0;
}