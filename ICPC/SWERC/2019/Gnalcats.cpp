#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 +7 ;

char s[2][N];
int n[2];
int v[N][2];
bool cond[2];
int v1s, v2s;
int nxt[N][2][2];
int s1[N],s2[N];
bool ok=true;
map<pair<int,int> ,int> id;
set<pair<int,int> > val;

void isEqual(int &x, int &y){
    if(val.count({x,y}))
        return ;
    val.insert({x,y});
    if(x>=100000   && y<100000  ){
        ok=false;
        return;
    }
    if(x<100000   && y>=100000  ){
        ok=false;
        return;
    }
    if(x>=100000  ){
        isEqual(nxt[x][0][0],nxt[y][1][0]);
        isEqual(nxt[x][0][1],nxt[y][1][1]);
        return ;
    }
    if(x!=y)
        ok=false;

}


int main()
{
    //freopen("input.txt", "r",stdin);
    scanf("%s",s[0]);
    scanf("%s",s[1]);
    n[0]=strlen(s[0]);
    n[1]=strlen(s[1]);

    for(int j=0;j<2;j++){
        id.clear();
        cond[j]=1;
        int cur = 15e3;
        int c = 100000;
        for(int i=0;i<=3e4;i++){
            v[i][j]=i;
        }
        for(int i=0;i<15e3;i++){
            v[i][j]=-1;
        }
        for(int i=0;i<n[j];i++){
            if(!cond[j])
                break;
            switch(s[j][i]){
                case 'C':{
                    v[cur-1][j]=v[cur][j];
                    cur--;
                    break;
                }
                case 'D':{
                    v[cur][j]=-1;
                    cur++;
                    break;
                }
                case 'L':{
                    if(v[cur][j]<100000){
                        cond[j]=false;
                    }else{
                        int z = v[cur][j];
                        v[cur][j]=nxt[z][j][0];
                    }
                    break;
                }


                case 'P':{
                    int x = v[cur][j];
                    int y = v[cur+1][j];
                    nxt[c][j][0]=x;
                    nxt[c][j][1]=y;
                    v[cur+1][j]=c;
                    v[cur][j]=-1;
                    cur++;
                    c++;

                    break;
                }
                case 'R':{
                    if(v[cur][j]<100000){
                        cond[j]=false;
                    }else{
                        int z = v[cur][j];
                        v[cur][j]=nxt[z][j][1];
                    }
                    break;
                }
                case 'S' :{
                    swap(v[cur][j],v[cur+1][j]);
                    break;
                }
                case 'U' : {
                    if(v[cur][j]<100000){
                        cond[j]=false;
                    }else{
                        int z = v[cur][j];
                        v[cur][j] = nxt[z][j][1];
                        v[--cur][j] = nxt[z][j][0];
                    }
                    break;
                }
            }
        }
    }



    if(!cond[0] && !cond[1]){
        puts("True");
        return 0;
    }

    if(!cond[0]){
        puts("False");
        return 0;
    }
    if(!cond[1]){
        puts("False");
        return 0;
    }
    for(int i=0;i<=3e4;i++){
        isEqual(v[i][0],v[i][1]);
        if(!ok)
            break;
        }
    if(ok){
        puts("True");
    }else{
        puts("False");
    }

    return 0;

}
