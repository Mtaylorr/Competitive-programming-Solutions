//https://codeforces.com/contest/55/problem/D
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 1e9 +7 ;

int t;
ll l,r;
string s;
int n;
ll dp[20][2522][50][2];
int mask;
int prod[1024];
int code[2550],decode[2550];
ll res[1024];
ll ans[1024];
int nxt[50][10];
int cn;

int lcm(int x, int y){
    if(y==0)
        y=1;
    if(x==0)
        x=1;
    return (x)*(y/__gcd(x,y));
}


int bitcount(int x){
    int rs=0;
    while(x){
        rs+=x%2;
        x/=2;
    }
    return rs;
}

void calcprod(int mask){
    prod[mask]=1;
    for(int j=1;j<10;j++){
        if((1<<j)&mask){
            prod[mask]=lcm(prod[mask],j);
        }
    }
}


ll calcdp(int p, int m,int lc, int iseq){
    if(p>=n){

        return m%decode[lc]==0;
    }
    if(dp[p][m][lc][iseq]!=-1)
        return dp[p][m][lc][iseq];
    ll rs = 0;
    int ub = 9;
    if(iseq){
        ub=s[p]-'0';
    }
    for(int j=0;j<=ub;j++){
        rs+=calcdp(p+1,(m*10+j)%2520,code[lcm(decode[lc],j)],iseq*(j==ub));
    }
    return dp[p][m][lc][iseq]=rs;
}

ll solve(ll x){
    s=to_string(x);
    n = s.size();
    memset(dp,0, sizeof(dp));
    dp[0][0][0][1]=1;
    ll ans=0;
    for(int i=1;i<=n;i++){
        int p = i&1;
        for(int lc=0;lc<cn;lc++){
            for(int m=0;m<2520;m++){
                for(int o=0;o<2;o++){
                    dp[p][m][lc][o]=0;
                }
            }
        }
        for(int lc=0;lc<cn;lc++){
            for(int m=0;m<2520;m++){
                if(!dp[p^1][m][lc][0] && !dp[p^1][m][lc][1])
                    continue;
                for(int o=0;o<2;o++){
                    if(o==0){
                        for(int j=0;j<=9;j++){
                            dp[p][(m*10+j)%2520][nxt[lc][j]][0]+=dp[p^1][m][lc][0];
                        }
                        int ub = s[i-1]-'0';
                        for(int j=0;j<ub;j++){
                            dp[p][(m*10+j)%2520][nxt[lc][j]][0]+=dp[p^1][m][lc][1];
                        }
                    }else{
                        int ub = s[i-1]-'0';
                        dp[p][(m*10+ub)%2520][nxt[lc][ub]][1]+=dp[p^1][m][lc][1];
                    }
                }
            }
        }
    }
    for(int lc=0;lc<cn;lc++){
        for(int m=0;m<2520;m++){
            if(m%decode[lc]!=0)
                continue;
            for(int o=0;o<2;o++){
                ans+=dp[n&1][m][lc][o];
            }
        }
    }
    return ans;
}


int main()
{
    freopen("input.txt", "r",stdin);
    for(int i=0;i<(1<<10);i++){
        calcprod(i);
    }
    int x=1;
    for(int i=0;i<4;i++){
        int y=1;
        for(int j=0;j<3;j++){

            int z=1;
            for(int o=0;o<2;o++){

                int w=1;
                for(int k=0;k<2;k++){

                    code[x*y*w*z]=cn;
                    decode[cn]=x*y*z*w;
                    cn++;
                    w*=7;
                }
                z*=5;
            }
            y*=3;
        }
        x*=2;
    }
    for(int i=0;i<cn;i++){
        for(int j=0;j<10;j++){
            nxt[i][j]= code[lcm(decode[i],j)];
        }
    }
    scanf("%d",&t);
    while(t--){
        scanf("%lld %lld",&l,&r);
        ll ans= solve(r);
        ans-=solve(l-1);
        printf("%lld\n",ans);
    }
    return 0;

}
