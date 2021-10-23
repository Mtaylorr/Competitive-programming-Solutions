//https://csacademy.com/ieeextreme-practice/task/crafting-wooden-tables/

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e3+5;

ll c,n,p,w;

bool ok(ll u){
    return (w-c*u+p-1)/p<=n-u;
}

int main(){
    freopen("input.txt", "r", stdin);
    cin >> c >> n >> p >> w;
    if(c>=p){
        cout << w/c << endl;
        return 0;
    }
    ll l=0;
    ll r = w/c;
    while(l<r-1){
        ll md = (l+r)/2;
        if(ok(md)){
            l=md;
        }else{
            r=md-1;
        }
    }
    if(ok(r))
        cout << r ;
    else
        cout << l;
    return 0;
}
