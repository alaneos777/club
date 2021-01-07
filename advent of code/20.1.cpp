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

	function<void(int)> f = [&](int pos){
		if(pos == n*n){
			lli prod = 1;
			prod *= get<0>(ans[0][0]);
			prod *= get<0>(ans[0][n-1]);
			prod *= get<0>(ans[n-1][0]);
			prod *= get<0>(ans[n-1][n-1]);
			cout << prod << endl;
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