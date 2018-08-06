#include <bits/stdc++.h>
using namespace std;

struct point{
	int x, y;

	point(){
		x = y = 0;
	}
	point(int x, int y){
		this->x = x, this->y = y;
	}
	point operator-(const point & p) const{
		return point(x - p.x, y - p.y);
	}
	bool operator<(const point & p) const{
		if(x == p.x){
			return y < p.y;
		}else{
			return x < p.x;
		}
	}
	bool operator>(const point & p) const{
		if(x == p.x){
			return y > p.y;
		}else{
			return x > p.x;
		}
	}
	bool operator==(const point & p) const{
		return x == p.x && y == p.y;
	}
	bool operator!=(const point & p) const{
		return !(*this == p);
	}
};

istream &operator>>(istream &is, point & P){
	point p;
    is >> p.x >> p.y;
    P = p;
    return is;
}

bool check(vector<point> & set1, vector<point> & set2){
	point T = set2[0] - set1[0];
	for(int i = 1; i < set1.size(); i++){
		if(set2[i] - set1[i] != T){
			return false;
		}
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<point> set1(n), set2(n);
		for(int i = 0; i < n; i++){
			cin >> set1[i];
		}
		for(int i = 0; i < n; i++){
			cin >> set2[i];
		}
		sort(set2.begin(), set2.end());
		bool matched = false;
		for(int i = 0; i < 4; i++){
			sort(set1.begin(), set1.end());
			if(check(set1, set2)){
				matched = true;
				break;
			}else{
				for(int j = 0; j < n; j++){
					set1[j] = point(-set1[j].y, set1[j].x);
				}
			}
		}
		if(matched){
			cout << "MATCHED\n";
		}else{
			cout << "NOT MATCHED\n";
		}
	}
	return 0;
}