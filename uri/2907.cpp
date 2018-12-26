#include <iostream>
#include <vector>
using namespace std;
using lli = long long int;

struct point{
    lli x, y;
    point(): x(0), y(0){}
    point(lli x, lli y): x(x), y(y) {}
    
    point operator-(const point & p) const{
    	return point(x-p.x, y-p.y);
    }
    
    lli cross(const point & p) const{
    	return x*p.y - y*p.x;
    }
};

istream & operator>>(istream & is, point & p){
	return is >> p.x >> p.y;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	lli n;
	cin >> n;
	vector<point> polygon(n), edges(2*n);
	for(int i = 0; i < n; ++i){
		cin >> polygon[i];
	}
	for(int i = 0; i < n; ++i){
		edges[i] = polygon[(i+1)%n] - polygon[i];
		edges[i+n] = edges[i];
	}
	
	lli ans = 0;
	for(lli i = 0, j = 0; i < n; ++i){
		while(edges[i].cross(edges[j]) >= 0) j++;
		ans += (j-i-1) * (j-i-2) / 2;
	}
	ans = n*(n-1)*(n-2)/6 - ans;
	cout << ans << "\n";
	return 0;
}