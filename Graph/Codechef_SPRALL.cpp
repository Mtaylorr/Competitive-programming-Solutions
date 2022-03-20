//https://www.codechef.com/problems/SPRALL
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 +7 ;

int n,q,t,u,v,c,d;
int deg[N];
ll sum[N];

int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d",&t);
    sum[0]=0;
    for(int i=1;i<=100000;i++){
        sum[i]=sum[i-1]+i;
    }
    while(t--){
        scanf("%d%d",&n,&q);
        for(int i=0;i<n;i++){
            deg[i]=0;
        }
        for(int i=0;i<n-1;i++){
            scanf("%d%d",&u,&v);
            --u;
            --v;
            deg[u]++;
            deg[v]++;
        }
        ll ans=0;
        for(int i=0;i<n;i++){
            ans+=sum[deg[i]]-1;
        }
        printf("%lld\n",ans+1);
        while(q--){
            scanf("%d%d%d%d",&u,&v,&c,&d);
            --u;
            --v;
            --c;
            --d;
            ans-=(sum[deg[u]]-1);
            ans-=(sum[deg[v]]-1);
            ans-=(sum[deg[c]]-1);
            ans-=(sum[deg[d]]-1);
            deg[u]--,deg[v]--;
            deg[c]++,deg[d]++;
            ans+=(sum[deg[u]]-1);
            ans+=(sum[deg[v]]-1);
            ans+=(sum[deg[c]]-1);
            ans+=(sum[deg[d]]-1);
            printf("%lld\n",ans+1);
            ans-=(sum[deg[u]]-1);
            ans-=(sum[deg[v]]-1);
            ans-=(sum[deg[c]]-1);
            ans-=(sum[deg[d]]-1);
            deg[u]++,deg[v]++;
            deg[c]--,deg[d]--;
            ans+=(sum[deg[u]]-1);
            ans+=(sum[deg[v]]-1);
            ans+=(sum[deg[c]]-1);
            ans+=(sum[deg[d]]-1);
        }

    }

    return 0;

}
