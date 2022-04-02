#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5;
const int MOD = 1e9 + 7 ;

int n,k,x;
int on[N];

int main()
{
    //freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        on[i]=1;
    }
    int ans=0;
    int nb=n;
    scanf("%d",&k);
    while(k--){
        scanf("%d",&x);
        for(int j=x;j<=n;j+=x){
            nb-=on[j];
            on[j]=1-on[j];
            nb+=on[j];
        }
        ans=max(ans, n-nb);
    }
    cout << ans << endl;
    return 0;

}
