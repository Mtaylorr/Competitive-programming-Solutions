#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e6+5;

ll x[3], y[3];
int t;
int main(){
    freopen("input.txt", "r", stdin);
    //freopen("rabbits.in", "r", stdin);
    scanf("%d",&t);
    while(t--){
        for(int i=0;i<3;i++){
            scanf("%lld %lld",&x[i],&y[i]);
        }
        if(x[0]==x[1] && y[0]==y[1]){
            puts("Possible");
            continue;
        }

        if(x[0]==x[2] && y[0]==y[2]){
            puts("Possible");
            continue;
        }

        if(x[2]==x[1] && y[2]==y[1]){
            puts("Possible");
            continue;
        }
        for(int i=1;i<3;i++){
            x[i]-=x[0];
            y[i]-=y[0];
        }
        ll det = x[1]*y[2]-x[2]*y[1];
        if(det==0)
            puts("Impossible");
        else
            puts("Possible");
    }
    return 0;
}
