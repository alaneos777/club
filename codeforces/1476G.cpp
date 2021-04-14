#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

int S = 0;
struct query{
	int l, r, k, time, index;
	query() {}
	query(int l, int r, int k, int time, int index): l(l), r(r), k(k), time(time), index(index) {}
	bool operator<(const query & q) const{
		if(time/S != q.time/S) return time/S < q.time/S;
		if(l/S != q.l/S) return l/S < q.l/S;
		if((l/S) & 1) return r < q.r;
		return r > q.r;
	}
};

struct update{
	int prev, next, pos;
	update(){}
	update(int prev, int next, int pos): prev(prev), next(next), pos(pos) {}
};

const int M = 1e5, inf = 1e9;

template<typename T>
struct node{
	T val;
	node* prev;
	node* next;
	node(): val(T()), prev(NULL), next(NULL) {}
	node(const T& val): val(val), prev(NULL), next(NULL) {}
};

template<typename T>
struct lista{
	int pt = M-1;
	node<T> nodeCache[M];
	stack<node<T>*> recycleBin;

	node<T>* newNode(const T& val){
		if(recycleBin.empty()){
			++pt;
			if(pt == M) pt = 0;
			nodeCache[pt].val = val;
			nodeCache[pt].prev = nodeCache[pt].next = NULL;
			return &nodeCache[pt];
		}else{
			node<T>* tmp = recycleBin.top();
			recycleBin.pop();
			tmp->val = val;
			tmp->prev = tmp->next = NULL;
			return tmp;
		}
	}

	void deleteNode(node<T>* p){
		recycleBin.push(p);
	}

	node<T>* first;
	node<T>* last;
	int sz;
	lista(): first(NULL), last(NULL), sz(0) {}
	bool empty() const{return first == NULL && last == NULL;}
	T back() const{return last->val;}
	T front() const{return first->val;}
	int size() const{return sz;}

	node<T>* insertBefore(const T& val, node<T>* p){
		node<T>* nuevo = newNode(val);
		sz++;
		nuevo->next = p;
		if(p->prev == NULL){
			nuevo->prev = NULL;
			first = nuevo;
		}else{
			nuevo->prev = p->prev;
			p->prev->next = nuevo;
		}
		p->prev = nuevo;
		return nuevo;
	}

	node<T>* insertAfter(const T& val, node<T>* p){
		node<T>* nuevo = newNode(val);
		sz++;
		nuevo->prev = p;
		if(p->next == NULL){
			nuevo->next = NULL;
			last = nuevo;
		}else{
			nuevo->next = p->next;
			p->next->prev = nuevo;
		}
		p->next = nuevo;
		return nuevo;
	}

	node<T>* push_front(const T& val){
		if(first == NULL){
			node<T>* nuevo = newNode(val);
			sz++;
			return first = last = nuevo;
		}else{
			return insertBefore(val, first);
		}
	}

	node<T>* push_back(const T& val){
		if(last == NULL){
			return push_front(val);
		}else{
			return insertAfter(val, last);
		}
	}

	void remove(node<T>* p){
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
		sz--;
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
	int n, m;
	cin >> n >> m;
	S = powl(2ll*n*n, 1.0l/3.0l);
	vector<int> a(n);
	for(int& ai : a) cin >> ai;
	vector<int> prev_a = a;
	vector<query> queries;
	vector<update> updates;
	for(int i = 0; i < m; ++i){
		int t;
		cin >> t;
		if(t == 1){
			int l, r, k;
			cin >> l >> r >> k;
			queries.emplace_back(l-1, r-1, k, updates.size(), queries.size());
		}else{
			int p, x;
			cin >> p >> x;
			--p;
			updates.emplace_back(prev_a[p], x, p);
			prev_a[p] = x;
		}
	}

	sort(queries.begin(), queries.end());
	vector<int> answers(queries.size());
	vector<int> freq(M+1);
	lista<pii> lst;
	vector<node<pii>*> mp(M+1);
	mp[0] = lst.push_back({0, inf});
	int prevL = 0, prevR = -1, updatesCnt = 0;

	auto remove = [&](int v){
		int& f = freq[v];
		if(!mp[f-1]) mp[f-1] = lst.insertBefore({f-1, 0}, mp[f]);
		mp[f-1]->val.second++;
		if(--mp[f]->val.second == 0) lst.remove(mp[f]), mp[f] = NULL;
		f--;
	};

	auto add = [&](int v){
		int& f = freq[v];
		if(!mp[f+1]) mp[f+1] = lst.insertAfter({f+1, 0}, mp[f]);
		mp[f+1]->val.second++;
		if(--mp[f]->val.second == 0) lst.remove(mp[f]), mp[f] = NULL;
		f++;
	};

	auto change = [&](int pos, int next){
		if(prevL <= pos && pos <= prevR){
			remove(a[pos]);
			a[pos] = next;
			add(a[pos]);
		}
		a[pos] = next;
	};

	for(const query& q : queries){
		while(updatesCnt < q.time){
			change(updates[updatesCnt].pos, updates[updatesCnt].next);
			updatesCnt++;
		}

		while(updatesCnt > q.time){
			updatesCnt--;
			change(updates[updatesCnt].pos, updates[updatesCnt].prev);
		}

		for(int i = prevL, j = min(prevR, q.l - 1); i <= j; ++i) remove(a[i]);
		for(int i = prevL - 1; i >= q.l; --i) add(a[i]);
		for(int i = max(prevR + 1, q.l); i <= q.r; ++i) add(a[i]);
		for(int i = prevR; i >= q.r + 1; --i) remove(a[i]);

		int diff = inf;
		vector<pii> v;
		for(node<pii>* p = lst.first->next; p; p = p->next){
			v.emplace_back(p->val);
		}
		int sz = v.size();
		vector<int> start(sz), end(sz);
		for(int i = 0; i < sz-1; ++i){
			start[i+1] = start[i] + v[i].second;
			end[i] = start[i+1] - 1;
		}
		end[sz-1] = start[sz-1] + v[sz-1].second-1;
		for(int i = 0; i < sz; ++i){
			int pos = start[i] + q.k-1;
			int j = lower_bound(end.begin()+i, end.end(), pos)-end.begin();
			if(j < sz){
				diff = min(diff, v[j].first - v[i].first);
			}else{
				break;
			}
		}
		if(diff == inf) diff = -1;
		answers[q.index] = diff;
		prevL = q.l, prevR = q.r;
	}

	for(int ans : answers){
		cout << ans << "\n";
	}
	return 0;
}