#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

stringstream ss;
char c;
int sz;

struct node{
	int val;
	node* next;
	node(int val): val(val), next(NULL){}
};
struct List{
	node *head, *tail;
	int size;
	List(): head(NULL), tail(NULL), size(0){}
	List(int val){
		node* t = new node(val);
		head = tail = t;
		size = 1;
	}
	void join(List* l){
		if(tail) tail->next = l->head;
		else head = l->head;
		tail = l->tail;
		size += l->size;
	}
};

List* solve(){
	if(c == '*'){
		ss >> c;
		sz++;
		return new List(sz-1);
	}else if(c == '('){
		ss >> c;
		bool type = 0;
		List* idxs = new List();
		while(true){
			List* tmp = solve();
			if(type == 0){
				if(idxs->size == 0 || tmp->size < idxs->size){
					idxs = tmp;
				}
			}else{
				idxs->join(tmp);
			}
			if(c == 'S'){
				ss >> c;
				type = 0;
			}else if(c == 'P'){
				ss >> c;
				type = 1;
			}else if(c == ')'){
				ss >> c;
				break;
			}
		}
		return idxs;
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	cin.ignore();
	while(t--){
		string s;
		getline(cin, s);
		s += "$";
		ss = stringstream(s);
		sz = 0;
		lli r;
		ss >> r >> c;
		List* ans = solve();
		vector<int> assignment(sz);
		int c = ans->size;
		for(node* t = ans->head; t; t = t->next){
			assignment[t->val] = c;
		}
		cout << "REVOLTING";
		for(lli ai : assignment){
			cout << " " << r*ai;
		}
		cout << "\n";
	}
	return 0;
}