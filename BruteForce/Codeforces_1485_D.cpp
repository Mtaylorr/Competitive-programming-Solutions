//https://codeforces.com/contest/1485/problem/D

#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 + 7 ;

int n,m;
int a[505][505];
int ans[20];
int lc  = 720720;

int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=16;i++){
        for(int k=1;lc-k*k*k*k>=1;k++){
            int z = lc-k*k*k*k;
            if(z%i==0){
                ans[i]=z;
            }
        }
        for(int k=1;lc+k*k*k*k<=1e6;k++){
            int z = lc+k*k*k*k;
            if(z%i==0){
                ans[i]=z;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if((i+j)%2==0){
                cout << lc << " ";
            }else{
                cout << ans[a[i][j]] << " ";
            }
        }
        cout << endl;
    }


    return 0;
}
