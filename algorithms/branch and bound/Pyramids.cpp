//https://vjudge.net/problem/UVA-1110
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353 ;


struct pyramid{
    int total, base;
    bool state;
};

vector<pyramid> v, curans, ansv;
int w;
int bst, cur;

void swim(int i, int rem){

    if(rem==0){
        if(bst>cur){
            bst=min(bst,cur);
            ansv=curans;
        }
        return ;
    }
    if(i==v.size())
        return ;
    if(cur+((rem+v[i].total-1)/v[i].total)>=bst)
        return ;
    if(rem>=v[i].total){
        cur++;
        curans.pb(v[i]);
        swim(i+1, rem-v[i].total);
        curans.pop_back();
        cur--;
    }
    swim(i+1,rem);



}

int main(){
    freopen("input.txt", "r",stdin);
    int n = 1e6;
    int t1 = 1, t2=1, t3=4;
    for(int b=2;t1<=n || t2<=n || t3<=n;b++){
        t1+=(b*b);
        if(t1<=n)
            v.pb({t1, b,1});
        if(b&1){
            t2+=b*b;
            if(t2<=n)
                v.pb({t2, b,0});
        }else if(b>2){
            t3+=b*b;
            if(t3<=n)
                v.pb({t3, b,0});
        }
    }
    sort(v.begin(), v.end(),[](const pyramid& a , const pyramid & b){return make_pair(a.total, a.state)>make_pair(b.total, b.state);});
    int ii=0;
    while(1){
        bst=1e9;
        cur=0;
        scanf("%d",&w);
        if(w==0)
            break;
        swim(0,w);
        printf("Case %d: ",++ii);
        if(bst<1e9){
            for(int i=0;i<ansv.size();i++){
                printf("%d%c%c", ansv[i].base, "LH"[ansv[i].state], " \n"[i==ansv.size()-1]);
            }
        }else{
            puts("impossible");
        }

    }
    return 0;
}
