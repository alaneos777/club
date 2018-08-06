#include <bits/stdc++.h>
using namespace std;
typedef double ld;

int dx, dy, w, v, lx, ly;
vector<vector<int>> grid;
vector<vector<int>> graph;
const ld g = 9.80665;
const ld eps = 1e-9;

vector<ld> quadratic(ld a, ld b, ld c){
	ld d = b * b - 4 * a * c;
	if(d < 0) return {};
	d = sqrt(d);
	ld x1 = (-b + d) / (2 * a);
	ld x2 = (-b - d) / (2 * a);
	if(x1 < x2) swap(x1, x2);
	return {x1, x2};
}

inline int id(int x, int y){
	return y * dx + x;
}

inline int Y(int pos){
	return pos / dx;
}

inline int X(int pos){
	return pos % dx;
}

bool collision(int i, int j, int k, int l, ld ex, ld ey, ld theta, ld tf){
	ld x, y, z, t;
	ld st = sin(theta), ct = cos(theta);
	ld p = k*w, q = p+w;
	ld r = l*w, s = r+w;

	t = (-l + j + 0.5) * w / ey / v / ct;
	x = (i + 0.5) * w + ex * v * ct * t;
	z = grid[j][i] + t * (v * st - 0.5 * g * t);
	if(0 < t && t < tf && 0 <= z && z <= grid[l][k] && p <= x && x <= q) return true;

	t = (-l + j - 0.5) * w / ey / v / ct;
	x = (i + 0.5) * w + ex * v * ct * t;
	z = grid[j][i] + t * (v * st - 0.5 * g * t);
	if(0 < t && t < tf && 0 <= z && z <= grid[l][k] && p <= x && x <= q) return true;

	t = (k - i - 0.5) * w / ex / v / ct;
	y = abs((-j - 0.5) * w + ey * v * ct * t);
	z = grid[j][i] + t * (v * st - 0.5 * g * t);
	if(0 < t && t < tf && 0 <= z && z <= grid[l][k] && r <= y && y <= s) return true;

	t = (k - i + 0.5) * w / ex / v / ct;
	y = abs((-j - 0.5) * w + ey * v * ct * t);
	z = grid[j][i] + t * (v * st - 0.5 * g * t);
	if(0 < t && t < tf && 0 <= z && z <= grid[l][k] && r <= y && y <= s) return true;

	return false;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> dx >> dy >> w >> v >> lx >> ly;
	--lx, --ly;
	int total = dx * dy;
	grid = vector<vector<int>>(dy, vector<int>(dx));
	graph = vector<vector<int>>(total, vector<int>());
	for(int j = 0; j < dy; ++j){
		for(int i = 0; i < dx; ++i){
			cin >> grid[j][i];
		}
	}

	int i = 0, j = 0;
	for(int pos1 = 0; pos1 < total; ++pos1){
		int k = 0, l = 0;
		for(int pos2 = 0; pos2 < total; ++pos2){
			if(pos1 != pos2){
				ld ex = k - i, ey = j - l;
				ld e = hypot(ex, ey);
				ex /= e, ey /= e;
				ld c = grid[j][i] - grid[l][k];
				ld b = e * w;
				ld a = -0.5 * g * e * e * w * w / v / v;
				vector<ld> roots = quadratic(a, b, a + c);
				if(roots.size() && roots[0] >= 0){
					ld theta = atan(roots[0]);
					ld t = e * w / v / cos(theta);
					bool test = true;
					int m = 0, n = 0;
					for(int m = min(i, k); m <= max(i, k); ++m){
						if(!test) break;
						for(int n = min(j, l); n <= max(j, l); ++n){
							if(collision(i, j, m, n, ex, ey, theta, t)){
								test = false;
								break;
							}
						}
					}
					if(test){
						graph[pos1].push_back(pos2);
					}
				}
			}
			++k;
			if(k == dx) k = 0, ++l;
		}
		++i;
		if(i == dx) i = 0, ++j;
	}

	vector<vector<int>> dist(dy, vector<int>(dx, 0));
	vector<bool> visited(total, false);
	queue<int> Q;
	Q.push(id(lx, ly));
	while(!Q.empty()){
		int current = Q.front(); Q.pop();
		visited[current] = true;
		for(int & dest : graph[current]){
			if(!visited[dest]){
				dist[Y(dest)][X(dest)] = dist[Y(current)][X(current)] + 1;
				Q.push(dest);
				visited[dest] = true;
			}
		}
	}

	for(int j = 0; j < dy; ++j){
		for(int i = 0; i < dx; ++i){
			if(dist[j][i] == 0 && !(j == ly && i == lx)){
				cout << "X ";
			}else{
				cout << dist[j][i] << " ";
			}
		}
		cout << "\n";
	}
	return 0;
}