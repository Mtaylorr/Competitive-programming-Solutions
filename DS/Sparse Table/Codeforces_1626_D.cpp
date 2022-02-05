//https://codeforces.com/problemset/problem/1626/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 +5 ;
const int MOD = 1e9 + 7 ;

int t,n,a[N];
int sum[N];
int nxt[N][20];
int spt[N][20];
int lg2[N];

int getp(int x){
    int p=1;
    while(p<x){
        p*=2;
    }
    return p-x;
}

int get(int l, int r){
    int lg = lg2[r-l+1];
    return min(spt[l][lg], spt[r-(1<<lg)+1][lg]);
}



int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
            sum[a[i]]++;
        }
        for(int j=0;j<20;j++){
            int l=0;
            int cur=0;
            int cursz = (1<<j);
            for(int r=0;r<=n;r++){
                cur+=sum[r];
                while(cur>cursz){
                    cur-=sum[l++];
                }
                nxt[r][j]=max(l-1,0);
            }
        }
        lg2[1]=0;
        for(int i=0;i<=n;i++){
            sum[i]+=sum[i-1];
            spt[i][0]=sum[i]+getp(sum[i]);
            if(i>=2)
                lg2[i]=1+lg2[i/2];
        }
        for(int j=1;j<20;j++){
            for(int i=0;i+(1<<j)<=n+1;i++){
                spt[i][j]=min(spt[i][j-1],spt[i+(1<<(j-1))][j-1]);
            }
        }

        int ans=1e9;
        for(int i=1;i<=n;i++){
            int k = 1;
            int res=1e9;
            int lg=0;
            while(k<2*sum[i]){
                if(k>=sum[i]-sum[i-1])
                    res=min(res, k-sum[i]+get(nxt[i][lg],i-1));
                k*=2;
                lg++;
            }
            res+=getp(n-sum[i]);
            ans=min(ans,res);
        }
        for(int i=0;i<=n;i++){
            sum[i]=0;
        }
        cout << ans << endl;

    }
    return 0;
}
