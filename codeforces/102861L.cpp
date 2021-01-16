#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> movs = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int w, h, n;
	cin >> w >> h;
	vector<vector<char>> grid(w, vector<char>(h));
	vector<vector<unordered_set<int>>> res(w, vector<unordered_set<int>>(h));
	for(auto & row : grid){
		for(char & c : row){
			cin >> c;
		}
	}
	cin >> n;
	for(int p = 0; p < n; ++p){
		string word;
		cin >> word;
		int wordSize = word.size();
		vector<int> freq(26);
		for(char c : word){
			freq[c-'A']++;
		}
		for(auto mov : movs){
			int dx, dy;
			tie(dx, dy) = mov;
			vector<vector<bool>> vis(w, vector<bool>(h));
			for(int i = 0; i < w; ++i){
				for(int j = 0; j < h; ++j){
					if(vis[i][j]) continue;
					int u_l = i, v_l = j, u_r = i-dx, v_r = j-dy;
					int len = 0;
					vector<int> bucket(26);
					while(true){
						u_r += dx, v_r += dy;
						if(!(0 <= u_r && u_r < w && 0 <= v_r && v_r < h)) break;
						vis[u_r][v_r] = true;
						bucket[grid[u_r][v_r] - 'A']++;
						len++;
						if(len > wordSize){
							bucket[grid[u_l][v_l] - 'A']--;
							u_l += dx, v_l += dy;
							len--;
						}
						if(freq == bucket){
							for(int x = u_l, y = v_l; ; x += dx, y += dy){
								res[x][y].insert(p);
								if(x == u_r && y == v_r) break;
							}
						}
					}
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < w; ++i){
		for(int j = 0; j < h; ++j){
			ans += (res[i][j].size() > 1);
		}
	}
	cout << ans << "\n";
	return 0;
}