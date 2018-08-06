#include <bits/stdc++.h>
using namespace std;

int main(){
	long n;
	cin >> n;
	vector< pair<long, long> > info(n);
	for(int i = 0; i < n; i++){
		cin >> info[i].first >> info[i].second;
	}
	sort(info.begin(), info.end());
	bool found = false;
	for(int i = 0; i < n - 1; i++){
		if(info[i].second > info[i + 1].second){
			found = true;
			break;
		}
	}
	if(found) cout << "Happy Alex";
	else cout << "Poor Alex";
	return 0;
}