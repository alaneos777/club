#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	string game[2][2];
	int time[2][2];
	cin >> game[0][0] >> game[1][0] >> game[0][1] >> game[1][1];
	time[0][0] = -4, time[1][0] = -3, time[0][1] = -2, time[1][1] = -1;
	queue<string> q;
	for(int i = 5; i <= n; ++i){
		string p;
		cin >> p;
		q.push(p);
	}
	string s;
	cin >> s;
	int mx = 0, cnt = 0;
	for(int i = 0; i < s.size(); ++i){
		if(i-1 >= 0 && s[i] == s[i-1]){
			cnt++;
		}else{
			mx = max(mx, cnt);
			cnt = 1;
		}
	}
	mx = max(mx, cnt), cnt = 0;
	for(int i = 0; i < s.size(); ++i){
		if(i-1 >= 0 && s[i] == s[i-1]){
			cnt++;
		}else{
			cnt = 1;
		}
		int j = s[i]=='W' ? 0 : 1;
		swap(game[j][0], game[j][1]);
		swap(time[j][0], time[j][1]);
		q.push(game[1-j][1]);
		game[1-j][1] = game[1-j][0];
		game[1-j][0] = q.front(); q.pop();
		time[1-j][0] = i;
		if(cnt == mx){
			if(time[j][0] < time[j][1]){
				cout << game[j][0] << " " << game[j][1] << "\n";
			}else{
				cout << game[j][1] << " " << game[j][0] << "\n";
			}
		}
	}
	return 0;
}