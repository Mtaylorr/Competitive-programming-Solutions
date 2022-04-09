#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7 ;

int n;
int a[N];
int b[N];
ll bs[3];
ll ans[3];


int main()
{
    ios::sync_with_stdio(0);
    //freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&b[i]);
        bs[i%3]+=b[i];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
            ans[(i+j)%3]+=bs[j]*a[i];
        }
    }
    for(int i=1;i<=3;i++){
        cout << ans[(i)%3] << " ";
    }
    return 0;

}
