#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> h(n), color(n, -1);
	vector<deque<int>> pos(1e6+1);
	for(int i = 0; i < n; ++i){
		cin >> h[i];
		pos[h[i]].push_back(i);
	}
	int sz = 0;
	for(int i = 0; i < n; ++i){
		if(color[i] == -1){
			color[i] = sz++;
			pos[h[i]].pop_front();
		}
		int nxt = h[i]-1;
		if(nxt > 0 && !pos[nxt].empty()){
			color[pos[nxt][0]] = color[i];
			pos[nxt].pop_front();
		}
	}
	cout << sz << "\n";
	return 0;
}