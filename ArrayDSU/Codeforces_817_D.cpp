//https://codeforces.com/problemset/problem/817/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5, E = 1 << 17;
const int MOD =  998244353;

vector<int> pos[N];
int a[N];
int id[N];
int n;
int sz[N];
void init(){
    for(int i=0;i<n;i++){
        id[i]=i;
        sz[i]=1;
    }
}

int getid(int u){
    return(id[u]==u?u:id[u]=getid(id[u]));
}

void uni(int u, int v){
    u = getid(u);
    v=getid(v);
    if(u==v)
        return ;
    id[u]=v;
    sz[v]+=sz[u];
    sz[u]=0;
}

int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    init();
    for(int i=0;i<n;i++){
        cin >> a[i];
        pos[a[i]].pb(i);
    }
    ll ans=0;
    for(int i=1e6;i>=1;i--){
        for(int j=0;j<pos[i].size();j++){
            int x = pos[i][j];
            if(x>0 && a[x-1]>=i){
                uni(x,x-1);
            }
            int l = sz[getid(x)];
            int r = 1;
            if(x<n && a[x+1]>i){
                r=1+sz[getid(x+1)];
            }
            if(x+1<n && a[x+1]>=i){
                uni(x,x+1);
            }

            ans-=i*1ll*l*1ll*r;
        }
    }
    init();
    for(int i=1;i<=1e6;i++){
        for(int j=0;j<pos[i].size();j++){
            int x = pos[i][j];
            if(x>0 && a[x-1]<=i){
                uni(x,x-1);
            }
            int l = sz[getid(x)];
            int r = 1;
            if(x+1<n && a[x+1]<i){
                r=1+sz[getid(x+1)];
            }
            if(x+1<n && a[x+1]<=i){
                uni(x,x+1);
            }
            ans+=i*1ll*l*1ll*r;
        }
    }
    cout << ans << endl;
    return 0;
}
