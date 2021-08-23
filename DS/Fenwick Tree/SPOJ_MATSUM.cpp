//https://www.spoj.com/problems/MATSUM/
#include <bits/stdc++.h>

using namespace std;

const int N = 1024 +2 ;


int n;
int tree[2*N][2*N];
int t;
char s[4];
int grid[N][N];

void upd(int x, int y, int val){
    for(;x<=n;x+=(x)&(-x)){
        int k=y;
        for(;k<=n;k+=(k)&(-k)){
            tree[x][k]+=val;
        }
    }
}

int get(int x, int y){
    int res=0;
    for(;x;x-=(x)&(-x)){
        int k=y;
        for(;k;k-=(k)&(-k)){
            res+=tree[x][k];
        }
    }
    return res;
}


int query(int a, int b, int c , int d){
    return get(b,d)+get(a-1,c-1) - get(a-1,d)- get(b,c-1);
}



int a,b,c,d,k;
int main()
{
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                tree[i][j]=0;
                grid[i][j]=0;
            }
        }
        while(1){
            scanf("%s",&s);
            if(s[1]=='N')
                break;
            switch(s[1]){
            case 'E':
                scanf("%d%d%d",&a,&b,&k);
                a++;b++;
                upd(a,b,k-grid[a][b]);
                grid[a][b]=k;
                break;
            case 'U':
                scanf("%d%d%d%d",&a,&b,&c,&d);
                a++;b++;c++;d++;
                printf("%d\n",query(a,c,b,d));
                break;

            }
        }
    }
    return 0;
}
