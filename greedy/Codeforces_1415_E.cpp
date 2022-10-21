//https://codeforces.com/problemset/problem/1415/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 5e5 + 5, M = 1000 + 5, E = 1e6 + 5;
const int MOD =998244353 ;
const double eps = 1e-7;

int n,k;
ll c[N];
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    ll sump=0;
    ll ans=-1e18;
    ll sum=0;
    for(int i=0;i<n;i++){
        cin >> c[i];
    }
    sort(c,c+n);
    reverse(c,c+n);
    for(int i=0;i<n;i++){
        sump+=c[i];
        sum+=c[i]*(n-i-1);
    }

    ans=sum;
    int cur=0;

    for(int b=n-1;b>=0;b-=(k+1)){
        for(int i=b;i>=max(0,b-(k+1)+1);i--){
            sump-=c[i];
            if(i!=b){
                sum-=sump;
                sum-=(c[i]*(cur+1));
                sum+=c[i]*cur;
            }
            ans=max(ans, sum);
        }
        cur++;
    }
    cout << ans ;


    return 0;

}
