#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

const int M = 26;
struct node{
	vector<int> child;
	int p = -1;
	char c = 0;
	int suffixLink = -1, endLink = -1;
	int id = -1;

	node(int p = -1, char c = 0) : p(p), c(c){
		child.resize(M, -1);
	}
};

struct AhoCorasick{
	vector<node> t;
	vector<int> lenghts;
	int wordCount = 0;

	AhoCorasick(){
		t.emplace_back();
	}

	void add(const string & s){
		int u = 0;
		for(char c : s){
			if(t[u].child[c-'A'] == -1){
				t[u].child[c-'A'] = t.size();
				t.emplace_back(u, c);
			}
			u = t[u].child[c-'A'];
		}
		t[u].id = wordCount++;
		lenghts.push_back(s.size());
	}

	void link(int u){
		if(u == 0){
			t[u].suffixLink = 0;
			t[u].endLink = 0;
			return;
		}
		if(t[u].p == 0){
			t[u].suffixLink = 0;
			if(t[u].id != -1) t[u].endLink = u;
			else t[u].endLink = t[t[u].suffixLink].endLink;
			return;
		}
		int v = t[t[u].p].suffixLink;
		char c = t[u].c;
		while(true){
			if(t[v].child[c-'A'] != -1){
				t[u].suffixLink = t[v].child[c-'A'];
				break;
			}
			if(v == 0){
				t[u].suffixLink = 0;
				break;
			}
			v = t[v].suffixLink;
		}
		if(t[u].id != -1) t[u].endLink = u;
		else t[u].endLink = t[t[u].suffixLink].endLink;
	}

	void build(){
		queue<int> Q;
		Q.push(0);
		while(!Q.empty()){
			int u = Q.front(); Q.pop();
			link(u);
			for(int v = 0; v < M; ++v)
				if(t[u].child[v] != -1)
					Q.push(t[u].child[v]);
		}
	}

	vector<pii> match(const string & text){
		int u = 0;
		vector<pii> ans;
		for(int j = 0; j < text.size(); ++j){
			int i = text[j] - 'A';
			while(true){
				if(t[u].child[i] != -1){
					u = t[u].child[i];
					break;
				}
				if(u == 0) break;
				u = t[u].suffixLink;
			}
			int v = u;
			while(true){
				v = t[v].endLink;
				if(v == 0) break;
				int idx = j + 1 - lenghts[t[v].id];
				ans.push_back({t[v].id, idx});
				v = t[v].suffixLink;
			}
		}
		return ans;
	}
};

struct point{
	int x, y;
};

struct result{
	char o = 'A';
	string str = "";
	point start;
	result(char o){
		this->o = o;
	}
	point realPos(int pos){
		if(o == 'A') return {start.x - pos, start.y};
		if(o == 'E') return {start.x + pos, start.y};
		if(o == 'G') return {start.x, start.y - pos};
		if(o == 'C') return {start.x, start.y + pos};
		if(o == 'D') return {start.x + pos, start.y + pos};
		if(o == 'H') return {start.x - pos, start.y - pos};
		if(o == 'B') return {start.x - pos, start.y + pos};
		if(o == 'F') return {start.x + pos, start.y - pos};
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		AhoCorasick ac;
		int w, h, c;
		cin >> w >> h >> c;
		vector<vector<char>> grid(w, vector<char>(h));
		for(int i = 0; i < w; ++i){
			for(int j = 0; j < h; ++j){
				cin >> grid[i][j];
			}
		}
		vector<string> words(c);
		for(int i = 0; i < c; ++i){
			cin >> words[i];
			ac.add(words[i]);
		}
		ac.build();

		vector<result> results;
		int i, j;

		//C, G
		for(i = 0; i < w; ++i){
			result r1('C'), r2('G');
			for(j = 0; j < h; ++j){
				r1.str.append(1, grid[i][j]);
			}
			r2.str = r1.str; reverse(r2.str.begin(), r2.str.end());
			r1.start = {i, 0}; r2.start = {i, h-1};
			results.push_back(r1); results.push_back(r2);
		}

		//E, A
		for(j = 0; j < h; ++j){
			result r1('E'), r2('A');
			for(i = 0; i < w; ++i){
				r1.str.append(1, grid[i][j]);
			}
			r2.str = r1.str; reverse(r2.str.begin(), r2.str.end());
			r1.start = {0, j}; r2.start = {w-1, j};
			results.push_back(r1); results.push_back(r2);
		}

		//D, H part 1
		for(i = w-1; i >= 0; --i){
			result r1('D'), r2('H');
			for(j = 0; i + j < w && j < h; ++j){
				r1.str.append(1, grid[i + j][j]);
			}
			r2.str = r1.str; reverse(r2.str.begin(), r2.str.end());
			r1.start = {i, 0}; r2.start = {i + j - 1, j - 1};
			results.push_back(r1); results.push_back(r2);
		}
		//D, H part 2
		for(j = 1; j < h; ++j){
			result r1('D'), r2('H');
			for(i = 0; i < w && i + j < h; ++i){
				r1.str.append(1, grid[i][i + j]);
			}
			r2.str = r1.str; reverse(r2.str.begin(), r2.str.end());
			r1.start = {0, j}; r2.start = {i - 1, i + j - 1};
			results.push_back(r1); results.push_back(r2);
		}

		//B, F part 1
		for(i = 0; i < w; ++i){
			result r1('B'), r2('F');
			for(j = 0; j < h && 0 <= i - j; ++j){
				r1.str.append(1, grid[i - j][j]);
			}
			r2.str = r1.str; reverse(r2.str.begin(), r2.str.end());
			r1.start = {i, 0}; r2.start = {i - j + 1, j - 1};
			results.push_back(r1); results.push_back(r2);
		}
		//B, F part 2
		for(j = 1; j < h; ++j){
			result r1('B'), r2('F');
			for(i = w-1; i >= 0 && j + w-1 - i < h; --i){
				r1.str.append(1, grid[i][j + w-1 - i]);
			}
			r2.str = r1.str; reverse(r2.str.begin(), r2.str.end());
			r1.start = {w-1, j}; r2.start = {i + 1, j + w-1 - (i + 1)};
			results.push_back(r1); results.push_back(r2);
		}

		vector<pair<point, char>> ans(c);

		for(auto & r : results){
			vector<pii> matches = ac.match(r.str);
			for(auto & par : matches){
				int idx = par.first;
				point location = r.realPos(par.second);
				ans[idx] = {location, r.o};
			}
		}

		for(auto & par : ans){
			cout << par.first.x << " " << par.first.y << " " << par.second << "\n";
		}
		if(t) cout << "\n";
	}
	return 0;
}