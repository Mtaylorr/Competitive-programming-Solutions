//https://www.spoj.com/problems/NHAY/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e6 + 5;

char str[N];
int Z[N];

void compute_z(){
    int st=1, en=1, i;
    for(i=1;str[i];i++){
        int p = i-st;
        if(Z[p]+i>=en){
            st=i;
            en=max(en, i);
            while(str[en]==str[en-st])
                en++;
            Z[i]=en-st;
        }else{
            Z[i]=Z[p];
        }
    }
    Z[0]=i;
}


int n;
int main(){
    freopen("input.txt", "r", stdin);
    while(~scanf("%d",&n)){
        scanf("%s",str);
        str[n]='$';
        scanf("%s",(str+n+1));
        compute_z();
        for(int i=n+1,j=0;str[i];i++,j++){
            if(Z[i]==n)
                printf("%d\n",j);
        }
    }
    return 0;
}
