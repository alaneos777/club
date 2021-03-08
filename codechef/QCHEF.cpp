#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
using namespace std;

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct query{
	int l, r, index;
	int64_t ord;
	query() {}
	query(int l, int r, int index): l(l), r(r), index(index) {
		ord = gilbertOrder(l, r, 21, 0);
	}
	bool operator<(const query & q) const{
		return ord < q.ord;
	}
};

struct SegmentTree{
	int N;
	vector<int> ST;

	SegmentTree(int N): N(N), ST(N << 1){}

	void update(int i, int value){
		ST[i += N] = value;
		while(i >>= 1)
			ST[i] = max(ST[i << 1], ST[i << 1 | 1]);
	}
};

struct node{
	int val;
	node* prev;
	node* next;
	node(): val(0), prev(NULL), next(NULL) {}
	node(int val): val(val), prev(NULL), next(NULL) {}
};

const int M = 1e5 + 10;
int pt = M-1;
node nodeCache[M];
stack<node*> recycleBin;

node* newNode(int val){
	if(recycleBin.empty()){
		++pt;
		if(pt == M) pt = 0;
		nodeCache[pt].val = val;
		nodeCache[pt].prev = nodeCache[pt].next = NULL;
		return &nodeCache[pt];
	}else{
		node* tmp = recycleBin.top();
		recycleBin.pop();
		tmp->val = val;
		tmp->prev = tmp->next = NULL;
		return tmp;
	}
}

void deleteNode(node* p){
	recycleBin.push(p);
}

struct lista{
	node* first;
	node* last;
	lista(): first(NULL), last(NULL) {}
	bool empty(){return first == NULL && last == NULL;}
	int back(){return last->val;}
	int front(){return first->val;}

	void insertBefore(int val, node* p){
		node* nuevo = newNode(val);
		nuevo->next = p;
		if(p->prev == NULL){
			nuevo->prev = NULL;
			first = nuevo;
		}else{
			nuevo->prev = p->prev;
			p->prev->next = nuevo;
		}
		p->prev = nuevo;
	}

	void insertAfter(int val, node* p){
		node* nuevo = newNode(val);
		nuevo->prev = p;
		if(p->next == NULL){
			nuevo->next = NULL;
			last = nuevo;
		}else{
			nuevo->next = p->next;
			p->next->prev = nuevo;
		}
		p->next = nuevo;
	}

	void push_front(int val){
		if(first == NULL){
			node* nuevo = newNode(val);
			first = last = nuevo;
		}else{
			insertBefore(val, first);
		}
	}

	void push_back(int val){
		if(last == NULL){
			push_front(val);
		}else{
			insertAfter(val, last);
		}
	}

	void remove(node* p){
		if(p->prev == NULL){
			first = p->next;
		}else{
			p->prev->next = p->next;
		}
		if(p->next == NULL){
			last = p->prev;
		}else{
			p->next->prev = p->prev;
		}
		deleteNode(p);
	}

	void pop_front(){
		remove(first);
	}

	void pop_back(){
		remove(last);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	unordered_map<int, int> ids;
	int sz = 0;
	vector<int> a(n);
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		if(ids.count(ai) == 0) ids[ai] = sz++;
		a[i] = ids[ai];
	}
	vector<query> queries;
	for(int i = 0; i < k; ++i){
		int l, r;
		cin >> l >> r;
		queries.emplace_back(l-1, r-1, i);
	}
	sort(queries.begin(), queries.end());
	vector<int> answers(k);
	vector<lista> freq(sz);
	int prevL = 0, prevR = -1, i, j;
	SegmentTree maxi(sz);
	for(const query& q : queries){
		for(i = prevL, j = min(prevR, q.l - 1); i <= j; ++i){
			freq[a[i]].pop_front();
			if(freq[a[i]].empty()) maxi.update(a[i], 0);
			else maxi.update(a[i], freq[a[i]].back() - freq[a[i]].front());
		}
		for(i = prevL - 1; i >= q.l; --i){
			freq[a[i]].push_front(i);
			maxi.update(a[i], freq[a[i]].back() - freq[a[i]].front());
		}
		for(i = max(prevR + 1, q.l); i <= q.r; ++i){
			freq[a[i]].push_back(i);
			maxi.update(a[i], freq[a[i]].back() - freq[a[i]].front());
		}
		for(i = prevR; i >= q.r + 1; --i){
			freq[a[i]].pop_back();
			if(freq[a[i]].empty()) maxi.update(a[i], 0);
			else maxi.update(a[i], freq[a[i]].back() - freq[a[i]].front());
		}
		answers[q.index] = maxi.ST[1];
		prevL = q.l, prevR = q.r;
	}
	for(int x : answers){
		cout << x << "\n";
	}
	return 0;
}