#include <bits/stdc++.h>
using namespace std;
typedef double ld;
ld eps = 1e-8;

struct building{
	ld x, h;
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<building> buildings(n);
	for(int i = 0; i < n; ++i){
		cin >> buildings[i].x >> buildings[i].h;
	}

	auto mini = [&](ld h){
		ld r = 0;
		for(building & b : buildings){
			r = max(r, hypot(b.x-0.5-h, b.h));
			r = max(r, hypot(b.x+0.5-h, b.h));
		}
		return r;
	};

	ld l = -5, r = 20000, m;
	while(true){
		if(abs(r-l) < eps){
			m = l + (r - l) / 2;
			break;
		}
		ld leftThird = l + (r-l)/3;
		ld rightThird = l + 2*(r-l)/3;
		if(mini(leftThird) > mini(rightThird)){
			l = leftThird;
		}else{
			r = rightThird;
		}
	}
	cout << fixed << setprecision(9) << mini(m) << "\n";
	return 0;
}