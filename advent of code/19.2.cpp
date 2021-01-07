#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

using nonTerminal = int;
using terminal = char;
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

vector<symbol> split(const string & s){
	stringstream ss(s);
	int x;
	vector<symbol> ans;
	while(ss >> x){
		ans.push_back(symbol(x));
	}
	return ans;
}

const regex reg0("([0-9]+): \"([a-z])\"");
const regex reg1("([0-9]+): (.+) \\| (.+)");
const regex reg2("([0-9]+): (.+)");

int main(){
	int ans = 0;
	grammar g;
	string line;
	while(getline(cin, line)){
		if(line == "") continue;
		if(line == "8: 42") line = "8: 42 | 42 8";
		if(line == "11: 42 31") line = "11: 42 31 | 42 11 31";
		if(line.find(":") != string::npos){
			smatch m;
			if(regex_match(line, m, reg0)){
				int lhs = stoi(m.str(1));
				g[lhs].push_back({symbol(m.str(2)[0])});
			}else if(regex_match(line, m, reg1)){
				int lhs = stoi(m.str(1));
				g[lhs].push_back(split(m.str(2)));
				g[lhs].push_back(split(m.str(3)));
			}else if(regex_match(line, m, reg2)){
				int lhs = stoi(m.str(1));
				g[lhs].push_back(split(m.str(2)));
			}
		}else{
			vector<terminal> str;
			for(char c : line){
				str.push_back(c);
			}
			if(earley(g, 0, str).size() > 0){
				ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}