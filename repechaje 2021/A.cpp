#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

map<char, char> decO = {
	{'0', 'O'},
	{'1', 'I'},
	{'2', 'Z'},
	{'3', 'E'},
	{'4', 'A'},
	{'5', 'S'},
	{'6', 'G'},
	{'7', 'T'},
	{'8', 'B'},
	{'9', 'P'}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	cin.ignore();
	while(t--){
		string line;
		getline(cin, line);
		string word;
		stringstream ss(line);
		int i = 0;
		while(ss >> word){
			if(i > 0) cout << " ";
			for(char c : word){
				if('0' <= c && c <= '9'){
					cout << decO[c];
				}else{
					cout << c;
				}
			}
			i++;
		}
		cout << "\n";
	}
	return 0;
}