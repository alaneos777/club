#include <bits/stdc++.h>
using namespace std;

using nonTerminal = char;
using terminal = int;
struct symbol{
	bool isTerminal;
	union{
		nonTerminal rule;
		terminal token;
	};
	symbol(){}
	symbol(nonTerminal rule): isTerminal(false), rule(rule){}
	symbol(terminal token): isTerminal(true), token(token){}
};
using production = vector<symbol>;
using grammar = map<nonTerminal, vector<production>>;

struct item{
	nonTerminal lhs;
	production *rhs;
	int start, position;
	item *prev, *complete;
	item(){}
	item(nonTerminal lhs, production *rhs, int start, int position): lhs(lhs), rhs(rhs), start(start), position(position){}
	symbol nextPosition() const{
		if(position < (*rhs).size()) return (*rhs)[position];
		else return symbol(-1);
	}
	bool end() const{
		return position == (*rhs).size();
	}
	bool operator<(const item & i) const{
		if(lhs != i.lhs) return lhs < i.lhs;
		if(rhs != i.rhs) return rhs < i.rhs;
		if(start != i.start) return start < i.start;
		return position < i.position;
	}
};

struct node{
	nonTerminal lhs;
	production *rhs;
	deque<node*> children;
	node(){}
	node(nonTerminal lhs, production *rhs): lhs(lhs), rhs(rhs){}
};

node* createTree(item *root){
	node *ans = new node(root->lhs, root->rhs);
	for(item *curr = root; curr && curr->position > 0; curr = curr->prev){
		if(curr->complete){
			ans->children.push_front(createTree(curr->complete));
		}
	}
	return ans;
}

void printTree(node *root, int lvl = 0){
	if(!root) return;
	for(int i = 0; i < lvl; ++i) cout << " ";
	cout << root->lhs << " -> ";
	for(auto elem : *(root->rhs)){
		if(elem.isTerminal) cout << elem.token;
		else cout << elem.rule;
	}
	cout << "\n";
	for(node *child : root->children){
		printTree(child, lvl + 1);
	}
}

vector<node*> earley(grammar & g, nonTerminal S, const vector<terminal> & str){
	int n = str.size();
	vector<deque<item>> dp(n+1);
	vector<set<item>> dpSet(n+1);
	for(production & rule : g.at(S)){
		item newItem(S, &rule, 0, 0);
		dp[0].push_back(newItem), dpSet[0].insert(newItem);
	}

	for(int i = 0; i <= n; ++i){
		terminal w = (i < n ? str[i] : -1);
		set<nonTerminal> predicted;
		for(int j = 0; j < dp[i].size(); ++j){
			item & currItem = dp[i][j];
			symbol next = currItem.nextPosition();
			if(currItem.end()){ //completition
				for(item & it : dp[currItem.start]){
					if(it.nextPosition().rule == currItem.lhs){
						item newItem = it;
						++newItem.position;
						newItem.prev = &it;
						newItem.complete = &currItem;
						if(!dpSet[i].count(newItem)) dp[i].push_back(newItem), dpSet[i].insert(newItem);
					}
				}
			}else if(next.isTerminal){ //scanner
				if(next.token == w){
					item newItem = currItem;
					++newItem.position;
					newItem.prev = &currItem;
					newItem.complete = NULL;
					if(!dpSet[i+1].count(newItem)) dp[i+1].push_back(newItem), dpSet[i+1].insert(newItem);
				}
			}else{ //prediction
				if(!predicted.count(next.rule)){
					for(production & rule : g.at(next.rule)){
						item newItem(next.rule, &rule, i, 0);
						if(!dpSet[i].count(newItem)) dp[i].push_back(newItem), dpSet[i].insert(newItem);
					}
					predicted.insert(next.rule);
				}
			}
		}
	}

	vector<node*> nodes;
	for(item & currItem : dp[n]){
		if(currItem.end() && currItem.start == 0 && currItem.lhs == S){
			nodes.push_back(createTree(&currItem));
		}
	}
	return nodes;
}

/*
0 |
1 $
2 :
3 {
4 }
5 number
*/

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	grammar g;
	map<char, terminal> terminals = {{'|', 0}, {'$', 1}, {':', 2}, {'{', 3}, {'}', 4}};

	g['M'].push_back({symbol('H'), symbol(0), symbol('P')});
	g['M'].push_back({symbol(0), symbol('M')});
	g['M'].push_back({symbol('P')});

	g['H'].push_back({symbol('M')});
	g['H'].push_back({symbol(1)});

	g['P'].push_back({symbol('P'), symbol(2), symbol('T')});
	g['P'].push_back({symbol('T')});

	g['T'].push_back({symbol(3), symbol('M'), symbol(4)});
	g['T'].push_back({symbol(5)});

	vector<terminal> str;
	string t;
	getline(cin, t);
	int i = 0;
	while(i < t.size()){
		if(t[i] == ' '){
			i++;
		}else if('0' <= t[i] && t[i] <= '9'){
			str.push_back(5);
			while(i < t.size() && '0' <= t[i] && t[i] <= '9') i++;
		}else{
			str.push_back(terminals[t[i]]);
			i++;
		}
	}

	vector<node*> nodes = earley(g, 'M', str);
	if(nodes.size()){
		cout << "YES\n";
		printTree(nodes[0]);
	}else{
		cout << "NO\n";
	}
	return 0;
}