#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E= 2e5+5;
const int MOD = 998244353 ;

int t;
int n,m;
int mxw, mxr;
int r,w;
int main() {
    ios::sync_with_stdio(0);
    //freopen("input.txt", "r", stdin);
    cin >> t;
    while(t--){
        cin >> n >> m;
        mxw=0;
        mxr=0;
        for(int i=0;i<m;i++){
            cin >> r >> w;
            mxr=max(mxr, r);
            mxw=max(mxw, w);
        }
        if(mxw+mxr>n){
            cout << "IMPOSSIBLE\n";
        }else{
            for(int i=0;i<mxw;i++){
                cout << "W";
            }
            for(int i=0;i<n-mxw;i++){
                cout << "R" ;
            }
            cout << "\n";
        }
    }


    return 0;

}
