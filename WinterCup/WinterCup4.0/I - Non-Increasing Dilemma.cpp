#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6+5;
const int MOD = 998244353  ;

int a[N];
int n;
int t;

int main(){
    //freopen("input.txt", "r",stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
        }
        int ans=0;
        int sum=0;
        for(int i=1;i<n;i++){
            if(a[i]+sum>a[i-1]){
                ans++;
                sum=a[i];
            }else{
                sum=0;
            }
        }
       printf("%d\n",ans);
    }
    return 0;
}
