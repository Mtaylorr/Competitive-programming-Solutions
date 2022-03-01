#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5;
const int MOD = 1e9 + 7 ;

double x,y;
int n;
double x1[N],x2[N], yi[N];
double dp[2][1005];
double eps = 1e-7;

void init(){
    for(int i=0;i<2;i++){
        for(int j=0;j<=n+2;j++){
            dp[i][j]=-1;
        }
    }
}

double solve(int i=0, int p=0){
    if(i>=n)
        return 0;
    if(dp[p][i]>-0.5)
        return dp[p][i];
    double x = x1[i];
    double y = yi[i];
    if(p==1){
        x = x2[i];
    }
    double mx = 1e18;
    double mn = -1e18;
    double ans=1e18;
    for(int j=i+1;j<=n;j++){
        double curmx = (x2[j]-x)/(y-yi[j]);
        double curmn = (x1[j]-x)/(y-yi[j]);


        if(mx>=curmx-eps && mn<=curmx+eps){
            double d = sqrt((x2[j]-x)*(x2[j]-x) + (y-yi[j])*(y-yi[j]));
            ans=min(ans,d+solve(j,1));
        }
        if(mx>=curmn-eps && mn<=curmn+eps){
            double d = sqrt((x1[j]-x)*(x1[j]-x) + (y-yi[j])*(y-yi[j]));
            ans=min(ans,d+solve(j,0));
        }
        mn=max(mn,curmn);
        mx=min(mx, curmx);
        if(mn>mx)
            break;
        if(j==n){
            if(mx<0){
                double ny = yi[n];
                double nx = x + mx * (y-ny);
                ans=min(ans,sqrt((x-nx)*(x-nx) + (y-ny)*(y-ny)));
            }else if(mn>0){
                double ny = yi[n];
                double nx = x + mn * (y-ny);
                ans=min(ans,sqrt((x-nx)*(x-nx) + (y-ny)*(y-ny)));
            }else{
                ans=min(ans,(y-yi[j]));
            }

        }
    }
    dp[p][i]=ans;
    return ans;

}


int main()
{
    //freopen("input.txt", "r",stdin);
    while(1){
        scanf("%d",&n);
        if(n==0)
            break;
        init();
        scanf("%lf%lf",&x1[0],&yi[0]);
        x2[0]=x1[0];
        for(int i=1;i<=n;i++){
            scanf("%lf%lf%lf",&yi[i],&x1[i],&x2[i]);
        }
        double ans=solve();
        cout << fixed << setprecision(7) <<  ans << endl;
    }
    return 0;
}
