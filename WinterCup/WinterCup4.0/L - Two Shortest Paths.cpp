#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353  ;

int t,n,m;
ll cum[N];

int main(){
    //freopen("input.txt", "r",stdin);
    scanf("%d",&t);
    cum[0]=0;
    for(int i=1;i<=1e5;i++){
        cum[i]+=cum[i-1]+i;
    }
    while(t--){
        scanf("%d%d",&n,&m);
        ll ans;
        if(n>=m){
            ans =cum[n+2*(m-1)]+cum[n];
        }else{
            ans=cum[m+2*(n-1)]+cum[m];
        }
        cout << ans << endl;
    }

    return 0;
}
