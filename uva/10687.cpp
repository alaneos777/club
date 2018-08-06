#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

bool comp(const pii & fixed, const pii & a, const pii & b){ //a < b
	int dist1 = (a.first - fixed.first) * (a.first - fixed.first) + (a.second - fixed.second) * (a.second - fixed.second);
	int dist2 = (b.first - fixed.first) * (b.first - fixed.first) + (b.second - fixed.second) * (b.second - fixed.second);
	if(dist1 == dist2){
		if(a.first == b.first){
			return a.second < b.second;
		}else{
			return a.first < b.first;
		}
	}else{
		return dist1 < dist2;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	while(cin >> n){
		if(n == 0) break;
		vector<pii> points(n);
		for(int i = 0; i < n; ++i){
			cin >> points[i].first >> points[i].second;
		}
		queue<int> Q;
		Q.push(0);
		vector<bool> visited(n, false);
		int ans = 0;
		while(!Q.empty()){
			int current = Q.front();
			Q.pop();
			if(visited[current]) continue;
			visited[current] = true;
			++ans;
			int min1 = -1, min2 = -1;
			for(int i = 0; i < n; ++i){
				if(i == current) continue;
				if(min1 == -1){
					min1 = i;
					continue;
				}else if(min2 == -1){
					min2 = i;
					if(comp(points[current], points[min2], points[min1])) swap(min1, min2);
					continue;
				}
				if(comp(points[current], points[i], points[min1])){
					min2 = min1;
					min1 = i;
				}else if(comp(points[current], points[i], points[min2])){
					min2 = i;
				}
			}
			if(min1 != -1 && !visited[min1]){
				Q.push(min1);
			}
			if(min2 != -1 && !visited[min2]){
				Q.push(min2);
			}
		}
		if(ans == n) cout << "All stations are reachable.\n";
		else cout << "There are stations that are unreachable.\n";
	}
	return 0;
}