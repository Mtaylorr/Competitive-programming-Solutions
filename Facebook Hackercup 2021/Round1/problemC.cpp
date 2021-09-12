#include <bits/stdc++.h>

using namespace std;
const int N = 1e6+5;
const int MOD = 1e9 + 7;

#define fi first
#define se second
#define pb push_back

typedef long long ll;

ll mul(ll u , ll v, ll mod=MOD){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
    return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
    return ((u%mod)-(v%mod)+mod)%mod;
}

int t;
int n;
int u,v;
int c[N];
vector<pair<int,int> >adj[N];
int dp[N];
int cn[N][20];
int ans[N];

void init(){
    for(int i=0;i<=n;i++){
        adj[i].clear();
        for(int j=0;j<=20;j++){
            cn[i][j]=0;
        }
        dp[i]=0;
    }
}
int cnt[22];

void dfs(int u, int p=-1){
    dp[u]=0;
    for(auto v:adj[u]){
        if(v.fi==p)
            continue;
        dfs(v.fi,u);
        dp[u]=add(dp[u],dp[v.fi]);
    }
    memset(cnt, 0, sizeof(cnt));
    for(auto v:adj[u]){
        if(v.fi==p)
            continue;
        int othercnt=0;
        for(int j=20;j>=c[v.se];j--){
            othercnt=add(othercnt,cnt[j]);
        }
        int ser=0;
        othercnt = add(othercnt,1);
        for(int j=20;j>=c[v.se];j--){
            int curc = j;
            int curcnt = cn[v.fi][j];
            if(j==c[v.se])
                curcnt=add(curcnt,1);
            ser=add(ser,cn[v.fi][j]);
            cn[u][c[v.se]]=add(cn[u][c[v.se]], curcnt);
            dp[u]=add(dp[u],mul(c[v.se],mul(curcnt, othercnt)));
        }
        ser=add(ser,1);

        //cout << u << " "<<v.fi<<" " << dp[u] << endl;
        for(int j=c[v.se]-1;j>=1;j--){
            int curc = j;
            int curcnt = cn[v.fi][j];
            int x = cn[u][j];
            dp[u]=add(dp[u],mul(curc,mul(x, ser)));
            cn[u][j]=add(cn[u][j], curcnt);
            othercnt=add(othercnt,cnt[j]);
            dp[u]=add(dp[u],mul(curc,mul(curcnt, othercnt)));
            ser=add(ser, curcnt);
        }
        //cout << u << " "<<v.fi<<" " << dp[u] << endl;

        for(int j=0;j<=20;j++){
            int curc = min(j,c[v.se]);
            int curcnt = cn[v.fi][j];
            if(j==c[v.se])
                curcnt=add(curcnt,1);
            cnt[curc]=add(cnt[curc],curcnt);
        }
    }
}
vector<int> res;
void solve(int u, vector<int> curcnt, int p=-1){
    for(auto v:adj[u]){
        if(v.fi==p)
            continue;
        for(int j=0;j<=20;j++){
            int x = min( j, c[v.se]);
            curcnt[x]=add(curcnt[x],cn[v.fi][j]);
        }
        curcnt[c[v.se]]=add(curcnt[c[v.se]],1);
    }
    for(auto v:adj[u]){
        if(v.fi==p)
            continue;
        int res=0;
        int ser = 0;
        curcnt[c[v.se]]=sub(curcnt[c[v.se]],1);
        for(int j=c[v.se];j<=20;j++){
            int x = sub(curcnt[j],cn[v.fi][j]);
            res=add(res,x);
            ser=add(ser, cn[v.fi][j]);

        }
        ser=add(ser,1);
        res=add(res,1);
        ans[v.se]=mul(c[v.se],mul(res, ser));
       /* cout << u << " " << v.fi << " " << res << " " << ser <<" " <<ans[v.se]<< endl;
        cout <<"cnt = \n";
        for(int i=0;i<=20;i++){
            cout << curcnt[i]-cn[v.fi][i] << " ";
        }
        cout << endl;
        for(int i=0;i<=20;i++){
            cout << cn[v.fi][i] << " ";
        }
        cout << endl;*/
        for(int j=c[v.se];j>=1;j--){
            int y =sub(curcnt[j-1], cn[v.fi][j-1]);
            res=add(res, y );
            int z = cn[v.fi][j-1];
            ans[v.se]=add(ans[v.se],mul(j-1,mul(z, res)));
            ans[v.se]=add(ans[v.se],mul(j-1,mul(y, ser)));
            //cout << j-1 << " " << z << " " << res << endl;
            //cout << j-1 << " " << y << " " << ser<< endl;

            ser=add(ser, z);

        }
        curcnt[c[v.se]]=add(curcnt[c[v.se]],1);
       // cout << v.se << " " << ans[v.se] << endl;
    }

    for(auto v:adj[u]){
        if(v.fi==p)
            continue;
        int res=0;
        int ser = 0;
        vector<int> newcnt(22,0);
        for(int j=0;j<=20;j++){
            newcnt[min(j,c[v.se])]=add(newcnt[min(j,c[v.se])],sub(curcnt[j],cn[v.fi][j]));
        }
        solve(v.fi, newcnt,u);
    }
}
bool cmp(pair<int,int> &x, pair<int,int> &y){
    return c[x.se]>c[y.se];
}

int main(){
    freopen("blockchain_input.txt", "r", stdin);
    freopen("output.txt","w", stdout);
    scanf("%d",&t);
    int tt=0;
    while(t--){
        scanf("%d",&n);
        cout << n<< endl;
        init();
        for(int i=0;i<n-1;i++){
            scanf("%d%d%d",&u,&v,&c[i]);
            --u,--v;
            adj[u].pb({v,i});
            adj[v].pb({u,i});
        }
        for(int i=0;i<n;i++){
            sort(adj[i].begin(),adj[i].end(),cmp);
        }
        dfs(0);
        //cout << dp[0] << endl;
        res.assign(22,0);
        solve(0,res);
        int anss=1;
        //cout << ans[1] << endl;
        for(int i=0;i<n-1;i++){
            anss=mul(anss, sub(dp[0], ans[i]));
        }
        printf("Case #%d: %lld\n",++tt,anss);
    }
    return 0;
}
