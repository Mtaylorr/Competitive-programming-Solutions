#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353  ;


int dp[N];
int n,q;
char s1[N],s2[N];

int l,r;

int main(){
   // freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&q);
    scanf("%s",s1);
    scanf("%s",s2);
    for(int i=1;i<n;i++){
        int mx1 = max((s1[i]-'a'), (s2[i]-'a'));
        int mx2  = max((s1[i-1]-'a'),s2[i-1]-'a');
        int mn1 = min(s1[i]-'a', s2[i]-'a');
        int mn2  = min(s1[i-1]-'a',s2[i-1]-'a');
        if(mx1>=mx2 && mn1>=mn2){
            dp[i]=1;
        }
    }
    for(int i=1;i<n;i++){
        dp[i]+=dp[i-1];
    }
    while(q--){
        scanf("%d%d",&l,&r);
        if(l==r){
            puts("YES");
            continue;
        }
        r--;
        l--;
        if(dp[r]-dp[l] == r-l){
            puts("YES");
        }else{
            puts("NO");
        }
    }

    return 0;
}
