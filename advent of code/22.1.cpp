#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	int idx = 0;
	vector<deque<int>> cards(2);
	string line;
	while(getline(cin, line)){
		if(line == "") continue;
		if(line == "Player 1:"){
			idx = 0;
		}else if(line == "Player 2:"){
			idx = 1;
		}else{
			cards[idx].push_back(stoi(line));
		}
	}
	while(!cards[0].empty() && !cards[1].empty()){
		for(int i : {0, 1}){
			if(cards[i].front() > cards[1-i].front()){
				int a = cards[i].front(); cards[i].pop_front();
				int b = cards[1-i].front(); cards[1-i].pop_front();
				cards[i].push_back(a);
				cards[i].push_back(b);
				break;
			}
		}
	}
	lli ans = 0;
	for(int i : {0, 1}){
		if(cards[i].empty()) continue;
		for(int j = 0; j < cards[i].size(); ++j){
			ans += (lli)cards[i][j] * (cards[i].size()-j);
		}
	}
	cout << ans << endl;
	return 0;
}