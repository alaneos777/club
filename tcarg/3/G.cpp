#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct point{
	int x, y;
	point(): x(0), y(0){}
	point(int x, int y): x(x), y(y){}
	bool operator<(const point& p) const{
		return x < p.x || (x == p.x && y < p.y);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<point> P(n);
	for(point& pi : P){
		cin >> pi.x >> pi.y;
	}
	sort(P.begin(), P.end());
	vector<vector<int>> X(2e5), Y(2e5);
	auto has = [&](const vector<int>& arr, int e){
		return binary_search(arr.begin(), arr.end(), e);
	};
	lli ans = 0;
	for(const point& p : P){
		if(X[p.y].size() < Y[p.x].size()){
			for(int x : X[p.y]){
				int l = p.x - x;
				assert(l > 0);
				if(p.y-l>=0 && has(X[p.y-l], x) && has(X[p.y-l], p.x)){
					ans++;
				}
			}
		}else{
			for(int y : Y[p.x]){
				int l = p.y - y;
				assert(l > 0);
				if(p.x-l>=0 && has(Y[p.x-l], y) && has(Y[p.x-l], p.y)){
					ans++;
				}
			}
		}
		X[p.y].push_back(p.x);
		Y[p.x].push_back(p.y);
	}
	cout << ans << "\n";
	return 0;
}