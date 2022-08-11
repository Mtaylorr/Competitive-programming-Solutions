//https://codeforces.com/problemset/problem/1601/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5, E = 2*(2e5 + 5);
const int MOD = 1e9 + 7;

int n;
int a[N];
int b[N];
int par[N];
int dist[N];
bool vis[N];
set<int> ss;

void bfs(){
    queue<int> q;
    for(int i=0;i<=n;i++){
        par[i]=-1;
        dist[i]=1e9;
        ss.insert(i);
    }
    q.push(n);
    dist[n]=0;
    vis[n]=1;
    while(!q.empty()){
        int u = q.front();
        int u_u = u;
        u+=b[u];
        q.pop();
        ss.insert(u-a[u]);
        set<int> ::iterator it = ss.find(u-a[u]);
        set<int> tmp;
        while(it!=ss.end() && *it<=u-1){
            int v = *it;
            tmp.insert(v);
            if(vis[v]){
                it++;
                continue;
            }
            q.push(v);
            it++;
            vis[v]=1;
            dist[v]=dist[u_u]+1;
            par[v]=u_u;
        }
        for(auto v:tmp){
            ss.erase(v);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        cin >> b[i];
    }
    bfs();
    if(dist[0]<1e9){
        cout << dist[0] << endl;
        vector<int> v;
        int cur = 0;
        while(cur!=n){
            v.pb(cur);
            cur=par[cur];
        }
        for(int i=v.size()-1;i>=0;i--){
            cout <<v[i] << " ";
        }
        cout << endl;
    }else{
        cout << -1 << endl;
    }
    return 0;

}
