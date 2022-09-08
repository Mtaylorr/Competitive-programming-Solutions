//https://codeforces.com/contest/708/problem/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5, E = 1 << 17;
const int MOD =  998244353 ;

ll a[2][2];
ll nb[2];

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            cin >> a[i][j];
        }
    }
    for(int i=0;i<2;i++){
        while(nb[i]*(nb[i]-1)/2<a[i][i]){
            nb[i]++;
        }
        if(nb[i]*(nb[i]-1)/2!=a[i][i]){
            cout << "Impossible";
            return 0;
        }
    }
    if(a[0][0]==0 && a[0][1]==0 && a[1][0]==0){
        if(nb[1]==0){
            nb[1]++;
        }
        for(int j=0;j<nb[1];j++){
            cout << 1;
        }
        return 0;
    }
    if(a[1][1]==0 && a[1][0]==0 && a[0][1]==0){
        if(nb[0]==0){
            nb[0]++;
        }
        for(int j=0;j<nb[0];j++){
            cout << 0;
        }
        return 0;
    }
    if(nb[0]==0){
        nb[0]++;
    }
    if(nb[1]==0){
        nb[1]++;
    }
    if(a[1][0]+a[0][1]!=nb[0]*nb[1]){
        cout << "Impossible";
        return 0;
    }
    int sz = nb[0]+nb[1];
    string s="";
    for(int i=0;i<sz;i++){
        int x = nb[0]-1;
        int y = a[0][1]-nb[1];
        if(x*nb[1]==y+a[1][0] && y>=0 && x>=0){
            nb[0]--;
            s+='0';
            a[0][1]-=nb[1];
        }else{
            nb[1]--;
            s+='1';
            a[1][0]-=nb[0];
        }
    }
    cout << s;
    return 0;
}
