//https://codeforces.com/problemset/problem/1494/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;

int n;
int a[505][505];
set<int> s[505];
bool vis[1505];
int c[N];
int id[N];
int par[N];
int ndcnt=0;
int curnode[N];

int addnode(){
    id[ndcnt]=ndcnt;
    curnode[ndcnt]=ndcnt;
    par[ndcnt]=-1;
    return ndcnt++;
}

int getid(int u){
    return (id[u]==u?u:id[u]=getid(id[u]));
}

void uni(int u, int v){
    u=getid(u);
    v=getid(v);
    if(u<v)
        swap(u,v);
    id[u]=v;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> a[i][j];
            s[i].insert(a[i][j]);
        }
        c[i]=a[i][i];
        s[i].erase(s[i].begin());
    }
    for(int i=0;i<n;i++){
        addnode();
    }
    bool cond=true;

    while(cond){
        cond=false;
        memset(vis, 0, sizeof(vis));
        for(int i=0;i<n;i++){
            if(getid(i)!=i)
                continue;
            if(vis[i])
                continue;
            vector<int> tmp;
            tmp.pb(i);
            int nb=1;
            for(int j=0;j<n;j++){
                if(getid(i)==getid(j))
                    continue;
                if(getid(j)!=j)
                    continue;
                nb+=(a[j][i]==(*s[i].begin()));
                if((*s[i].begin())!=(*s[j].begin()))
                    continue;

                if(a[i][j]!=(*s[i].begin()))
                    continue;
                tmp.pb(j);
            }
            if(tmp.size()>=2 && tmp.size()==nb){
                cond=true;
                int p = addnode();
                c[p]=*s[i].begin();
                for(auto u:tmp){
                    par[curnode[u]]=p;
                    uni(u,i);
                    vis[u]=1;
                    s[u].erase(s[u].begin());
                }
                curnode[getid(i)]=p;
            }
        }
    }
    cout << ndcnt << "\n";
    for(int i=0;i<ndcnt;i++){
        cout << c[i] << " ";
    }
    cout << "\n";
    cout << ndcnt << "\n";
    for(int i=0;i<ndcnt;i++){
        if(par[i]!=-1){
            cout << i+1 << " " << par[i]+1 << "\n";
        }
    }



    return 0;

}
