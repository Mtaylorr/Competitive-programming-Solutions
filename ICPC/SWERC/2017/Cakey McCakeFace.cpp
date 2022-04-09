#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7 ;

map<int,int> freq;
int n,m;
int a[N],b[N];

int main()
{
    ios::sync_with_stdio(0);
   // freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    scanf("%d",&m);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<m;i++){
        scanf("%d",&b[i]);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(b[j]>=a[i]){
                freq[b[j]-a[i]]++;
            }
        }
    }
    int mx=0;
    int ans=0;
    for(auto u:freq){
        if(mx<u.se){
            mx=u.se;
            ans=u.fi;
        }
    }
    cout << ans;

    return 0;

}
