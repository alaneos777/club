#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using mat = vector<vector<char>>;
using pii = pair<int, int>;
using tup = tuple<int, int, int>;

template<typename T>
vector<vector<T>> rotate(const vector<vector<T>> & grid){
	int n = grid.size();
	int pos = 0;
	vector<vector<T>> ans(n, vector<T>(n));
	for(int j = n-1; j >= 0; --j){
		for(int i = 0; i < n; ++i){
			ans[pos/n][pos%n] = grid[i][j];
			pos++;
		}
	}
	return ans;
}

template<typename T>
vector<vector<T>> rotate_flip(vector<vector<T>> grid, int rot, int flip){
	while(rot--){
		grid = rotate(grid);
	}
	if(flip){
		reverse(grid.begin(), grid.end());
	}
	return grid;
}

vector<vector<pii>> identity(int n){
	vector<vector<pii>> id(n, vector<pii>(n));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			id[i][j] = {i, j};
		}
	}
	return id;
}

vector<vector<pii>> mappings[4][2];
void pre(int n){
	for(int rot = 0; rot < 4; ++rot){
		for(int flip = 0; flip < 2; ++flip){
			mappings[rot][flip] = rotate_flip<pii>(identity(n), rot, flip);
		}
	}
}

string border(const mat & grid, int rot, int flip, int t){
	int n = grid.size();
	string ans;
	const auto & mp = mappings[rot][flip];
	if(t == 0){
		for(int i = 0; i < n; ++i){
			pii pos = mp[0][i];
			ans += grid[pos.first][pos.second];
		}
	}else if(t == 3){
		for(int i = 0; i < n; ++i){
			pii pos = mp[i][n-1];
			ans += grid[pos.first][pos.second];
		}
	}else if(t == 2){
		for(int i = 0; i < n; ++i){
			pii pos = mp[n-1][i];
			ans += grid[pos.first][pos.second];
		}
	}else if(t == 1){
		for(int i = 0; i < n; ++i){
			pii pos = mp[i][0];
			ans += grid[pos.first][pos.second];
		}
	}
	return ans;
}

vector<pii> search(const mat & grid, const vector<string> & pattern){
	vector<pii> ans;
	int n = grid.size(), h = pattern.size(), w = pattern[0].size();
	for(int r = 0; r+h-1 < n; ++r){
		for(int c = 0; c+w-1 < n; ++c){
			bool valid = true;
			for(int i = r; i < r+h; ++i){
				for(int j = c; j < c+w; ++j){
					if(pattern[i-r][j-c] == '#') valid &= (grid[i][j] == '#');
				}
			}
			if(valid){
				ans.emplace_back(r, c);
			}
		}
	}
	return ans;
}

int main(){
	string line;
	int id;
	int area = 0;
	map<int, mat> grids;
	while(getline(cin, line)){
		if(line == "") continue;
		if(line.substr(0, 4) == "Tile"){
			line = line.substr(5);
			line = line.substr(0, line.size()-1);
			id = stoi(line);
			area++;
		}else{
			vector<char> row;
			for(char c : line){
				row.push_back(c);
			}
			grids[id].push_back(row);
		}
	}

	int n = sqrt(area);
	int l = grids.begin()->second.size();
	pre(l);
	vector<vector<tup>> ans(n, vector<tup>(n));
	set<int> avaliable;
	for(const auto & par : grids){
		avaliable.insert(par.first);
	}

	const vector<string> pattern = {
	"                  # ",
	"#    ##    ##    ###",
	" #  #  #  #  #  #   "};
	auto part2 = [&](const mat & grid){
		int n = grid.size(), h = pattern.size(), w = pattern[0].size();
		vector<vector<bool>> monster(n, vector<bool>(n));
		for(int r = 0; r < 4; ++r){
			for(int F = 0; F < 2; ++F){
				auto nueva = rotate_flip<char>(grid, r, F);
				auto s = rotate_flip<pii>(identity(n), r, F);
				vector<vector<pii>> inv(n, vector<pii>(n));
				for(int i = 0; i < n; ++i){
					for(int j = 0; j < n; ++j){
						inv[s[i][j].first][s[i][j].second] = {i, j};
					}
				}
				auto positions = search(nueva, pattern);
				for(const auto & pos : positions){
					int r, c;
					tie(r, c) = pos;
					for(int i = r; i < r+h; ++i){
						for(int j = c; j < c+w; ++j){
							monster[inv[i][j].first][inv[i][j].second] = (pattern[i-r][j-c]=='#');
						}
					}
				}
			}
		}
		int cnt = 0;
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				cnt += (grid[i][j] == '#' && monster[i][j] == false);
			}
		}
		return cnt;
	};

	function<void(int)> f = [&](int pos){
		if(pos == n*n){
			auto cpy = grids;
			for(int r = 0; r < n; ++r){
				for(int c = 0; c < n; ++c){
					int id, rot, flip;
					tie(id, rot, flip) = ans[r][c];
					grids[id] = rotate_flip(grids[id], rot, flip);
				}
			}
			int N = n*(l-2);
			mat grid(N, vector<char>(N));
			int p = 0;
			for(int i = 0; i < n*l; ++i){
				if(i%l == 0 || i%l == l-1) continue;
				for(int j = 0; j < n*l; ++j){
					if(j%l == 0|| j%l == l-1) continue;
					int r = i/l, c = j/l;
					grid[p/N][p%N] = grids[get<0>(ans[r][c])][i%l][j%l];
					p++;
				}
			}
			cout << part2(grid) << endl;
			grids = cpy;
			exit(0);
		}
		int row = pos / n, col = pos % n;
		auto aval = avaliable;
		for(int id : aval){
			for(int rot = 0; rot < 4; ++rot){
				for(int flip = 0; flip < 2; ++flip){
					bool valid = true;
					if(row-1 >= 0){
						int id_up, rot_up, flip_up;
						tie(id_up, rot_up, flip_up) = ans[row-1][col];
						valid &= (border(grids[id_up], rot_up, flip_up, 2) == border(grids[id], rot, flip, 0));
					}
					if(valid && col-1 >= 0){
						int id_left, rot_left, flip_left;
						tie(id_left, rot_left, flip_left) = ans[row][col-1];
						valid &= (border(grids[id_left], rot_left, flip_left, 3) == border(grids[id], rot, flip, 1));
					}
					if(valid){
						ans[row][col] = tup(id, rot, flip);
						avaliable.erase(id);
						f(pos+1);
						ans[row][col] = tup(0, 0, 0);
						avaliable.insert(id);
					}
				}
			}
		}
	};

	f(0);

	return 0;
}