//https://www.spoj.com/problems/PLD/
#include <bits/stdc++.h>
#include <ext/numeric>
#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;
using namespace __gnu_cxx;
const int N = 1e6+5;
const int MOD = 1e9+7;
const int BASE = 128;

struct MUL{
    int operator()(int x , int y){
        return x*1LL * y % MOD;
    }
}mul;

int identity_element(const MUL &ml){
    return 1;
}

int add(int x, int y){
    return (x+y)%MOD;
}

int sub(int x, int y){
    return add(x, MOD-y%MOD);
}

const int INV = power(BASE, MOD-2, mul);

char s[30005];
int k;

int main(){
    freopen("input.txt", "r", stdin);
    //freopen("output.txt","w", stdout);
    scanf("%d",&k);
    scanf("%s",s);
    int  h1 =0, h2=0,p=1;
    for(int i=0, j=k-1;i<k;i++,j--){
        if(i)
            p=mul(p, BASE);
        h1=mul(h1,BASE);
        h1=add(h1,s[i]);
        h2=mul(h2,BASE);
        h2=add(h2, s[j]);
    }
    int res=0;
    for(int i=k,j=0;;i++,j++){
        res+=(h1==h2);
        if(!s[i])
            break;
        h1 = sub(h1, mul(s[j],p));
        h1 = mul(h1,BASE);
        h1 = add(h1, s[i]);

        h2 = sub(h2, s[j]);
        h2 = mul(h2, INV);
        h2=add(h2, mul(s[i],p));
    }
    cout << res << endl;
    return 0;
}
