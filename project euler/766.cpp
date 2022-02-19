#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

const int M = 5, N = 6;

struct pt{
	int x, y;
	pt(): x(0), y(0){}
	pt(int x, int y): x(x), y(y){}
	inline int pos() const{return x*N + y;}
	inline bool valid() const{return 0 <= x && x < M && 0 <= y && y < N;}
	pt operator+(const pt& p) const{
		return pt(x + p.x, y + p.y);
	}
};

const vector<pt> movs = {pt(1, 0), pt(-1, 0), pt(0, 1), pt(0, -1)};

struct shape{
	lli msk;
	vector<pt> d;
	shape(): msk(0){}
	shape(const vector<pt>& d): msk(0), d(d){
		for(const pt& p : d){
			msk += lli(1) << p.pos();
		}
	}
};

const vector<shape> shapes = {
	shape(vector<pt>{}),
	shape(vector<pt>{pt(0, 0), pt(0, 1), pt(1, 0)}),           // 1: L roja
	shape(vector<pt>{pt(0, 0)}),                               // 2: cuadrito morado
	shape(vector<pt>{pt(0, 0), pt(0, 1), pt(1, 0), pt(1, 1)}), // 3: cuadro azul fuerte
	shape(vector<pt>{pt(0, 0), pt(1, 0), pt(1, -1)}),          // 4: L verde
	shape(vector<pt>{pt(0, 0), pt(0, 1)}),                     // 5: rectangulo azul claro
	shape(vector<pt>{pt(0, 0), pt(1, 0)})                      // 6: rectangulo amarillo
};

struct cell{
	int color;
	pt start;
	cell(){}
	cell(int color, const pt& start): color(color), start(start){}
	cell shift(const pt& p) const{
		return cell(color, start+p);
	}
	bool valid() const{
		for(const pt& d : shapes[color].d){
			if(!(start + d).valid()) return false;
		}
		return true;
	}
	inline lli getHsh() const{
		return lli(color) << (3*start.pos());
	}
	inline lli getMsk() const{
		return shapes[color].msk << start.pos();
	}
};

using board = vector<cell>;

lli getHsh(const board& b){
	lli hsh = 0;
	for(const cell& s : b){
		hsh += s.getHsh();
	}
	return hsh;
}

lli getMsk(const board& b){
	lli msk = 0;
	for(const cell& s : b){
		msk += s.getMsk();
	}
	return msk;
}

unordered_set<lli> vis;
void dfs(lli hsh, lli msk){
	vis.insert(hsh);
	lli rem = hsh;
	for(int m = 0; m < M; ++m){
		for(int n = 0; n < N; ++n){
			int color = rem & 7;
			rem >>= 3;
			if(color){
				cell s(color, pt(m, n));
				for(const pt& mov : movs){
					cell newS = s.shift(mov);
					if(newS.valid() && ((msk - s.getMsk()) & newS.getMsk()) == 0){
						lli nxtHsh = hsh - s.getHsh() + newS.getHsh();
						lli nxtMsk = msk - s.getMsk() + newS.getMsk();
						if(vis.count(nxtHsh) == 0) dfs(nxtHsh, nxtMsk);
					}
				}
			}
		}
	}
}

int main(){
	vis.reserve(1<<8);
	vis.max_load_factor(0.25);

	board init = {
		cell(1, pt(0, 1)),
		cell(1, pt(0, 4)),
		cell(2, pt(2, 0)),
		cell(2, pt(3, 0)),
		cell(2, pt(4, 0)),
		cell(2, pt(2, 1)),
		cell(2, pt(3, 1)),
		cell(2, pt(4, 1)),
		cell(3, pt(2, 2)),
		cell(4, pt(0, 3)),
		cell(4, pt(3, 5)),
		cell(5, pt(4, 2)),
		cell(6, pt(2, 4)),
		cell(6, pt(1, 5))
	};

	dfs(getHsh(init), getMsk(init));
	cout << vis.size() << "\n";

	return 0;
}