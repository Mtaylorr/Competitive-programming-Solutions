#include <bits/stdc++.h>

using namespace std;
const int N = 1e6+5;

#define fi first
#define se second
#define pb push_back

typedef long long ll;

int t;
int n;
char s[N];

int main(){
    freopen("weak_typing_chapter_1_input.txt", "r", stdin);
    freopen("output.txt","w", stdout);
    scanf("%d",&t);
    int tt=0;
    while(t--){
        scanf("%d",&n);
        scanf("%s",s);
        int cur=-1;
        int res=0;
        for(int i=0;i<n;i++){
            if(s[i]=='F')
                continue;
            if(s[i]=='X'){
                if(cur==2)
                    res++;
                cur=1;
            }else{
                if(cur==1)
                    res++;
                cur=2;
            }
        }
        printf("Case #%d: %d\n",++tt,res);
    }
    return 0;
}
