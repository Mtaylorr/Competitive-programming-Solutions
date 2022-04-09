#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e6 + 5;
const int MOD = 1e9 + 7 ;

int n;
int W ,L;
int w,l;
ll area=0;

int main()
{
    ios::sync_with_stdio(0);
    //freopen("input.txt", "r",stdin);
    scanf("%d",&W);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d%d",&w,&l);
        area+=w*l;
    }
    cout << area/W ;

    return 0;

}
