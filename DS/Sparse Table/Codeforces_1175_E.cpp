//https://codeforces.com/contest/1175/problem/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 5e5 + 5, M=1000 +5,E = 1e6 +5 ;
const int MOD = 1e9 + 7   ;
const double eps = 1e-7;

int spt[21][N];
int l,r;
int n,m;
int A = 5e5;
int po[30];

int calc(int p,int x){
    for(int i=20;i>=0;i--){
        if(x>=po[i]){
            p=spt[i][p];
            x-=po[i];
        }
    }
    return p;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    po[0]=1;
    for(int i=1;i<=20;i++){
        po[i]=2*po[i-1];
    }
    for(int i=0;i<n;i++){
        cin >> l >> r;
        spt[0][l]=max(spt[0][l],r);
    }
    for(int i=1;i<=A;i++){
        spt[0][i]=max(spt[0][i],i);
        spt[0][i]=max(spt[0][i],spt[0][i-1]);
    }
    for(int j=1;j<=20;j++){
        int cur  = (1<<j);
        for(int i=0;i<=A;i++){
            spt[j][i]=spt[j-1][spt[j-1][i]];
        }
    }
    while(m--){
        cin >> l >> r;
        int lf = 0;
        int rg = n+2;
        while(lf<rg){
            int md = (lf+rg)/2;
            int mxp= calc(l,md);
            if(mxp>=r){
                rg=md;
            }else{
                lf=md+1;
            }
        }
        if(lf>n){
            cout << -1 << "\n";
        }else{
            cout << lf << "\n";
        }
    }

    return 0;
}
