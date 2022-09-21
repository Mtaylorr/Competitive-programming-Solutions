//https://codeforces.com/problemset/problem/400/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 1e9 + 7 ;

int id[N];
int n,m,k;
int u[N],v[N], x[N];
int b[N],c[N];
ll dist[505][505];
set<int> s[505];

int getid(int u){
    return (id[u]==u?u:id[u]=getid(id[u]));
}

void uni(int u, int v){
    u=getid(u);
    v=getid(v);
    id[u]=v;
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> k;
    int j=0;
    for(int i=0;i<k;i++){
        cin >> c[i];
        for(int o=0;o<c[i];o++){
            b[j]=i;
            id[j]=j;
            j++;
        }
    }
    for(int i=0;i<m;i++){
        cin >> u[i] >> v[i] >> x[i];
        u[i]--;v[i]--;
        if(x[i]==0){
            uni(u[i],v[i]);
        }
    }
    for(int i=0;i<n;i++){
        s[b[i]].insert(getid(i));
    }
    for(int i=0;i<k;i++){
        if(s[i].size()!=1){
            cout << "No";
            return 0;
        }
    }
    for(int i=0;i<k;i++){

        for(int j=0;j<k;j++){
            dist[i][j] = 1e18;
        }
        dist[i][i]=0;
    }
    for(int i=0;i<m;i++){
        int a = b[u[i]];
        int c = b[v[i]];
        dist[a][c]=min(dist[a][c],(ll)x[i]);
        dist[c][a]=min(dist[c][a],(ll)x[i]);
    }
    for(int o=0;o<k;o++){
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                dist[i][j]=min(dist[i][j], dist[i][o]+dist[o][j]);
            }
        }
    }
    cout << "Yes\n";
    for(int i=0;i<k;i++) {
        for (int j = 0; j < k; j++) {
            if (dist[i][j] < 1e18) {
                cout << dist[i][j] << " ";
            } else {
                cout << -1 << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}
