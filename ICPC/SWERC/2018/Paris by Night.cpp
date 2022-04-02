#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7 ;

ll x[N],y[N],g[N];
ll sum=0;
int curi,n;
vector<int> tmp;
ll tmpg[N];
ll x_a,x_b,y_a,y_b;


bool cmp(int a, int b){
    x_a = x[a]-x[curi];
    x_b = x[b]-x[curi];
    y_a = y[a]-y[curi];
    y_b = y[b]-y[curi];
    if(y_a*y_b<0){
        return y_a>0;
    }
    return x_a*y_b-x_b*y_a>0;
}

ll calc(int a, int b){
    x_a = x[tmp[a]]-x[curi];
    x_b = x[tmp[b]]-x[curi];
    y_a = y[tmp[a]]-y[curi];
    y_b = y[tmp[b]]-y[curi];
    return x_a*y_b-x_b*y_a;
}

int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%lld%lld%lld",&x[i],&y[i],&g[i]);
        sum+=g[i];
    }
    ll ans=1e18;
    for(int i=0;i<n;i++){
        curi=i;
        tmp.clear();
        for(int j=0;j<n;j++){
            if(j==i)
                continue;
            tmp.pb(j);
        }

        sort(tmp.begin(),tmp.end(),cmp);
        for(int j=0;j<tmp.size();j++){
            tmpg[j+1]=g[tmp[j]];
        }
        for(int j=1;j<=tmp.size();j++){
            tmpg[j]+=tmpg[j-1];
        }
        int l=0;
        int r=0;
        for(int j=0;j<tmp.size();j++){
            if(y[tmp[j]]<y[i]){
                continue;
            }
            while(l< tmp.size() && calc(j,l)<0){
                l++;
            }
            while(r<tmp.size() && calc(j,r)>=0)
                r++;
            ll up = tmpg[r]-tmpg[l+1];
            ll down = sum-g[i]-up-g[tmp[j]];
            ans=min(ans, abs(down-up));
        }
    }
    cout << ans << endl;

    return 0;

}
