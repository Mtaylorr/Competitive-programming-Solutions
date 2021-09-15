//https://www.spoj.com/problems/PERIOD/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5;

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

int t,n;
int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    int ii=0;
    while(t--){
        scanf("%d",&n);
        scanf("%s",pat);
        compute_f();
        int ln = strlen(pat);
        printf("Test case #%d\n", ++ii);
        for(int i=0;i<ln;i++){
            int curln = i+1;
            if(curln%(curln-F[i])==0 && curln/(curln-F[i])>1){
                printf("%d %d\n", i+1 ,curln/(curln-F[i]));
            }
        }
    }
    return 0;
}
