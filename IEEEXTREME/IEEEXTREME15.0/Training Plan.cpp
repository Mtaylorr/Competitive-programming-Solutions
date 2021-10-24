#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

#define neig(u,v,e) for(int e=head[u],v;(e!=-1) && (v=to[e],1); e=nxt[e])

const int N = 2e5 +5 ;

int t,m,x,y,k;
vector<int> v[1005];

void init(){
    for(int i=1;i<=m;i++)
        v[i].clear();
}
int u;

ll dp[2][1005][1005][21];

ll getlast(int id, int i, int j, int o){
    if(i<0){
        return dp[id^1][x-1][y][o];
    }
    return dp[id][i][j][o];
}


int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d%d",&m,&x,&y,&k);
        init();
        for(int i=1;i<=m;i++){
            for(int j=0;j<x;j++){
                scanf("%d",&u);
                v[i].pb(u);
            }
        }

        for(int j=0;j<x;j++){
            for(int u=0;u<=y;u++){
                for(int o=0;o<=k;o++){
                    dp[0][j][u][o]=-1e16;
                }
            }
        }

        dp[0][x-1][y][0]=0;
        ll ans=-1;

        for(int i=1;i<=m;i++){
            int id = i&1;
            for(int j=0;j<x;j++){

                for(int u=0;u<=y;u++){
                    dp[id][j][u][0]=-1e16;
                    if(u<=j)
                        for(int o=0;o<=k;o++){
                            dp[id][j][u][0]=max(dp[id][j][u][0], getlast(id, j-1,u,o));
                        }
                    //cout << id << " " << j << " " << u << " "<<0<<" "<<dp[id][j][u][0] << endl;
                    for(int o=1;o<=k;o++){
                        dp[id][j][u][o]=-1e16;
                    }
                    if(u<=j+1 && u>0)
                        for(int o=1;o<=k;o++){
                            dp[id][j][u][o] = v[i][j]+getlast(id, j-1,u-1, o-1);
                           // cout << id << " " << j << " " << u << " "<<o<<" "<<dp[id][j][u][o] << endl;
                        }
                }
            }
        }
        ans=-1e17;
        for(int i=0;i<=k;i++){
            ans=max(ans, dp[m&1][x-1][y][i]);
        }
        if(ans>0){
            cout << ans << endl;
        }else{
            puts("IMPOSSIBLE");
        }


    }
    return 0;
}
