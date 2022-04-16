#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353  ;

int n;
int a[N];

map<int,int> freq;

int dp[N];

int main(){
    //freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    dp[0]=1;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++){
        int mx = 0;
        int distincts = 0;
        freq.clear();
        for(int j=i;j>=1;j--){
            freq[a[j]]++;
            if(freq[a[j]]>=2)
                break;
            distincts+=(freq[a[j]]==1);
            mx = max(mx, a[j]);
            if(mx==distincts){
                dp[i]=max(dp[i],dp[j-1]);
            }
        }
    }
    if(dp[n]){
        cout << "YES";
    }else{
        cout << "NO";
    }
    return 0;
}
