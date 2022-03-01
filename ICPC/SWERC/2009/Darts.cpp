#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5;
const int MOD = 1e9 + 7 ;

double dp[505][505][2];
double dp2[22][505][2][100];
int n;
vector<int> wheel={1,18,4,13,6,10,15,2,17,3,19,7,16,8,11,14,9,12,5,20};


double solve(int i, int j, int p, int round){
    if(i==0)
        return 1.0;
    if(j==0)
        return 0;
    if(round==100)
        return 0;
    if(i<=20){
        if(dp2[i][j][p][round]>-0.5)
            return dp2[i][j][p][round];
    }
    else{
        if(dp[i][j][p]>-0.5)
            return dp[i][j][p];
    }
    double ans = 0.0;
    if(p==0){
        for(int k=0;k<20;k++){
            if(wheel[k]<=i){
                if(i<=20){
                    ans+=(1.0-solve(j, i-wheel[k],1-p,round+1))/(20.0);
                }else{
                    ans+=(1.0-solve(j, i-wheel[k],1-p,round))/(20.0);
                }
            }else{
                if(i<=20){
                    ans+=(1.0-solve(j,i,1-p,round+1))/(20.0);
                }else{
                    ans+=(1.0-solve(j,i,1-p,round))/(20.0);
                }

            }
        }
    }else{
        vector<double> cur(20,0.0);
        for(int k=0;k<20;k++){
            if(wheel[k]<=i){
                if(i<=20){
                    cur[k]=(1.0-solve(j,i-wheel[k],1-p,round+1))/3.0;
                }else{
                    cur[k]=(1.0-solve(j,i-wheel[k],1-p,round))/3.0;
                }

            }else{
                if(i<=20){
                    cur[k]=(1.0-solve(j,i,1-p,round+1))/3.0;
                }else{
                    cur[k]=(1.0-solve(j,i,1-p,round))/3.0;
                }

            }

            for(int i=0;i<20;i++){
                double res=0;
                for(int j=0;j<3;j++){
                    res+=(cur[(i+j)%20]);
                }
                ans=max(ans, res);
            }
        }
    }
    if(i<=20){
        return dp2[i][j][p][round]=ans;
    }
    return dp[i][j][p]=ans;
}

int main()
{
    //freopen("input.txt", "r",stdin);
    memset(dp, -1, sizeof(dp));
    memset(dp2, -1, sizeof(dp2));
    while(1){
        scanf("%d",&n);
        if(n==0)
            break;
        long double ans1 =  solve(n,n,0,0);
        long double ans2 = solve(n,n,1,0);
        cout << fixed << setprecision(10) << ans1 << " "<< ans2 << endl;

    }
    return 0;
}
