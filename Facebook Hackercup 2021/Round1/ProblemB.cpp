#include <bits/stdc++.h>

using namespace std;
const int N = 2e6+5;
const int MOD = 1e9 + 7;

#define fi first
#define se second
#define pb push_back

typedef long long ll;

int t,n,m,a,b;

int main(){
    freopen("traffic_control_input.txt", "r", stdin);
    freopen("output.txt","w", stdout);
    scanf("%d",&t);
    int tt=0;
    while(t--){
        ++tt;
        scanf("%d%d%d%d",&n,&m,&a,&b);
        if(a<n+m-1 || b<n+m-1){
            printf("Case #%d: Impossible\n",tt);
        }else{
            if(n>=2 || m>=2){
                printf("Case #%d: Possible\n",tt);
                printf("%d ",a-(n+m-2));
                for(int i=0;i<m-2;i++){
                    printf("%d ",1);
                }
                printf("%d\n",b-(n+m-2));
                for(int i=0;i<n-1;i++){
                    for(int i=0;i<m;i++){
                        printf("%d ",1);
                    }
                    puts("");
                }
            }
        }

    }
    return 0;
}
