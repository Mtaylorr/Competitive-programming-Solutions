#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e6+5;

int t;
char s[N];
ll k;
int getModulo(){
    ll res=0;
    for(int i=0;s[i];i++){
        res= (res*10 + (ll)(s[i]-'0'))%k;
    }
    return res;
}

int main(){
    freopen("input.txt", "r", stdin);
    //freopen("cipher.in", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%s",s);
        scanf("%lld",&k);
        if(getModulo()==0)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
