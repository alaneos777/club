#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <utility>
#include <string>
using namespace std;

int r, c, d, e;
char grid[50][50];

int x, y, dir;

int movs[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
map<char, int> dirs = {{'e', 0}, {'n', 1}, {'w', 2}, {'s', 3}};
char dirs_inv[4] = {'e', 'n', 'w', 's'};

bool valid(int i, int j){
	return 1 <= i && i <= r && 1 <= j && j <= c && grid[i][j] == '.';
}

bool check(char c){
	if(c == 'b'){
		return !valid(x + movs[dir][0], y + movs[dir][1]);
	}else if(c == 'n'){
		return dir == dirs['n'];
	}else if(c == 's'){
		return dir == dirs['s'];
	}else if(c == 'e'){
		return dir == dirs['e'];
	}else if(c == 'w'){
		return dir == dirs['w'];
	}
}

struct instruction{
	char type, arg;
	bool neg;
	int pos;
	instruction(char type): type(type){}
	instruction(char type, char arg): type(type), arg(arg){}
	instruction(char type, char arg, bool neg, int pos): type(type), arg(arg), neg(neg), pos(pos){}
};

int limit = 1.61e8;

string cad;
int pos;
int pc;
vector<instruction> rom;
map<char, int> label;
stack<int> st;

int program();
int command();

int program(){
	if(pos == cad.size()) return 0;
	else if(cad[pos] == 'm' || cad[pos] == 'l' || cad[pos] == 'i' || cad[pos] == 'u' || isupper(cad[pos])){
		int cnt = 0;
		cnt += command();
		cnt += program();
		return cnt;
	}else{
		return 0;
	}
}

int command(){
	if(cad[pos] == 'm'){
		++pos;
		rom.emplace_back('m');
		return 1;
	}else if(cad[pos] == 'l'){
		++pos;
		rom.emplace_back('l');
		return 1;
	}else if(isupper(cad[pos])){
		char id = cad[pos];
		++pos;
		rom.emplace_back('c', id); //call id
		return 1;
	}else if(cad[pos] == 'i'){
		++pos;
		char flag = cad[pos];
		pos += 2;
		rom.emplace_back('i', flag, true, 0); //if !flag goto pos
		int sz1 = program();
		pos += 2;
		rom.emplace_back('g', 0); //goto pos
		int sz2 = program();
		rom[rom.size() - sz2 - 1 - sz1 - 1].pos = rom.size() - sz2;
		rom[rom.size() - sz2 - 1].pos = rom.size();
		++pos;
		return sz1 + sz2 + 2;
	}else if(cad[pos] == 'u'){
		++pos;
		char flag = cad[pos];
		pos += 2;
		rom.emplace_back('i', flag, false, 0); //if flag goto pos
		int sz = program();
		++pos;
		rom.emplace_back('g', 0, 0, rom.size() - sz - 1); //goto pos
		rom[rom.size() - 1 - sz - 1].pos = rom.size();
		return sz + 2;
	}
}

bool run(){
	int steps = 0;
	st = stack<int>();
	while(steps < limit){
		steps++;
		auto & curr = rom[pc++];
		if(curr.type == 'm'){
			int nX = x + movs[dir][0];
			int nY = y + movs[dir][1];
			if(valid(nX, nY)){
				x = nX;
				y = nY;
			}
		}else if(curr.type == 'l'){
			dir = (dir + 1) % 4;
		}else if(curr.type == 'c'){
			st.push(pc);
			pc = label[curr.arg];
		}else if(curr.type == 'r'){
			pc = st.top(); st.pop();
		}else if(curr.type == 'g'){
			pc = curr.pos;
		}else if(curr.type == 'i'){
			if(curr.neg){
				if(!check(curr.arg)) pc = curr.pos;
			}else{
				if(check(curr.arg)) pc = curr.pos;
			}
		}else if(curr.type == 'f'){
			return true;
		}
	}
	return false;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> r >> c >> d >> e;
	for(int i = 1; i <= r; ++i){
		for(int j = 1; j <= c; ++j){
			cin >> grid[i][j];
		}
	}
	for(int i = 0; i < d; ++i){
		string str;
		cin >> str;
		if(str.size()>=3) cad = str.substr(2);
		else cad = "";
		pos = 0;
		label[str[0]] = rom.size();
		program();
		rom.emplace_back('r');
	}
	auto copia = rom;
	for(int i = 0; i < e; ++i){
		char tmp;
		pos = 0;
		cin >> x >> y >> tmp >> cad;
		dir = dirs[tmp];
		pc = rom.size();
		program();
		rom.emplace_back('f');
		if(run())
			cout << x << " " << y << " " << dirs_inv[dir] << "\n";
		else
			cout << "inf\n";
		rom = copia;
	}
	return 0;
}