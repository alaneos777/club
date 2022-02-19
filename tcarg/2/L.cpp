#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using grid = vector<string>;

bool isletter(char c){
	return 'A' <= c && c <= 'Z';
}

string s;
int pos = 0;
char eat(char c){
	assert(pos < s.size() && s[pos] == c);
	pos++;
	return c;
}

grid I();
grid E();
grid T();
grid A(bool&);
grid L();

grid I(){
	grid g = E();
	g[1] = "S->" + g[1] + "->F";
	for(int i = 0; i < g.size(); ++i){
		if(i == 1) continue;
		g[i] = "   " + g[i] + "   ";
	}
	return g;
}

grid OR(const vector<grid>& grids){
	if(grids.size() == 1) return grids[0];
	int m = 0, n = 0;
	for(const grid&g : grids){
		n = max(n, (int)g[0].size());
		m += g.size()+1;
	}
	m--;
	grid ans(m, string(n+6, ' '));
	int row = 1;
	for(int k = 0; k < grids.size(); ++k){
		ans[row][0] = '+'; ans[row][1] = '-'; ans[row][2] = '>';
		for(int j = grids[k][0].size()+3; j < n+4; ++j){
			ans[row][j] = '-';
		}
		ans[row][n+4] = '>'; ans[row][n+5] = '+';
		for(int i = 0; i < grids[k].size(); ++i){
			for(int j = 0; j < grids[k][0].size(); ++j){
				ans[i+row-1][j+3] = grids[k][i][j];
			}
		}
		if(k+1 < grids.size()){
			for(int i = 1; i < grids[k].size()+1; ++i){
				ans[row+i][0] = ans[row+i][n+5] = '|';
			}
		}
		row += grids[k].size()+1;
	}
	return ans;
}

grid E(){
	vector<grid> ans = {T()};
	while(pos < s.size() && s[pos] == '|'){
		eat('|');
		ans.push_back(T());
	}
	return OR(ans);
}

grid concat(grid g, const grid& h, bool flag){
	if(!flag){
		int n = g[0].size();
		g.resize(max(g.size(), h.size()));
		for(string&row : g){
			row.resize(n+2, ' ');
		}
		g[1][g[1].size()-2] = '-';
		g[1][g[1].size()-1] = '>';
		for(int i = 0; i < g.size() && i < h.size(); ++i){
			g[i] += h[i];
		}
		for(string&row : g){
			row.resize(n+h[0].size()+2, ' ');
		}
		return g;
	}else{
		int n = g[0].size();
		g[1][n-2] = h[1][2];
		g[0][n-1] = g[2][n-1] = '-';
		g[1][n-1] = ' ';
		for(int i = 0; i < g.size(); ++i){
			if(i < 3) g[i] += "+";
			else g[i] += " ";
		}
		return g;
	}
}

grid T(){
	bool flag;
	grid ans = A(flag);
	while(pos < s.size() && (isletter(s[pos]) || s[pos] == '(')){
		bool newflag;
		grid rhs = A(newflag);
		ans = concat(ans, rhs, flag && newflag);
		flag = newflag;
	}
	return ans;
}

grid closure(const grid& g, char op){
	int m = g.size(), n = g[0].size();
	if(op == '+'){
		grid ans(m+2, string(n+6, ' '));
		ans[1][0] = '+'; ans[1][1] = '-'; ans[1][2] = '>';
		ans[1][n+3] = '-'; ans[1][n+4] = '>'; ans[1][n+5] = '+';
		for(int i = 2; i < m+1; ++i){
			ans[i][0] = ans[i][n+5] = '|';
		}
		ans[m+1][0] = '+'; ans[m+1][1] = '<'; ans[m+1][n+5] = '+';
		for(int j = 2; j < n+5; ++j){
			ans[m+1][j] = '-';
		}
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				ans[i][j+3] = g[i][j];
			}
		}
		return ans;
	}else if(op == '?'){
		grid ans(m+3, string(n+6, ' '));
		ans[1][0] = '+'; ans[1][n+4] = '>'; ans[1][n+5] = '+';
		for(int j = 1; j < n+4; ++j){
			ans[1][j] = '-';
		}
		ans[2][0] = ans[2][n+5] = '|';
		ans[3][0] = ans[3][n+5] = '|';
		ans[4][0] = '+'; ans[4][1] = '-'; ans[4][2] = '>';
		ans[4][n+3] = '-'; ans[4][n+4] = '>'; ans[4][n+5] = '+';
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				ans[i+3][j+3] = g[i][j];
			}
		}
		return ans;
	}else if(op == '*'){
		grid ans(m+5, string(n+6, ' '));
		ans[1][0] = '+'; ans[1][n+4] = '>'; ans[1][n+5] = '+';
		for(int j = 1; j < n+4; ++j){
			ans[1][j] = '-';
		}
		ans[2][0] = ans[2][n+5] = '|';
		ans[3][0] = ans[3][n+5] = '|';
		ans[4][0] = '+'; ans[4][1] = '-'; ans[4][2] = '>';
		ans[4][n+3] = '-'; ans[4][n+4] = '>'; ans[4][n+5] = '+';
		for(int i = 5; i < m+4; ++i){
			ans[i][0] = ans[i][n+5] = '|';
		}
		ans[m+4][0] = '+'; ans[m+4][1] = '<'; ans[m+4][n+5] = '+';
		for(int j = 2; j < n+5; ++j){
			ans[m+4][j] = '-';
		}
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				ans[i+3][j+3] = g[i][j];
			}
		}
		return ans;
	}
}

grid A(bool& single){
	single = false;
	char x;
	grid ans;
	if(isletter(s[pos])){
		ans = L();
		single = true;
	}else if(s[pos] == '('){
		eat('(');
		ans = E();
		eat(')');
	}
	while(pos < s.size() && (s[pos] == '+' || s[pos] == '*' || s[pos] == '?')){
		single = false;
		char op = s[pos];
		eat(op);
		ans = closure(ans, op);
	}
	return ans;
}

grid L(){
	char c = s[pos];
	eat(c);
	return {"+---+", string("+ ") + c + " +", "+---+"};
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> s;
	auto ans = I();
	cout << ans.size() << " " << ans[0].size() << "\n";
	for(const auto&row : ans){
		for(char c : row){
			cout << c;
		}
		cout << "\n";
	}
	return 0;
}