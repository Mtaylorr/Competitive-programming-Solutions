//32%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


#define neig(u,v,e) for(int e=head[u],v;(e!=-1) && (v=to[e], 1) ; e=nxt[e])

const int N = 1e6 +5 ;


int n;
int a[N];
int grid[55][55];
int main(){
    //freopen("input.txt", "r", stdin);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    bool cond=true;
    for(int i=0;i<n;i++){
        if(a[i]>i+1)
            cond=false;
    }
    if(cond){
        for(int i=0;i<n;i++){
            for(int j=i;j>=i-a[i]+1;j--){
                grid[i][j]=1;
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout << grid[i][j] <<" ";
            }
            cout << endl;
        }

        return 0;
    }

    cond=true;
    for(int i=0;i<n;i++){
        if(a[i]>n-i)
            cond=false;
    }
    if(cond){
        for(int i=0;i<n;i++){
            for(int j=i;j<=i+a[i]-1;j++){
                grid[i][j]=1;
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout << grid[i][j] <<" ";
            }
            cout << endl;
        }
        return 0;
    }
    cout << -1;


    return 0;
}
