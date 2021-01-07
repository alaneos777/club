#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct node{
    int num;
    node* next;
    node(int num): num(num), next(NULL) {}
};

int main(){
    string line;
    cin >> line;
    int n = 1e6;
    vector<int> nums;
    node* tail = new node(0);
    node* head = tail;
    vector<node*> mp(n+1);
    for(char c : line){
        nums.push_back(c-'0');
    }
    for(int i = 10; i <= n; ++i){
        nums.push_back(i);
    }
    for(int x : nums){
        node* New = new node(x);
        mp[x] = New;
        tail->next = New;
        tail = New;
    }
    node* first = head->next;
    tail->next = new node(0);
    for(int k = 1; k <= 1e7; ++k){
        int a = first->num;
        int b = first->next->num;
        int c = first->next->next->num;
        int d = first->next->next->next->num;
        node* sub = first->next;
        first->next = first->next->next->next->next;
        sub->next->next->next = NULL;
        int target = a-1;
        if(target == 0) target = n;
        node* idx = NULL;
        while(true){
            node* pos = mp[target];
            if(pos->num == target && pos->num != b && pos->num != c && pos->num != d){
                idx = pos;
                break;
            }else{
                target--;
                if(target == 0) target = n;
            }
        }
        node* after = idx->next;
        idx->next = sub;
        sub->next->next->next = after;
        if(idx == tail) tail = sub->next->next;
        node* e = first;
        first = head->next = first->next;
        e->next = tail->next;
        tail->next = e;
        tail = e;
    }
    tail->next = NULL;
    
    node* start = mp[1]->next;
    if(!start) start = first;
    lli x = start->num;
    start = start->next;
    if(!start) start = first;
    lli y = start->num;
    
    cout << x*y << endl;
    return 0;
}