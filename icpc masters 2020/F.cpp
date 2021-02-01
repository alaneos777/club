#include <iostream>
#include <vector>
#define endl '\n'
using namespace std;

const int MX = 1e6;

string addsymbol(const string& s) {
  string res = "^#";
  for (int i = 0; i < (int) s.size(); i++) {
    res.push_back(s[i]);
    res.push_back('#');
  }
  res += "$";
  return res;
}

string Manacher(const string& s) { // O(n)
  if (s.empty()) return s;

  string ns = addsymbol(s);
  int mx, id;
  int len = ns.length();
  vector<int> p(len, 0);
  mx = id = 0;

  for (int i = 1; i < len-1; i++) {
    if(i < mx)
      p[i] = min(p[id - (i-id)], mx - i);
    else
      p[i] = 0;

    while (ns[i + p[i] + 1] == ns[i - p[i] - 1])
      p[i]++;

    if(p[i] + i > mx) {
      mx = p[i] + i;
      id = i;
    }
  }
  mx = id = 0;
  for (int i = 1; i < len-1; i++)
    if(p[i] > mx) {
      mx = p[i];
      id = i;
    }
  int res = 0;
  for(int i = 3; i < len; i += 2)
    if(p[i] > res) res = p[i];
  cout << res << endl;
  int left = (id - p[id]) / 2;
  return s.substr(left, p[id]);
}

void solve(){
  string cadena;
  cin >> cadena;
  Manacher(cadena);
}

int main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int T;
  cin >> T;
  while(T--)
      solve();

  return 0;
}
