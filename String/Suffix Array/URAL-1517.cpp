//https://vjudge.net/problem/URAL-1517

#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
char s[N];
int n;
int suff[N], rnk[N], newrnk[N],len;
int LCP[N];

void buildSuffix_N_log2N(){
    for(len=0;!len||s[len-1];++len){
        suff[len]=len;
        rnk[len]=s[len];
    }
    int cur=1;
    do{
        auto cmp = [cur](int a , int b){return rnk[a]<rnk[b] || rnk[a]==rnk[b]&& rnk[a+cur]<rnk[b+cur];};
        sort(suff, suff+len, cmp);
        newrnk[0]=0;
        for(int i=1;i<len;++i){
            newrnk[i] = newrnk[i-1] + (cmp(suff[i-1], suff[i]));
        }
        for(int i=0;i<len;++i){
            rnk[suff[i]] = newrnk[i];
        }
        cur<<=1;
    }while(newrnk[len-1]!=len-1);
}

void buildLCP(){
    int cnt=0;
    for(int i=0;s[i];++i){
        int j = suff[rnk[i]-1];
        while(s[i+cnt]==s[j+cnt])
            cnt++;
        LCP[rnk[i]] = cnt;
        if(cnt)
            cnt--;
    }
}

int t;
int main()
{
    scanf("%d",&n);
    scanf("%s",s);
    s[n]='$';
    scanf("%s",s+n+1);
    buildSuffix_N_log2N();
    buildLCP();
    int mx=-1;
    int pos=-1;
    for(int i=1;i<len;i++){
        if((suff[i]<n)!=(suff[i-1]<n)){
            if(LCP[i]>mx){
                mx=LCP[i];
                pos=suff[i];
            }
        }
    }
    s[mx+pos]=0;
    puts(s+pos);
    return 0;
}
