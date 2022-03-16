#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 +7 ;


vector<pair<int,int> > zone;

int n;
int c=1;
int curC=0;
char s[20][20];
int cc[20][20];
bool vis[20][20];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int sz;
int pos[20][20];
int po[22];

bool ingrid(int i,int j){
    return i>=0 && i<n && j>=0 && j<n;
}

int isvalid(int i,int j){
    if(s[i][j]=='x' || s[i][j]=='*')
        return 0;
    for(int k=0;k<4;k++){
        int ni = i+dx[k];
        int nj = j+dy[k];
        if(ingrid(ni,nj) && s[ni][nj]=='*'){
            return cc[ni][nj];
        }
    }
    return 0;
}

void dfs(int i, int j){
    if(vis[i][j])
        return ;
    pos[i][j]=zone.size();
    vis[i][j]=1;
    zone.pb({i,j});
    for(int k=0;k<4;k++){
        int ni = i+dx[k];
        int nj = j+dy[k];
        if(ingrid(ni,nj) && isvalid(ni,nj)==curC){
            dfs(ni,nj);
        }
    }
}

void calcCC(int i,int j){
    if(vis[i][j])
        return ;
    vis[i][j]=1;
    cc[i][j]=c;
    for(int k=0;k<4;k++){
        int ni = i+dx[k];
        int nj = j+dy[k];
        if(ingrid(ni,nj) && s[ni][nj]=='*'){
            calcCC(ni,nj);
        }
    }
}

int dp[1048576+5];

int solve(int mask){
    if(dp[mask]!=-1)
        return dp[mask];
    if(mask==po[sz]-1)
        return 0;
    set<int> tmp;
    for(int i=0;i<sz;i++){
        if(mask&po[i])
            continue;
        int cur=po[i];
        for(int k=0;k<4;k++){
            int ni = zone[i].fi+dx[k];
            int nj = zone[i].se+dy[k];
            if(ingrid(ni,nj) && isvalid(ni,nj)==curC){
                cur=(cur|po[pos[ni][nj]]);
            }
        }
        tmp.insert(solve(mask|cur));
    }
    int j=0;
    while(tmp.count(j)){
        j++;
    }
    tmp.clear();
    return dp[mask]=j;

}

int main()
{
    //freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    po[0]=1;
    for(int i=1;i<21;i++){
        po[i]=2*po[i-1];
    }
    for(int i=0;i<n;i++){
        scanf("%s",s[i]);
    }
    int g=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(vis[i][j])
                continue;
            if(s[i][j]=='*'){
                calcCC(i,j);
                c++;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(vis[i][j])
                continue;
            if(s[i][j]=='*' || s[i][j]=='x')
                continue;
            curC=isvalid(i,j);
            if(curC){
                zone.clear();
                dfs(i,j);
                sz=zone.size();
                for(int k=0;k<po[sz];k++){
                    dp[k]=-1;
                }
                int x = solve(0);
                g=g^x;
            }
        }
    }
    if(!g){
        puts("Second player will win");
    }else{
        puts("First player will win");
    }

    return 0;

}
