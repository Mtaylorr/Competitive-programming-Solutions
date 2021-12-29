#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353 ;

int n,m,sz;
char s[105];
ll dp[105];

ll res=0;

void swim(int i){
    if(i==sz){
        if((!n) && (!m)){
            res++;
        }
        return ;
    }

    if(s[i]=='0'){
        n--;
        swim(i+1);
        n++;
    }else{
        ll cur=0;
        int j=i;
        while(j<sz && s[j]=='1'){
            cur = cur*2 + (s[j]-'0');
            j++;
        }
        if(cur==3 && n>=2 && m>=2){
            n-=2;
            m-=2;
            swim(i+2);
            n+=2;
            m+=2;
        }
        for(;j<=sz;j++){
            if(cur>n || cur>m)
                break;
            if((j==sz || s[j]=='0')&&(cur==1 || j-i<cur)){

                n-=cur;
                m-=cur;
                swim(j);
                n+=cur;
                m+=cur;
            }
            if(j==sz)
                break;
            cur = cur*2 + (s[j]-'0');
        }
    }
}

int main(){
    freopen("input.txt", "r",stdin);
    int ii=0;
    while(1){
        scanf("%d",&n);
        if(n==0)
            break;
        scanf("%d",&m);
        res=0;

        scanf("%s",s);
        sz=strlen(s);
        dp[sz]=0;
        ll po=1;
        for(int i=sz-1;i>=0;i--){
            dp[i]=po*(s[i]-'0') + (dp[i+1]);
            po*=2;
        }
        swim(0);
        printf("Case #%d: ",++ii);
        if(res==0){
            puts("NO");
        }else if(res==1){
            puts("YES");
        }else{
            puts("NOT UNIQUE");
        }
    }
    return 0;
}
