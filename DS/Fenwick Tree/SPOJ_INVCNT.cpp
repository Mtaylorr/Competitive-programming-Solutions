//https://www.spoj.com/problems/INVCNT/en/
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 2e5 + 2 ;
const int M = 1e7 + 2;
 
typedef long long ll;
 
ll tree[M];
 
void upd(int x, int v){
    for(;x<=1e7;x+=(x)&(-x))
        tree[x]+=v;
}
 
ll getprefix(int x){
    ll res=0;
    for(;x;x-=(x)&(-x))
        res+=tree[x];
    return res;
}
 
ll getrange(int l, int r){
    return getprefix(r)-getprefix(l-1);
}
 
int t;
int n, a[N];
 
int main()
{
    freopen("in.txt","r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        long long ans=0;
        for(int i=n-1;i>=0;i--){
            ans+=getprefix(a[i]-1);
            upd(a[i],1);
        }
        printf("%lld\n",ans);
        for(int i=0;i<n;i++)
            upd(a[i],-1);
 
    }
    return 0;
}
