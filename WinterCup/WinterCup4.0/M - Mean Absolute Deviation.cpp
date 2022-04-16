#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353  ;

int n,m;
int q;
int t;
ll x[N];
ll a[N];
vector<double> sqt[N];
vector<double> cumsum[N];
int sz[N];
int l,r;


double get(int p , double mu){
    if(sqt[p][0]>=mu){
        return (cumsum[p][sz[p]]-mu*sz[p]);
    }
    if(sqt[p][sz[p]-1]<=mu){
        return mu*sz[p]-cumsum[p][sz[p]];
    }
    int l=0;
    int r=sz[p]-1;
    while(l<r){
        int md = (l+r)/2;
        if(sqt[p][md]>=mu){
            r=md;
        }else{
            l=md+1;
        }
    }
    double x1 = mu*(l)- cumsum[p][l];
    double x2 = cumsum[p][sz[p]]-cumsum[p][l] -mu*(sz[p]-(l));
    return x1+x2;
}



int main(){
   // freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&q);
    int B = sqrt(n);
    int le=0;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        x[i]=a[i];
        sqt[i/B].pb(a[i]);
        le=max(le,i/B);
        sz[i/B]++;
        x[i]+=x[i-1];
    }
    for(int i=0;i<=le;i++){
        sort(sqt[i].begin(),sqt[i].end());
        cumsum[i].pb(0);
        for(int j=0;j<sqt[i].size();j++){
            cumsum[i].pb(cumsum[i][j]+sqt[i][j]);
        }
    }
    while(q--){
        scanf("%d%d" ,&l,&r);
        double mu = x[r]-x[l-1];
        double  n = r-l+1;
        mu = mu/n;
        double ans=0;
        int qs=l/B;
        int qe= r/B;
        if(qs==qe){
            for(int i=l;i<=r;i++){
                ans+=abs(mu-1.0*a[i]);
            }
            ans/=n;
        }else{
            qs++;
            for(int i=l;i<qs*B;i++){
                ans+=abs(mu-1.0*a[i]);
            }
            for(int i=qe*B;i<=r;i++){
                ans+=abs(mu-1.0*a[i]);
            }
            for(int i=qs;i<qe;i++){
                ans+=get(i,mu);
            }
            ans/=n;
        }
        cout << fixed  << setprecision(6) << ans << endl;

    }


    return 0;
}
