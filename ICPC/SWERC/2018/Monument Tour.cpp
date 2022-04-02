#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7 ;

int X, Y,n;
vector<int> pos[N];
int mn[N], mx[N];

int main()
{
    //freopen("input.txt", "r",stdin);
    scanf("%d%d",&X,&Y);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int x,y;
        cin >> x >> y;
        pos[x].pb(y);
    }
    ll cur=0;
    ll curmn=0;
    ll curmx=0;
    for(int i=0;i<X;i++){
        if(pos[i].size()){
            sort(pos[i].begin(),pos[i].end());
            mn[pos[i][0]]++;
            mx[pos[i].back()]++;
            curmx++;
            cur+=pos[i].back();
        }
    }
    ll ans=1e18;
    for(int i=0;i<Y;i++){
        ans=min(ans, cur);
        curmn+=mn[i];
        curmx-=mx[i];
        cur+=curmn;
        cur-=curmx;
    }
    ans = ans*2 + X-1;
    cout << ans << endl;
    return 0;

}
