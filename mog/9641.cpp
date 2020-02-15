#include <bits/stdc++.h>
using namespace std;

const int M = 26;
struct state{
	int len, link;
	vector<int> child;
	state(int len = 0, int link = -1): len(len), link(link), child(M, -1){}
	state(int len, int link, const vector<int> & child): len(len), link(link), child(child){}
};

struct SuffixAutomaton{
	vector<state> st;
	int last = 0;

	SuffixAutomaton(){
		st.emplace_back();
	}

	void extend(char c){
		int curr = st.size();
		st.emplace_back(st[last].len + 1);
		int p = last;
		while(p != -1 && st[p].child[c-'A'] == -1){
			st[p].child[c-'A'] = curr;
			p = st[p].link;
		}
		if(p == -1){
			st[curr].link = 0;
		}else{
			int q = st[p].child[c-'A'];
			if(st[p].len + 1 == st[q].len){
				st[curr].link = q;
			}else{
				int clone = st.size();
				st.emplace_back(st[p].len + 1, st[q].link, st[q].child);
				while(p != -1 && st[p].child[c-'A'] == q){
					st[p].child[c-'A'] = clone;
					p = st[p].link;
				}
				st[q].link = st[curr].link = clone;
			}
		}
		last = curr;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string C, str;
	int q;
	cin >> C >> q;
	SuffixAutomaton sa;
	for(char c : C){
		sa.extend(c);
	}
	while(q--){
		cin >> str;
		int curr = 0;
		int ans = 1;
		for(int i = 0; i < str.size(); ++i){
			if(sa.st[curr].child[str[i]-'A'] != -1){
				curr = sa.st[curr].child[str[i]-'A'];
			}else{
				if(curr == 0){
					ans = -1;
					break;
				}
				curr = 0;
				i--;
				ans++;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}