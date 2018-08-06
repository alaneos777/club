#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	string x1, y1, x2, y2, x3, y3, x4, y4;
	while(cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4){
		map< pair<string, string>, int> puntos;
		puntos[make_pair(x1, y1)]++;
		puntos[make_pair(x2, y2)]++;
		puntos[make_pair(x3, y3)]++;
		puntos[make_pair(x4, y4)]++;
		double x = 0, y = 0;
		for(pair< pair<string, string>, int> p : puntos){
			double xi, yi;
			istringstream(p.first.first) >> xi;
			istringstream(p.first.second) >> yi;
			if(p.second == 1){
				x += xi, y += yi;
			}else{
				x -= xi, y -= yi;
			}
		}
		cout << fixed << setprecision(3) << x << " " << y << "\n";
	}
	return 0;
}