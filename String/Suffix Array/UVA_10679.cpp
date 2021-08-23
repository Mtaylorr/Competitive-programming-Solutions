//https://vjudge.net/problem/UVA-10679

#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 1e3 + 5;
char s[N];
int n;
int suff[N], rnk[N], newrnk[N],len;

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


void buildSuffix_N2_logN(){
    for(len=0;!len||s[len-1];++len)
        suff[len]=len;
    sort(suff, suff+len,[](int a,int b){return strcmp(s+a,s+b)<0;});
}

int main()
{
    freopen("input.txt", "r", stdin);
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%s",s);
        buildSuffix_N_log2N();
        scanf("%d",&n);
        while(n--){
            scanf("%s",s+len);
            int st=0, en=len;
            for(int i=0;st<en && s[len+i];++i){
                st = lower_bound(suff+st, suff+en, len,[i](int a,int b){return s[a+i]<s[b+i];})-suff;
                en = upper_bound(suff+st, suff+en, len,[i](int a,int b){return s[a+i]<s[b+i];})-suff;
            }
            puts((st<en) ?"y": "n");
        }
    }
    return 0;
}
