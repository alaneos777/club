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
	
	function<int(vector<deque<int>> &)> play = [&](vector<deque<int>> & cards){
		set<vector<deque<int>>> seen;
		while(!cards[0].empty() && !cards[1].empty()){
			int winner = -1;
			if(seen.count(cards)){
				return 0;
			}else if(cards[0].front() <= (int)cards[0].size()-1 && cards[1].front() <= (int)cards[1].size()-1){
				int a = cards[0].front();
				int b = cards[1].front();
				deque<int> A, B;
				for(int i = 0; i < a; ++i){
					assert(i+1 < cards[0].size());
					A.push_back(cards[0][i+1]);
				}
				for(int i = 0; i < b; ++i){
					assert(i+1 < cards[1].size());
					B.push_back(cards[1][i+1]);
				}
				vector<deque<int>> cpy = {A, B};
				winner = play(cpy);
			}else{
				for(int i : {0, 1}){
					if(cards[i].front() > cards[1-i].front()){
						winner = i;
						break;
					}
				}
			}
			seen.insert(cards);
			int a = cards[winner].front(); cards[winner].pop_front();
			int b = cards[1-winner].front(); cards[1-winner].pop_front();
			cards[winner].push_back(a);
			cards[winner].push_back(b);
		}
		if(cards[0].empty()) return 1;
		else return 0;
	};

	int winner = play(cards);

	lli ans = 0;
	for(int j = 0; j < cards[winner].size(); ++j){
		ans += (lli)cards[winner][j] * (cards[winner].size()-j);
	}
	cout << ans << endl;
	return 0;
}