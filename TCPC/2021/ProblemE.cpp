#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e6+5;

int n;
char a[N], b[N];
int t;
int main(){
    freopen("input.txt", "r", stdin);
    //freopen("rabbits.in", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        scanf("%s",a);
        scanf("%s",b);
        int zeros=0;
        int eqone = 0;
        for(int i=0;i<n;i++){
            if(a[i]!=b[i]){
                continue;
            }else if(a[i]=='1'){
                eqone++;
            }else{
                zeros++;
            }
        }
        if(eqone==0){
            puts("YES");
        }else if(eqone>1){
            puts("NO");
        }else if(zeros==0){
            puts("NO");
        }else{
            puts("YES");
        }
    }
    return 0;
}
