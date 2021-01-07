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

int64_t rec(node *root){
	nonTerminal lhs = root->lhs;
	auto rhs = *(root->rhs);
	if(lhs == 'F'){
		if(rhs.size() == 1){
			return rhs[0].token;
		}else{
			return rec(root->children[0]);
		}
	}else if(lhs == 'T'){
		if(rhs.size() == 1){
			return rec(root->children[0]);
		}else{
			int64_t A = rec(root->children[0]);
			int64_t B = rec(root->children[1]);
			return A+B;
		}
	}else if(lhs == 'E'){
		if(rhs.size() == 1){
			return rec(root->children[0]);
		}else{
			int64_t A = rec(root->children[0]);
			int64_t B = rec(root->children[1]);
			return A*B;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	grammar g;
	g['E'].push_back({symbol('E'), symbol(11), symbol('T')});
	g['E'].push_back({symbol('T')});
	g['T'].push_back({symbol('T'), symbol(10), symbol('F')});
	g['T'].push_back({symbol('F')});
	g['F'].push_back({symbol(12), symbol('E'), symbol(13)});
	for(int d = 0; d <= 9; ++d){
		g['F'].push_back({symbol(d)});
	}
	string expr;
	int64_t ans = 0;
	while(getline(cin, expr)){
		vector<terminal> str;
		for(char c : expr){
			if(c == '+') str.push_back(10);
			if(c == '*') str.push_back(11);
			if(c == '(') str.push_back(12);
			if(c == ')') str.push_back(13);
			if('0' <= c && c <= '9') str.push_back(int(c-'0'));
		}
		node* tree = earley(g, 'E', str)[0];
		int64_t eval = rec(tree);
		ans += eval;
	}
	cout << ans << endl;
	return 0;
}