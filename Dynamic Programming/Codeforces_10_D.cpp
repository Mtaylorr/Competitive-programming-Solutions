//https://codeforces.com/contest/10/problem/D
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 1e9 +7 ;

set<int> s;
map<int,int> code;
map<int,int> decode;
int a[N],b[N],n,m;
int dp[505][505];
int tree[1005];
int cn;

void upd(int x, int v){
    for(;x<cn;x+=(x)&-(x)){
        tree[x]=max(tree[x],v);
    }
}
int get(int x){
    int rs=0;
    for(;x;x-=(x)&(-x)){
        rs=max(rs, tree[x]);
    }
    return rs;
}


int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        s.insert(a[i]);
    }
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%d",&b[i]);
        s.insert(b[i]);
    }
    cn=1;
    for(auto u:s){
        code[u]=cn;
        decode[cn]=u;
        cn++;
    }
    for(int i=0;i<n;i++){
        a[i]=code[a[i]];
    }
    for(int i=0;i<m;i++){
        b[i]=code[b[i]];
    }
    int ans=0;
    for(int i=0;i<n;i++){
        memset(tree,0,sizeof(tree));
        for(int j=0;j<m;j++){
            for(int k=0;k<i;k++){
                if(a[k]==b[j]){
                    upd(a[k],dp[k][j]);
                }
            }
            if(a[i]==b[j]){
                int x = get(a[i]-1);
                x++;
                dp[i][j]=x;
                upd(a[i],x);
                ans=max(ans,x);
            }
        }
    }
    int last = 1e9;
    printf("%d\n",ans);
    vector<int> tmp;
    int lasti=n;
    int lastj=m;
    while(ans){
        bool cond=false;
        for(int i=0;i<lasti;i++){
            if(cond)
                break;
            for(int j=0;j<lastj;j++){
                if(cond)
                    break;
                if(a[i]==b[j] && dp[i][j]==ans && a[i]<last){
                    last=a[i];
                    ans--;
                    tmp.pb(a[i]);
                    lasti=i;
                    lastj=j;
                    cond=true;
                }
            }
        }
    }
    reverse(tmp.begin(),tmp.end());
    for(auto u:tmp){
        printf("%d ",decode[u]);
    }
    return 0;

}
