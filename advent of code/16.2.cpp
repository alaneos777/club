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
	vector<int> my_ticket;
	while(getline(cin, line)){
		if(line == "") continue;
		smatch m;
		if(regex_match(line, m, reg)){
			string key = m[1];
			fields[key].emplace_back(stoi(m.str(2)), stoi(m.str(3)));
			fields[key].emplace_back(stoi(m.str(4)), stoi(m.str(5)));
		}else if(line == "your ticket:"){
			getline(cin, line);
			my_ticket = parseTicket(line);
		}else if(line == "nearby tickets:"){
			nearby = true;
		}else if(nearby){
			vector<int> ticket = parseTicket(line);
			bool valid_ticket = true;
			for(int x : ticket){
				bool valid_x = false;
				for(const auto & field : fields){
					valid_x |= validateField(x, field.second);
				}
				valid_ticket &= valid_x;
			}
			if(valid_ticket){
				tickets.push_back(ticket);
			}
		}
	}
	
	int n = fields.size();
	vector<vector<int>> adj(n);
	for(int i = 0; i < n; ++i){
		// field #i in ticket
		// field #j in fields
		int j = 0;
		for(const auto & field : fields){
			bool valid = true;
			for(const auto & ticket : tickets){
				valid &= validateField(ticket[i], field.second);
			}
			if(valid){
				adj[j].push_back(i);
			}
			++j;
		}
	}

	auto maxMatching = [&](){
		vector<int> left(n, -1), right(n, -1);
		vector<bool> used(n);

		function<bool(int)> tryKuhn = [&](int u){
			if(used[u]) return false;
			used[u] = true;
			for(int v : adj[u]){
				if(right[v] == -1 || tryKuhn(right[v])){
					right[v] = u;
					left[u] = v;
					return true;
				}
			}
			return false;
		};

		for(int u = 0; u < n; ++u){
			tryKuhn(u);
			fill(used.begin(), used.end(), false);
		}
		vector<int> ans(n);
		for(int u = 0; u < n; ++u){
			ans[right[u]] = u;
		}
		return ans;
	};

	vector<int> pi = maxMatching();
	int j = 0;
	lli ans = 1;
	for(const auto & field : fields){
		if(field.first.size() >= 9 && field.first.substr(0, 9) == "departure"){
			ans *= my_ticket[pi[j]];
		}
		j++;
	}

	cout << ans << endl;

	return 0;
}