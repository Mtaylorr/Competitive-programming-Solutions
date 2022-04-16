#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6+5;
const int MOD = 998244353  ;

int n;
char s[N];
int t;
int freq[20];

int main(){
    //freopen("input.txt", "r",stdin);
    scanf("%d",&t);
    while(t--){
        memset(freq, 0, sizeof(freq));
        scanf("%d",&n);
        scanf("%s",s);
        int rs=0;
        ll ans=0;
        int cur=1;
        freq[0]++;
        for(int i=n-1;i>=0;i--){
            rs += cur*(s[i]-'0');
            rs%=11;
            cur*=10;
            cur%=11;
            ans+=freq[rs];
            freq[rs]++;
        }
        printf("%lld\n",ans);
    }

    return 0;
}
