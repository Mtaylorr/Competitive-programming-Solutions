#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e5+5;
const int MOD = 1e9 +7;

int t,n,s,x;
int main(){
    freopen("input.txt", "r", stdin);
    //freopen("adhm.in", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&n,&s,&x);
        if(s<n){
            puts("Methat");
        }else if(x<n){
            puts("Methat");
        }else{
            puts("Adhm");
        }
    }
    return 0;
}
