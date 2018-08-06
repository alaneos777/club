#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct point{
	lli x, y;
	point(){
		x = y = 0;
	}
	point(lli x, lli y){
		this->x = x, this->y = y;
	}
};

int main(){
	int n;
	scanf("%lld", &n);
	vector<point> points(n);
	for(int i = 0; i < n; ++i){
		scanf("%lld %lld", &points[i].x, &points[i].y);
	}
	lli area2 = 0, b = n;
	int j;
	for(int i = 0; i < n; ++i){
		j = i + 1;
		if(j == n) j = 0;
		area2 += points[i].x * points[j].y - points[j].x * points[i].y;
		b += __gcd(abs(points[i].x - points[j].x), abs(points[i].y - points[j].y)) - 1;
	}
	area2 = abs(area2);
	printf("%lld", (area2 - b + 2) >> 1);
	return 0;
}