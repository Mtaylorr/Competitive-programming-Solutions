//https://tlx.toki.id/problems/troc-25/E
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 +1 ;
const int MOD = 998244353 ;

int n,q;
vector<int> adj[N];
int a[N],u,v;
int sz[N];
vector<int> bigset;
vector<int> adjb[N];
int bigid[N];
int B,nb;
int sum[N];
int distr[N];
int ans[N];

int dist2[420][N];

void dfs(int u, int id,int d=0, int p=-1){
    if(d==2){
        dist2[id][u]=1;
        return ;
    }
    for(auto v:adj[u]){
        if(v==p)
            continue;
        dfs(v,id, d+1, u);
    }
}

int main(){
    //freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    B=sqrt(n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        sum[i]=a[i];
    }
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        --u;--v;
        sz[u]++;
        sz[v]++;
        adj[u].pb(v);
        adj[v].pb(u);
        ans[v]+=a[u];
        ans[u]+=a[v];
        ans[u]%=MOD;
        ans[v]%=MOD;
    }
    for(int i=0;i<n;i++){
        if(sz[i]<B){
            bigid[i]=-1;
        }else{
            dfs(i,nb);
            dist2[nb][i]=sz[i];
            bigid[i]=nb++;
            bigset.pb(i);
        }
    }
    for(auto u:bigset){
        for(auto v:adj[u]){
            if(bigid[v]!=-1){
                adjb[u].pb(v);
            }
        }
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&v,&u);
        u--;
        if(v==1){
            if(bigid[u]!=-1){
                distr[u]+=sum[u];
                distr[u]%=MOD;
                for(auto v:adjb[u]){
                    sum[v]+=sum[u];
                    sum[v]%=MOD;
                }
                for(int i=0;i<nb;i++){
                    int ii= bigset[i];
                    ans[ii]=(ans[ii]+(dist2[i][u]*1ll*sum[u])%MOD)%MOD;
                }

            }else{
                int newa = a[u];
                for(auto v:adj[u]){
                    if(bigid[v]!=-1){
                        newa+=distr[v];
                        newa%=MOD;
                    }
                }
                for(auto v:adj[u]){
                    a[v]+=newa;
                    a[v]%=MOD;
                }
                for(auto v:adj[u]){
                    if(bigid[v]!=-1){
                        sum[v]+=newa;
                        sum[v]%=MOD;
                    }
                }
                for(int i=0;i<nb;i++){
                    int ii= bigset[i];
                    ans[ii]=(ans[ii]+(dist2[i][u]*1ll*newa)%MOD)%MOD;
                }
            }
        }else{
            if(bigid[u]==-1){
                int ans=0;
                for(auto v:adj[u]){
                    ans+=a[v];
                    ans%=MOD;

                }
                for(int i=0;i<nb;i++){
                    ans=(ans+(dist2[i][u]*distr[bigset[i]])%MOD)%MOD;
                }
                cout << ans << endl;
            }else{
                cout << ans[u] << endl;
            }
        }
    }




    return 0;
}
