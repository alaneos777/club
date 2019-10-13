#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int g, y, r, n;
	cin >> g >> y >> r >> n;
	int s = g + y + r;
	
	int lo = 0, hi = s-1;
	auto add = [&](int L, int R){
		cout << L << " " << R << "\n";
		if(hi == -1) return;
		if(lo <= L && L <= hi && hi <= R){
			lo = L;
		}else if(L <= lo && lo <= R && R <= hi){
			hi = R;
		}else if(lo <= L && R <= hi){
			lo = L;
			hi = R;
		}else if(L <= lo && hi <= R){
			//no change
		}else{
			lo = 0, hi = -1;
		}
	};

	for(int i = 1; i <= n; ++i){
		int ti; string ci;
		int a = 0, b = 0;
		cin >> ti >> ci;
		ti %= s;
		if(ci == "green"){
			a = 0, b = g - 1;
		}else if(ci == "yellow"){
			a = g, b = g + y - 1;
		}else{
			a = g + y, b = g + y + r - 1;
		}
		int l = ti-b, r = ti-a;
		if(l < 0 && r < 0){ //normal
			add(l+s, r+s);
		}else if(l < 0 && r >= 0){ //da la vuelta
			add(s+l, s-1);
			add(0, r);
		}else{ //normal
			add(l, r);
		}
	}
	int tq; string cq;
	int num = 0, den = 0;
	cin >> tq >> cq;
	for(int T = lo; T <= hi; ++T){
		den++;
		int tmp = (tq - T) % s;
		if(tmp < 0) tmp += s;
		if(0 <= tmp && tmp <= g-1 && cq == "green"){
			num++;
		}else if(g <= tmp && tmp <= g+y-1 && cq == "yellow"){
			num++;
		}else if(g+y <= tmp && tmp <= g+y+r-1 && cq == "red"){
			num++;
		}
	}
	cout << fixed << setprecision(6) << (double)num/den << "\n";
	return 0;
}