//https://algo.monster/problems/amazon-oa-shipment-imbalance?fbclid=IwAR2ovjdm7njje0KEBxrXAuXmLfW4JJ-llo825d2TlrSQc2SkkEY9zOePL6s
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 +7 ;

vector<int> pos[N];
int l[N],r[N],id[N];
int a[N];
int n;

int getid(int u){
    return(id[u]==u?u:id[u]=getid(id[u]));
}

void mrg(int u, int v){
    u=getid(u);
    v=getid(v);
    if(u==v)
        return ;
    id[v]=u;
    l[u]=min(l[u],l[v]);
    r[u]=max(r[u],r[v]);
}

void init_dsu(){
    for(int i=0;i<n;i++){
        id[i]=i;
        l[i]=r[i]=i;
    }
}

int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        pos[a[i]].pb(i);
    }
    ll ans=0;
    init_dsu();
    for(int i=0;i<N;i++){
        for(auto u:pos[i]){
            if(u-1>=0 && a[u-1]<=i){
                mrg(u-1,u);
            }
            if(u+1<n && a[u+1]<=i){
                mrg(u+1,u);
            }
        }
        int last= -1;
        for(auto u:pos[i]){
            int v = getid(u);
            int curl = max(last+1, l[v]);
            last = u;
            ans+=i**1ll*(r[v]-u+1)*(u-curl+1);
        }
    }

    init_dsu();
    for(int i=N-1;i>=0;i--){
        for(auto u:pos[i]){
            if(u-1>=0 && a[u-1]>=i){
                mrg(u-1,u);
            }
            if(u+1<n && a[u+1]>=i){
                mrg(u+1,u);
            }
        }
        int last= -1;
        for(auto u:pos[i]){
            int v = getid(u);
            int curl = max(last+1, l[v]);
            last = u;
            ans-=i*1ll*(r[v]-u+1)*(u-curl+1);
        }
    }
    cout << ans;

    return 0;

}

