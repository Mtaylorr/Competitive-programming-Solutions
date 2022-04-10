#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e6 + 5, E = 1e6 +5;
const int MOD = 1e9  ;

int m;
ll n;
vector<vector<int> > T;
int M, newMask, oldMask;

int dp[10];
int po[10];

int mul(int u , int v, int mod=MOD){
    return ((u%mod)*1ll*(v%mod))%mod;
}
int add(int u, int v, int mod=MOD){
    return ((u%mod)+0ll+(v%mod)+mod)%mod;
}

int sub(int u, int v , int mod=MOD){
    return ((u%mod)+0ll-(v%mod)+mod)%mod;
}

int calc(int p){
    if(p>=m)
        return 1;
    if(dp[p]!=-1)
        return dp[p];
    if(!(newMask&po[p]))
        return dp[p]=calc(p+1);
    int rs  = 0 ;
    if(!(oldMask&po[p])){
        rs=add(rs, calc(p+1));
    }
    if((p<m-1) && (newMask&po[p+1])){
        rs=add(rs, calc(p+2));
    }
    return dp[p]=rs;
}

vector<vector<int> > tmp;

void matM(vector<vector<int> > &a , vector<vector<int> > &b){
    tmp.resize(M);
    for(int i=0;i<M;i++){
        tmp[i].assign(M,0);
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            for(int k=0;k<M;k++){
                tmp[i][j]=add(tmp[i][j], mul(a[i][k], b[k][j]));
            }
        }
    }
}

void cp(vector<vector<int> >  &a){
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            a[i][j]=tmp[i][j];
        }
    }

}

vector<vector<int> >  powM(vector<vector<int> > & a, ll n){
    vector<vector<int> > rs;
    rs.resize(M);
    for(int i=0;i<M;i++){
        rs[i].assign(M,0);
        rs[i][i]=1;
    }
    while(n){
        if(n%2){
            matM(rs, T);
            cp(rs);
        }
        n/=2;
        matM(a,a);
        cp(a);
    }
    return rs;

}



int main()
{
    //ios::sync_with_stdio(0);
    freopen("input.txt", "r",stdin);
    po[0]=1;
    for(int i=1;i<10;i++){
        po[i]=2*po[i-1];
    }
    scanf("%d",&m);
    scanf("%lld",&n);
    M = 1<<m;
    T.resize(M);
    for(int i=0;i<M;i++){
        T[i].assign(M,0);
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            newMask = i;
            oldMask = j;
            memset(dp,-1, sizeof(dp));
            T[i][j]=calc(0);
        }
    }
    vector<vector<int> > rs = powM(T,n);

    int ans=0;
    for(int i=0;i<M;i++){
        ans=add(ans, rs[i][M-1]);
    }
    printf("%d\n",ans);


    return 0;

}
