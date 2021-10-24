#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 +5 ;
const int MOD = 1e9 +7;

int t,n1,n2;
vector<int> adj[2][N];
int subtree[2][N];
int dp[2][N];
int ans;

void buildsubtree(int u,int b, int p=-1){
    subtree[b][u]=0;
    int mx1=0;
    int mx2=0;
    for(auto v: adj[b][u]){
        if(v==p)
            continue;
        buildsubtree(v,b,u);
        if(subtree[b][v]+1>mx1){
            mx2=mx1;
            mx1=1+subtree[b][v];

        }else{
            mx2=max(mx2, 1+subtree[b][v]);
        }
        subtree[b][u]=max(subtree[b][u], 1+subtree[b][v]);
    }
    ans=max(ans, mx1+mx2);
}

void builddp(int u, int b, int p=-1, int fromtop=0){
    multiset<int> ss;
    ss.insert(-fromtop);
    for(auto v:adj[b][u]){
        if(p==v)
            continue;
        ss.insert(-(1+subtree[b][v]));
    }
    int cnt=0;
    dp[b][u]=0;
    for(auto o:ss){
        if(cnt>=1)
            break;
        cnt++;
        dp[b][u]+=(-o);
    }
    //cout << b << " " << u+1 << " "<< dp[b][u]<<" "<<fromtop << endl;

    for(auto v:adj[b][u]){
        if(p==v)
            continue;
        ss.erase(ss.find(-(1+subtree[b][v])));
        int mx = -(*ss.begin());
        builddp(v, b, u, mx+1);
        ss.insert(-(1+subtree[b][v]));
    }
}


int x,y;
int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n1);
        for(int i=0;i<n1;i++){
            adj[0][i].clear();
        }
        for(int i=0;i<n1-1;i++){
            scanf("%d%d",&x,&y);
            x--;y--;
            adj[0][x].pb(y);
            adj[0][y].pb(x);
        }

        scanf("%d",&n2);
        for(int i=0;i<n2;i++){
            adj[1][i].clear();
        }
        for(int i=0;i<n2-1;i++){
            scanf("%d%d",&x,&y);
            x--;y--;
            adj[1][x].pb(y);
            adj[1][y].pb(x);
        }

        ans=0;
        buildsubtree(0,0);
        //cout << ans << endl;
        buildsubtree(0,1);
        //cout << ans << endl;

        builddp(0,0);
        builddp(0,1);
        int ans1=n1+2;
        int ans1v=0;
        for(int i=0;i<n1;i++){
            if(dp[0][i]<ans1){
                ans1=dp[0][i];
                ans1v=i;
            }
        }

        int ans2=n2+2;
        int ans2v=0;
        for(int i=0;i<n2;i++){
            if(dp[1][i]<ans2){
                ans2=dp[1][i];
                ans2v=i;
            }
        }
        ans=max(ans,ans1+ans2+1);
        cout << ans << endl;
        cout << ans1v+1 << " " << ans2v+1 << endl;
    }
    return 0;
}
