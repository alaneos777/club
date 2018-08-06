#include <iostream>
#include <vector>
#include <string>

using namespace std;

int fast_pow(int b, int e){
    int ans = 1;
    while(e > 0){
        if(e%2 == 1){
            ans *= b;
        }
        e = e >> 1;
        b *= b;
    }
    return ans;
}

template<typename tipo>
vector< vector<tipo> > power_set_1(vector<tipo> arr){
    int n = arr.size();
    int pn = fast_pow(2, n);
    vector< vector<tipo> > ans(pn);
    for(int i=0;i<pn;i++){
        int c = 0;
        vector<tipo> tmp;
        for(int j=0;j<n;j++){
            if(i & (1 << j)){
                tmp.push_back(arr[j]);
                c++;
            }
        }
        ans[i] = tmp;
    }
    return ans;
}

template<typename tipo>
vector< vector<tipo> > power_set_2(vector<tipo> arr){
    vector< vector<tipo> > ans(1);
    for(tipo x:arr){
        int n = ans.size();
        for(int i=0;i<n;i++){
            vector<tipo> actual = ans[i];
            actual.push_back(x);
            ans.push_back(actual);
        }
    }
    return ans;
}

template<typename tipo>
vector< vector< vector<tipo> > > power_set_3(vector<tipo> arr){
    vector< vector< vector<tipo> > > ans(1);
    ans[0].resize(1);
    for(tipo x:arr){
        int n = ans.size();
        vector< vector< vector<tipo> > > tmp(n);
        for(int i=0;i<n;i++){
            vector< vector<tipo> > actual = ans[i];
            int p = actual.size();
            for(int j=0;j<p;j++){
                actual[j].push_back(x);
            }
            tmp[i] = actual;
        }
        ans.resize(n+1);
        for(int i=0;i<n;i++){
            for(int j=0;j<tmp[i].size();j++){
                ans[i+1].push_back(tmp[i][j]);
            }
        }
    }
    return ans;
}

int main()
{
    int n;
    cin >> n;
    vector<string> elementos(n);
    for(int i=0;i<n;i++) cin >> elementos[i];
    /*vector< vector<string> > p_s = power_set_2<string>(elementos);
    for(vector<string> c:p_s){
        for(string i:c) cout << i << " ";
        cout << endl;
    }*/
    vector< vector< vector<string> > > p_s = power_set_3<string>(elementos);
    cout << "--" << endl;
    int i = 0;
    for(vector< vector<string > > c:p_s){
        cout << "Conjuntos de cardinalidad " << i << ":" << endl;
        for(vector<string> s:c){
            for(string i:s) cout << i << " ";
            cout << endl;
        }
        i++;
    }
    return 0;
}
