#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
/*using ld = long double;
using comp = complex<ld>;
const ld pi = acosl(-1);*/

const int m = 5;
const int n = 70;

map<array<int, m>, lli> mem[n][m][m];

int main(){
	/*ld theta = 2*pi/5;
	vector<int> sgn = {1, -1, 1, 1, 1, -1, -1, -1, -1, 1, -1, -1, 1, -1, 1, 1, 1, 1, -1, 1, 1, -1, 1, 1, 1};
	vector<int> chg = {0};
	for(int i = 0; i < sgn.size(); ++i){
		if(i && sgn[i] != sgn[i-1]){
			chg.push_back(-1);
		}else{
			chg.push_back(1);
		}
	}
	assert(sgn.size() == 25);
	comp c(0, 0), p(1, 0);
	for(int i = 1; i < chg.size(); ++i){
		theta = theta * chg[i];
		c = c*ld(chg[i]) + p*ld(1-chg[i]);
		p = c + (p-c)*polar(1.0l, theta);
		cout << p << "\n";
	}*/
	function<lli(int, int, int, array<int, m>)> f = [&](int pos, int prev_arc, int left_turns, array<int, m> cnt_arcs) -> lli{
		if(pos == -1) return left_turns==0;
		if(mem[pos][prev_arc][left_turns].count(cnt_arcs)) return mem[pos][prev_arc][left_turns][cnt_arcs];
		lli& ans = mem[pos][prev_arc][left_turns][cnt_arcs];
		int ccw = prev_arc+1; if(ccw == m) ccw = 0;
		int cw = prev_arc-1; if(cw == -1) cw = m-1;
		for(int nxt_arc : {ccw, cw}){
			if(cnt_arcs[nxt_arc] < n/m){
				cnt_arcs[nxt_arc]++;
				int nxt_left_turns = left_turns;
				if(nxt_arc == ccw){
					nxt_left_turns++;
					if(nxt_left_turns == m) nxt_left_turns = 0;
				}
				ans += f(pos-1, nxt_arc, nxt_left_turns, cnt_arcs);
				cnt_arcs[nxt_arc]--;
			}
		}
		return ans;
	};
	cout << f(n-1, m-1, 0, array<int, m>()) << "\n";
	return 0;
}