#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool right(int x1, int y1, int x2, int y2){
	int d1 = x1*x1 + y1*y1;
	int d2 = x2*x2 + y2*y2;
	int d3 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
	vector<int> d = {d1, d2, d3};
	sort(d.begin(), d.end());
	return (d[0] > 0 && d[1] > 0 && d[2] > 0 && d[0]+d[1]==d[2]);
}

int main(){
	int M = 50;
	lli cnt = 0;
	for(int x1 = 0; x1 <= M; ++x1){
		for(int y1 = 0; y1 <= M; ++y1){
			for(int x2 = 0; x2 <= M; ++x2){
				for(int y2 = 0; y2 <= M; ++y2){
					if(right(x1, y1, x2, y2)){
						cnt++;
					}
				}
			}
		}
	}
	cout << cnt/2 << "\n";
	return 0;
}