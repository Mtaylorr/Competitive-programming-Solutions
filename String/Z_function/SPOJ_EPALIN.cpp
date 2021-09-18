//https://www.spoj.com/problems/EPALIN/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e6 +5;

int Z[N];
int n,l;
char s[N];
char ss[N];
void compute_z(){
    int st=1, en=1,i;
    for(i=1;s[i];i++){
        if(i+ Z[i-st]>=en){
            st=i;
            en=max(en, i);
            while(s[en]==s[en-st]){
                en++;
            }
            Z[i] = en-st;
        }else{
            Z[i] = Z[i-st];
        }
    }
    Z[0]=i;
}



int main(){
    while(~scanf("%s",ss)){
        int n = strlen(ss);
        reverse(ss,ss+n);
        strcpy(s, ss);
        s[n]='#';
        reverse(ss,ss+n);
        strcpy(s+n+1, ss);
        compute_z();
        int ln = 0;
        for(int i=n+1;s[i];i++){
            if(2*n+1-i==Z[i]){
                ln=max(ln,Z[i]);
            }
        }
        ln = n-ln;
        cout << ss;
        for(int i=ln-1;i>=0;i--){
            cout << ss[i];
        }
        cout << endl;
    }
    return 0;
}
