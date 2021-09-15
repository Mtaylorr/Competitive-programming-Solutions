//https://www.spoj.com/problems/NHAY/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5;

char s[N];
char pat[N];
int F[N];

int getNextLen(int len , char c){
    while(len && pat[len]!=c)
        len=F[len-1];
    if(pat[len]==c)
        len++;
    return len;
}

void compute_f(){
    F[0]=0;
    for(int i=1;pat[i];i++){
        F[i]=getNextLen(F[i-1], pat[i]);
    }
}

void match(){
    int len=0;
    for(int i=0;s[i];i++){
        len = getNextLen(len ,s[i]);
        if(!pat[len])
            printf("%d\n", i-len+1);
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    int n;
    while(~scanf("%d",&n)){
        scanf("%s %s", pat, s);
        compute_f();
        match();
        printf("\n");
    }
    return 0;
}
