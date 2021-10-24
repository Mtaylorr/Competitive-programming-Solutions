#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 +5 ;
const int MOD = 1e9 +7;

int t,n,m;
int c;
char grid[100][100];

ll mul(ll u , ll v, ll mod=MOD){
	return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
	return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
	return ((u%mod)-(v%mod)+mod)%mod;
}

int dp[100][5][5];

int cnt[5];

int solve(int pos, int topcolor, int bottomcolor){
    if(pos>=m)
        return 1;
    int & res = dp[pos][topcolor][bottomcolor];
    if(res!=-1)
        return res;
    res=0;
    map<int,int> maa;
    if(topcolor!=0)
        maa[topcolor]++;
    if(bottomcolor!=0)
        maa[bottomcolor]++;
    if(grid[0][pos]=='#' && grid[1][pos]=='#'){
        res=solve(pos+1,0,0);
    }else if(grid[0][pos]=='#'){
        for(int i=1;i<=c;i++){
            if(maa[i]>=2)
                continue;
            res=add(res, solve(pos+1,0, i));
        }
    }else if(grid[1][pos]=='#'){
        for(int i=1;i<=c;i++){
            if(maa[i]>=2)
                continue;
            res=add(res, solve(pos+1,i, 0));
        }
    }else{
        for(int i=1;i<=c;i++){
                for(int j=1;j<=c;j++){
                    if(i==j && maa[i]<=0)
                        res=add(res, solve(pos+1,i, i));
                    else if(i!=j && maa[i]<=1 && maa[j]<=1){
                        res=add(res, solve(pos+1,i,j));
                    }
                }

        }
    }
    return res;
}

int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        memset(dp,-1, sizeof(dp));
        scanf("%d%d%d",&n,&m,&c);
        if(n!=2)
            continue;
        for(int i=0;i<n;i++){
            cin >> grid[i];
        }
        cout << solve(0,0,0) << endl;
    }
    return 0;
}
