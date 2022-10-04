//https://codeforces.com/problemset/problem/899/E

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

int id[N];
int l[N],r[N];
int sz[N];
int a[N];
set<pair<int,int> > s;
int n;
int getid(int u){
    return (id[u]==u?u:id[u]=getid(id[u]));
}
bool done[N];

void uni(int u , int v){
    u=getid(u);
    v=getid(v);
    if(u==v)
        return ;
    id[v]=u;
    sz[u]+=sz[v];
    l[u]=min(l[u],l[v]);
    r[u]=max(r[u],r[v]);
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
        id[i]=i;
        l[i]=r[i]=i;
        sz[i]=1;
    }
    for(int i=1;i<n;i++){
        if(a[i]==a[i-1]){
            uni(i-1,i);
        }
    }
    for(int i=0;i<n;i++){
        if(getid(id[i])==i){
            s.insert({-sz[i], i});
        }
    }
    int ans=0;
    while(!s.empty()){
        pair<int,int> p  = *s.begin();
        s.erase(s.begin());
        if(done[getid(p.se)]){
            continue;
        }
        done[p.se]=1;
        int lf = l[getid(p.se)]-1;
        int rg = r[getid(p.se)]+1;
        if(lf>=0 && done[getid(lf)]){
            uni(p.se,lf);
        }
        if(rg<n && done[getid(rg)]){
            uni(p.se, rg);
        }
        ans++;
        lf = l[getid(p.se)]-1;
        rg = r[getid(p.se)]+1;
        if(lf>=0 && rg<n && a[lf]==a[rg]){
            uni(lf, rg);
            int id = getid(lf);
            s.insert({-sz[id], id});
        }
    }
    cout << ans;
    return 0;

}
