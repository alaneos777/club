#include <iostream>
#include <set>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    set<int> ans;
    for(int i=1;i<=10;i++){
        cin >> n;
        ans.insert(n%42);
    }
    cout << ans.size();
    return 0;
}
