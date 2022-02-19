#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	cin.ignore();
	stack<string> st;
	string s;
	while(n--){
		getline(cin, s);
		reverse(s.begin(), s.end());
		st.push(s);
	}
	while(!st.empty()){
		cout << st.top().size() << " " << st.top() << "\n";
		st.pop();
	}
	return 0;
}