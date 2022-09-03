//https://codeforces.com/problemset/problem/1715/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 1 << 17;
const int MOD =  1e9 + 7;

int n,q;
int x[N], y[N], d[N];
int ands[N], val[N];
vector<pair<int,int> > adj[N];

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    int mx = (1<<30)-1;
    for(int i=0;i<n;i++){
        ands[i]=mx;
    }
    for(int i=0;i<q;i++){
        cin >> x[i] >> y[i] >> d[i];
        x[i]--;y[i]--;
        if(x[i]==y[i]){
            val[x[i]]=d[i];
            ands[x[i]]=d[i];
            continue;
        }
        adj[x[i]].pb({y[i],d[i]});
        adj[y[i]].pb({x[i],d[i]});
        ands[x[i]]=(ands[x[i]]&d[i]);
        ands[y[i]]=(ands[y[i]]&d[i]);
    }
    for(int i=0;i<q;i++){
        val[x[i]]=(val[x[i]]|(d[i]^ands[y[i]]));
        val[y[i]]=(val[y[i]]|(d[i]^ands[x[i]]));
    }
    for(int i=0;i<n;i++){
        cout << val[i] << " ";
        for(auto u:adj[i]){
            int v = u.fi;
            int d = u.se;
            if(v<i)
                continue;
            int rem = d^val[i];
            val[v]=(val[v]|rem);
        }
    }
    return 0;
}
