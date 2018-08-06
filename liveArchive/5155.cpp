#include <bits/stdc++.h>
using namespace std;

double distance(pair<int, int> & a, pair<int, int> & b){
	return hypot(a.first - b.first, a.second - b.second) + 16;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n;
	int caso = 1;
	while(cin >> n && n){
		vector<pair<int, int>> points(n);
		for(int i = 0; i < n; ++i){
			cin >> points[i].first >> points[i].second;
		}
		vector<int> sigma(n);
		for(int i = 0; i < n; ++i){
			sigma[i] = i;
		}
		double minimal = 1 << 29;
		vector<int> conf;
		vector<double> dists;
		do{
			double dist = 0;
			for(int i = 0; i < n - 1; ++i){
				dist += distance(points[sigma[i]], points[sigma[i + 1]]);
			}
			if(dist < minimal){
				minimal = dist;
				conf = sigma;
			}
		}while(next_permutation(sigma.begin(), sigma.end()));
		cout << "**********************************************************\nNetwork #" << caso++ << "\n";
		for(int i = 0; i < n - 1; ++i){
			cout << fixed << setprecision(2) << "Cable requirement to connect (" << points[conf[i]].first << "," << points[conf[i]].second << ") to (" << points[conf[i + 1]].first << "," << points[conf[i + 1]].second << ") is " << distance(points[conf[i]], points[conf[i + 1]]) << " feet.\n";
		}
		cout << fixed << setprecision(2) << "Number of feet of cable required is " << minimal << ".\n";
	}
	return 0;
}