#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 10567201 ;

int n;
double x[N], y[N];
int p;


int main()
{
    //freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    double ans=0;
    for(int i=0;i<n;i++){
        scanf("%d",&p);
        for(int j=0;j<p;j++){
            scanf("%lf %lf",&x[j],&y[j]);
        }
        double rs=0;
        for(int j=0;j<p;j++){
            rs+=(x[j]*y[(j+1)%p] - x[(j+1)%p]*y[j]);
        }
        rs=abs(rs);
        rs/=2.0;

        ans+=rs;
    }
    ll y = (long long)floor(ans);
    cout << y << endl;
    return 0;
}
