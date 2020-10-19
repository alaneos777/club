#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

struct pt{
	lli x, y;
	pt(): x(0), y(0) {}
	pt(lli x, lli y): x(x), y(y) {}
	pt operator-(const pt & p) const{return pt(x - p.x, y - p.y);}
	lli cross(const pt & p) const{return x*p.y - y*p.x;}
};

int main(){
	srand(time(0));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, p;
	cin >> n >> p;
	int m = (n*p + 99) / 100;
	vector<pt> pts(n);
	for(int i = 0; i < n; ++i){
		cin >> pts[i].x >> pts[i].y;
	}
	random_shuffle(pts.begin(), pts.end(), [](int i){return ((rand() << 15) + rand()) % i;});
	if(n == 1){
		cout << "possible\n";
		return 0;
	}
	for(int k = 0; k < 250; ++k){
		int i = rand() % n, j;
		do{
			j = rand() % n;
		}while(j == i);
		pt v = pts[j] - pts[i];
		int cnt = 2;
		for(int l = 0; l < n; ++l){
			if(l == i || l == j) continue;
			if(v.cross(pts[l] - pts[i]) == 0){
				cnt++;
			}
		}
		if(cnt >= m){
			cout << "possible\n";
			return 0;
		}
	}
	cout << "impossible\n";
	return 0;
}