#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const regex reg("(.+):\\s([0-9]+)-([0-9]+)\\sor\\s([0-9]+)-([0-9]+)");

bool validateField(int x, const vector<pair<int, int>> & ranges){
	bool ans = false;
	for(const auto & range : ranges){
		ans |= (range.first <= x && x <= range.second);
	}
	return ans;
}

vector<int> parseTicket(const string & line){
	stringstream ss(line);
	vector<int> ticket;
	string x;
	while(getline(ss, x, ',')){
		ticket.push_back(stoi(x));
	}
	return ticket;
}

int main(){
	map<string, vector<pair<int, int>>> fields;
	string line;
	bool nearby = false;
	vector<vector<int>> tickets;
	while(getline(cin, line)){
		if(line == "") continue;
		smatch m;
		if(regex_match(line, m, reg)){
			string key = m[1];
			fields[key].emplace_back(stoi(m.str(2)), stoi(m.str(3)));
			fields[key].emplace_back(stoi(m.str(4)), stoi(m.str(5)));
		}else if(line == "nearby tickets:"){
			nearby = true;
		}else if(nearby){
			tickets.push_back(parseTicket(line));
		}
	}

	int ans = 0;
	for(const auto & ticket : tickets){
		for(int x : ticket){
			bool valid_x = false;
			for(const auto & field : fields){
				valid_x |= validateField(x, field.second);
			}
			if(!valid_x){
				ans += x;
			}
		}
	}
	cout << ans << endl;
	return 0;
}