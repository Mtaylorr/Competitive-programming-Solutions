//https://codeforces.com/problemset/problem/59/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 3e5 + 100, M = 1000 + 5, E = 2e6 + 5;
const int MOD = 1e9 + 7;

int n, m, k;
vector<int> adj[N];
map<int,int> dist[3005];
set<pair<pair<int,int>,int> > ss;
unordered_map<int,bool> vis[3005];
unordered_map<int,int> par[3005];

void bfs() {
    dist[0][0]=0;
    pair<int,int> p;
    queue<pair<int,int> > q;
    q.push({0,0});
    vis[0][0]=1;
    while(!q.empty()){
        p=q.front();
        q.pop();
        for(auto v:adj[p.se]){
            if(vis[p.se][v])
                continue;
            if(ss.count({{p},v}))
                continue;
            vis[p.se][v]=1;

            dist[v][p.se]=dist[p.se][p.fi]+1;
            q.push({p.se, v});
            par[p.se][v]=p.fi;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    for (int i = 0; i < k; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x--, y--, z--;
        ss.insert({{x,y},z});
    }

    bfs();
    int di = 1e9;
    int p=-1;
    for(auto u:dist[n-1]) {
        if(di>u.se){
            p=u.fi;
            di=u.se;
        }
    }
    if (di < 1e9){
        vector<int> path;
        cout << di << "\n";
        int b=n-1;
        int a = p;
        path.pb(b);
        while(b!=0){
            path.pb(a);
            int tmp = par[a][b];
            b=a;
            a=tmp;
        }
        reverse(path.begin(),path.end());
        for(auto u:path){
            cout << u+1 << " ";
        }
    }
    else
        cout << -1;

    return 0;

}
