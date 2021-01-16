#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s;
	cin >> s;
	vector<int> games = {0, 0}, points = {0, 0};
	int server = 0, winner = -1;
	for(char c : s){
		if(c == 'S'){
			points[server]++;
		}else if(c == 'R'){
			points[1-server]++;
			server = 1-server;
		}else if(c == 'Q'){
			if(winner == -1){
				if(server == 0){
					cout << games[0] << " (" << points[0] << "*) - " << games[1] << " (" << points[1] << ")\n";
				}else{
					cout << games[0] << " (" << points[0] << ") - " << games[1] << " (" << points[1] << "*)\n";
				}
			}else{
				if(winner == 0){
					cout << games[0] << " (winner) - " << games[1] << "\n";
				}else{
					cout << games[0] << " - " << games[1] << " (winner)\n";
				}
			}
		}
		for(int i : {0, 1}){
			if(points[i] >= 10 || (points[i] >= 5 && points[i]-points[1-i] >= 2)){
				games[i]++;
				server = i;
				points = {0, 0};
				break;
			}
		}
		for(int i : {0, 1}){
			if(games[i] >= 2){
				winner = i;
				break;
			}
		}
	}
	return 0;
}