#include <bits/stdc++.h>
using namespace std;

double eps = 1e-8;

int main(){
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	while(n--){
		int nl;
		cin >> nl;
		set<double> starts;
		map<double, vector< pair<double, double> > > info;
		while(nl--){
			double x1, y1, x2, y2, r;
			cin >> x1 >> y1 >> x2 >> y2 >> r;
			if(x1 > x2) swap(x1, x2);
			starts.insert(x1);
			starts.insert(x2);
			info[x1].push_back(make_pair(x2, r));
		}
		vector<double> puntos(starts.begin(), starts.end());
		vector<double> segments(starts.size(), 1);
		for(int i = 0; i < puntos.size(); i++){
			for(pair<double, double> p : info[puntos[i]]){
				int j = i;
				while(puntos[j] != p.first){
					segments[j] *= p.second;
					j++;
				}
			}
		}
		cout << starts.size() + 1 << "\n";
		cout << fixed << setprecision(3) << "-inf " << puntos[0] << " 1.000\n";
		for(int i = 0; i < segments.size(); i++){
			cout << puntos[i] << " ";
			if(i == segments.size() - 1){
				cout << "+inf";
			}else{
				cout << puntos[i + 1];
			}
			cout << " " << segments[i] << "\n";
		}
		if(n > 0){
			cout << "\n";
		}
	}
	return 0;
}