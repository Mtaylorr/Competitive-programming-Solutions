#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 1e9 + 7 ;


int n;
double x[N], y[N];

double calc(double a){
    double rs=0;
    for(int i=0;i<n;i++){
        rs = max(rs, (a-x[i])*(a-x[i])+y[i]*y[i]);
    }
    return rs;
}


int main(){
    //freopen("input.txt", "r",stdin);
    while(1){
        scanf("%d",&n);
        if(n==0)
            break;
        for(int i=0;i<n;i++){
            scanf("%lf%lf",&x[i],&y[i]);
        }
        double l = -2e5,r=2e5;
        for(int i=0;i<100;i++){
            double x1 = l+(r-l)/3;
            double x2 = r-(r-l)/3;
            double v1 = calc(x1);
            double v2 = calc(x2);
            if(v1>v2){
                l = x1;
            }else{
                r=x2;
            }
        }
        printf("%.6lf %.6f\n",l,sqrt(calc(l)));
    }
    return 0;
}
