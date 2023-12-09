// SCC IMPLEMENTATION (sample):

#include <bits/stdc++.h>
using namespace std; typedef long long ll; typedef long double ld;
const int inf = INT_MAX; const ll INF = LLONG_MAX;
#define nl '\n'

const int n = 8;

vector<vector<int>> connected(n,vector<int>()); //stores the SCCs
vector<vector<int>> adj(n,vector<int>());
vector<vector<int>> rev(n,vector<int>());
vector<pair<int,int>> t1(n,{0,0}); //{node,departure_time}
vector<bool> found(n,0);
int curr;

void dfs(int node){
    ++curr;
    found[node] = 1;
    for(int i : adj[node]){
        if(found[i]) continue;
        dfs(i);
    }
    t1[node].second = ++curr; 
}

void dfs(int node, int value){
    connected[value].push_back(node);
    found[node]=1;
    for(int i : rev[node]){
        if(!found[i]) dfs(i,value);
    }
}

void solve(){ //SCC

    int m = 10; //no of edges in the input below
    int x,y;
    while(m--){
        cin>>x>>y;
        adj[x].push_back(y);
        rev[y].push_back(x);
    }

    curr=0;
    for(int i=1;i<n;i++){
        t1[i].first = i;
        if(!found[i]) {
            dfs(i);
        }
    }
    sort(t1.begin(),t1.end(),[](const pair<int,int> &a,const pair<int,int>&b){
        return a.second < b.second; //sorting in rev order of leaving node.
    });

    reverse(t1.begin(),t1.end());
    found.assign(n,0);

    int value=0;
    for(int i=0;i<n-1;i++){
        if(!found[t1[i].first]) {
            dfs(t1[i].first,value);
            ++value;
        }
    }

    for(int j=0;j<value;j++){ //reverse topologically sorted iteration.
        for(int i : connected[j]){
            cout<<i<<' ';
        }
        cout<<nl;
    }

}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout<<fixed; cout << setprecision(11);
    // freopen("input.txt","r",stdin);
    int tc = 1;
    // cin >> tc;
    while(tc--){ solve(); }
    return 0;
}

//Try with this input.
//Note: change n and m if you want to give different inputs.

// 1 2 
// 2 1
// 1 4
// 2 5
// 5 4
// 3 2
// 6 5
// 3 7
// 7 6
// 6 3
