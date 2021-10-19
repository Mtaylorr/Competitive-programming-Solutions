#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e5+5;
const int MOD = 1e9 +7;

ll mul(ll u , ll v, ll mod=MOD){
	return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
	return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
	return ((u%mod)-(v%mod)+mod)%mod;
}

ll powe(ll u, ll v, ll mod=MOD){
	ll ans=1;
	ll acc=u;
	while(v){
		if(v%2){
			ans=mul(ans,acc,mod);
		}
		acc = mul(acc,acc,mod);
		v/=2;
	}
	return ans;
}
vector<int> adj[N], radj[N], topo;
bool vis[N];
int n,m;
ll v[N];
ll ans[N];
int mx[N], cnt[N];
int zeros[N];
int a,b;

void init(){
    for(int i=0;i<n;i++){
        adj[i].clear();
        radj[i].clear();
        vis[i]=0;
        ans[i]=-1e18;
        cnt[i]=0;
        mx[i]=-1e9;
    }
    topo.clear();
}


void topoSort(int u){
    if(vis[u])
        return ;
    vis[u]=1;
    for(auto v: adj[u]){
        if(vis[v])
            continue;
        topoSort(v);
    }
    topo.pb(u);
}

void dfs(int u, int cmp){
    if(vis[u])
        return ;
    vis[u]=1;
    if(v[u]==0){
        zeros[cmp]++;
    }
    ans[cmp]=max(max(ans[cmp], v[u]), ans[cmp]+v[u]);
    if(v[u]>mx[cmp]){
        mx[cmp]=v[u];
        cnt[cmp]=1;
    }else if(v[u]==mx[cmp]){
        cnt[cmp]++;
    }
    for(auto v:radj[u]){
        if(vis[v])
            continue;
        dfs(v,cmp);
    }
}
int t;
int main(){
    freopen("input.txt", "r", stdin);
    //freopen("safe.in", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=0;i<n;i++){
            scanf("%lld",&v[i]);
        }
        for(int i=0;i<m;i++){
            scanf("%d%d",&a,&b);
            --a;--b;
            adj[a].pb(b);
            radj[b].pb(a);
        }
        for(int i=0;i<n;i++){
            if(!vis[i])
                topoSort(i);
        }
        reverse(topo.begin(), topo.end());
        for(int i=0;i<n;i++)
            vis[i]=0;
        int cmp=0;
        for(auto i:topo){
            if(vis[i])
                continue;
            dfs(i,cmp);
            cmp++;
        }
        ll sum=0;
        ll poss=1;
        for(int i=0;i<cmp;i++){
            sum+=ans[i];
            if(ans[i]>0){
                if(zeros[i]>0){
                    poss=mul(poss, powe(2,zeros[i]));
                }
            }else if(ans[i]==0){
                poss=mul(poss, sub(powe(2,zeros[i]),1));
            }else {
                poss=mul(poss, cnt[i]);
            }
        }
        printf("%lld %lld\n", sum, poss);

    }
    return 0;
}
