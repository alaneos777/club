#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

struct point{
	int a[5];
	point(){
		memset(a, 0, sizeof(a));
	}
	point(int u, int v, int w, int x, int y){
		a[0] = u;
		a[1] = v;
		a[2] = w;
		a[3] = x;
		a[4] = y;
	}
	point operator+(const point& p) const{
		return point(a[0] + p.a[0], a[1] + p.a[1], a[2] + p.a[2], a[3] + p.a[3], a[4] + p.a[4]);
	}
	point operator-(const point& p) const{
		return point(a[0] - p.a[0], a[1] - p.a[1], a[2] - p.a[2], a[3] - p.a[3], a[4] - p.a[4]);
	}
	bool valid() const{
		return 0 <= a[0] && a[0] < 5 && 0 <= a[1] && a[1] < 5 && 0 <= a[2] && a[2] < 5 && 0 <= a[3] && a[3] < 5 && 0 <= a[4] && a[4] < 5;
	}
};

istream& operator>>(istream& is, point& p){
	return cin >> p.a[0] >> p.a[1] >> p.a[2] >> p.a[3] >> p.a[4];
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<point> movs;
	for(int a = -1; a <= 1; ++a){
		for(int b = -1; b <= 1; ++b){
			for(int c = -1; c <= 1; ++c){
				for(int d = -1; d <= 1; ++d){
					for(int e = -1; e <= 1; ++e){
						if(!(a == 0 && b == 0 && c == 0 && d == 0 && e == 0)) movs.emplace_back(a, b, c, d, e);
					}
				}
			}
		}
	}
	int t;
	cin >> t;
	int grid[5][5][5][5][5];
	memset(grid, -1, sizeof(grid));
	for(int turn = 1; turn <= t; ++turn){
		point curr; char c;
		cin >> curr >> c;
		int who = (c == 'X' ? 0 : 1);
		grid[curr.a[0]][curr.a[1]][curr.a[2]][curr.a[3]][curr.a[4]] = who;
		bool pWins = false;
		for(const point& mov : movs){
			point left = curr, right = curr;
			int l = 0, r = 0;
			while(true){
				left = left - mov;
				if(!(left.valid() && grid[left.a[0]][left.a[1]][left.a[2]][left.a[3]][left.a[4]] == who)) break;
				l--;
			}
			while(true){
				right = right + mov;
				if(!(right.valid() && grid[right.a[0]][right.a[1]][right.a[2]][right.a[3]][right.a[4]] == who)) break;
				r++;
			}
			if(r-l+1 == 5){
				pWins = true;
				break;
			}
		}
		if(pWins){
			cout << c << " " << turn << "\n";
			return 0;
		}
	}
	cout << "DRAW\n";
	return 0;
}