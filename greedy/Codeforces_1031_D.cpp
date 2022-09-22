//https://codeforces.com/problemset/problem/1031/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 3e5 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 1e9 + 7  ;
const double eps = 1e-7;


char grid[2005][2005];
pair<int,int> nxt[2005][2005];
int val[2005][2005];
int n,k;
string rs;

int idx[2005][2005];

void get(int i, int j){
    rs+=grid[i][j];
    if(i!=n-1 || j!=n-1){
        get(nxt[i][j].fi, nxt[i][j].se);
    }
}

vector<pair<int,int> > tmpv;


bool cmp(pair<int,int> & a, pair<int,int> &b){
    if(grid[a.fi][a.se]!=grid[b.fi][b.se]){
        return grid[a.fi][a.se]<grid[b.fi][b.se];
    }
    int id1 = idx[nxt[a.fi][a.se].fi][nxt[a.fi][a.se].se];
    int id2 = idx[nxt[b.fi][b.se].fi][nxt[b.fi][b.se].se];
    return id1<id2;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for(int i=0;i<n;i++){
        cin >> grid[i];
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i>0){
                val[i][j]=max(val[i][j], val[i-1][j]);
            }
            if(j>0){
                val[i][j]=max(val[i][j], val[i][j-1]);
            }
            val[i][j]+=(grid[i][j]=='a');
        }
    }
    if(2*n-1<=k || 2*n-1-val[n-1][n-1]<=k){
        for(int i=0;i<2*n-1;i++){
            cout << 'a';
        }
        return 0;
    }
    string ans="";
    for(int l = 2*(n-1)-1;l>=0;l--){
        if(l+1<k)
            break;
        bool cond=false;
        tmpv.clear();
        for(int i=0;i<=l;i++){
            int  j=l-i;
            if(j>=n || i>=n )
                continue;
            tmpv.pb({i,j});
            int nxi=-1;
            int nxj=-1;
            int nxidx = 1e9;
            if(i<n-1 && nxidx>idx[i+1][j]){
                nxidx = idx[i+1][j];
                nxi = i+1;
                nxj = j;
            }
            if(j<n-1 && nxidx>idx[i][j+1]){
                nxidx = idx[i][j+1];
                nxi = i;
                nxj = j+1;
            }
            nxt[i][j]={nxi,nxj};
            if(l+1-val[i][j]<=k){
                string tmp="";
                for(int o=0;o<l+1;o++){
                    tmp+='a';
                }
                rs="";
                get(nxi, nxj);
                tmp+=rs;
                if(ans==""){
                    ans=tmp;
                }else{
                    ans=min(ans, tmp);
                }
                cond=true;
            }
        }
        if(cond)
            break;
        sort(tmpv.begin(),tmpv.end(), cmp);
        for(int i=0;i<tmpv.size();i++){
            idx[tmpv[i].fi][tmpv[i].se]=i;
        }
    }
    if(ans==""){
        rs="";
        get(0,0);
        ans=rs;
    }
    cout << ans;
    return 0;
}
