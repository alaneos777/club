#include <bits/stdc++.h>
using namespace std;

struct island{
	int x, y;
	double h;
};

bool comp(const island & a, const island & b){
	if(abs(a.h - b.h) < 1e-9){
		if(a.x == b.x){
			return a.y < b.y;
		}else{
			return a.x < b.x;
		}
	}else{
		return a.h < b.h;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	int n, d;
	int caso = 1;
	while(cin >> n >> d && !(n == 0 && d == 0)){
		vector<island> islands(n);
		for(int i = 0; i < n; i++){
			cin >> islands[i].x >> islands[i].y;
			if(abs(islands[i].y) <= d) islands[i].h = islands[i].x + sqrt(d * d - islands[i].y * islands[i].y);
		}
		sort(islands.begin(), islands.end(), comp);
		int i = 0;
		int radars = 0;
		while(i < islands.size()){
			double h = islands[i].h;
			if(abs(islands[i].y) > d) break;
			i++;
			while(i < islands.size() && (islands[i].x - h) * (islands[i].x - h) + islands[i].y * islands[i].y <= d * d){
				i++;
			}
			radars++;
		}
		cout << "Case " << caso++ << ": ";
		if(i == islands.size()){
			cout << radars << "\n";
		}else{
			cout << "-1\n";
		}
	}
	return 0;
}