#include <bits/stdc++.h>

using namespace std;

using lli = long long int;
const int mod = 1e9 + 7;

vector<string> split_string(string);

auto phiSieve(int n){
    vector<int> phi(n+1);
    iota(phi.begin(), phi.end(), 0);
    for(int i = 2; i <= n; ++i){
        if(phi[i] == i){
            for(int j = i; j <= n; j += i){
                phi[j] -= phi[j] / i;
            }
        }
    }
    return phi;
}

// Complete the solve function below.
int solve(const vector<int> & arr) {
    int mini = *min_element(arr.begin(), arr.end());
    auto phi = phiSieve(mini);
    int ans = 0;
    for(int d = 1; d <= mini; ++d){
        lli prod = 1;
        for(int xi : arr){
            prod = prod * (xi / d) % mod;
        }
        ans += phi[d] * prod % mod;
        if(ans >= mod) ans -= mod;
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while(t--){

        int n_count;
        cin >> n_count;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string n_temp_temp;
        getline(cin, n_temp_temp);

        vector<string> n_temp = split_string(n_temp_temp);

        vector<int> n(n_count);

        for (int i = 0; i < n_count; i++) {
            int n_item = stoi(n_temp[i]);

            n[i] = n_item;
        }

        int result = solve(n);

        fout << result << "\n";
    }


    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
