//https://codeforces.com/problemset/problem/1707/B

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 2*(2e5 + 5);
const int MOD = 1e9 + 7;

int n;
int a[N];
int b[N];
int t;
int nbz=0;
int v[N];

void process(){
    int p=0;
    int nexnbz = max(0,nbz-1);
    for(int i=1;i<n;i++){
        int x =b[i]-b[i-1];
        if(x==0){
            nexnbz++;
        }else{
            v[p++]=x;
        }
    }
    if(nbz){
        v[p++]=b[0];
    }
    sort(v,v+p);
    n=p;
    for(int i=0;i<n;i++){
        b[i]=v[i];
    }
    nbz=nexnbz;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n;
        nbz=0;
        int p=0;
        for(int i=0;i<n;i++){
            cin >> a[i];
            nbz+=a[i]==0;
            if(a[i]!=0){
                b[p++]=a[i];
            }
        }
        n=p;
        while(n>1){
            process();
        }
        if(n==1)
            cout << b[n-1] << "\n";
        else{
            cout << 0 << "\n";
        }
    }

    return 0;

}
