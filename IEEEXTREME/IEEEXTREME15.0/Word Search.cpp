//89.29%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 +5 ;
const int MOD = 1e9 +7, B= 37;

int r,c,q;

char grid[105][105];

unordered_map<int,pair<pair<int,int> , pair<int,int> > > pos;


void upd(int h , int rs , int cs , int re, int ce){
    if(pos.count(h)){
        pos[h]=min(pos[h], {{rs,cs},{re,ce}});
    }
    else{
        pos[h]={{rs,cs},{re,ce}};
    }
}
string s;


int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d%d%d",&r,&c,&q);
    for(int i=0;i<r;i++){
        scanf("%s",grid[i]);
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            int h = 0;
            for(int k=j;k<c;k++){
                h = ((h*1ll*B)%MOD + (grid[i][k]-'a'+1))%MOD;
                upd(h,i,j,i,k);
            }
            h = 0;
            for(int k=j;k>=0;k--){
                h = ((h*1ll*B)%MOD + (grid[i][k]-'a'+1))%MOD;
                upd(h,i,j,i,k);
            }
        }
    }

    for(int i=0;i<c;i++){
        for(int j=0;j<r;j++){
            int h = 0;
            for(int k=j;k<r;k++){
                h = ((h*1ll*B)%MOD+ (grid[k][i]-'a'+1))%MOD;
                upd(h,j,i,k,i);
            }
            h = 0;
            for(int k=j;k>=0;k--){
                h = ((h*1ll*B)%MOD + (grid[k][i]-'a'+1))%MOD;
                upd(h,j,i,k,i);
            }
        }
    }

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            int h=0;
            for(int k=0;k+i<r && k+j<c;k++){
                h = ((h*1ll*B)%MOD + (grid[i+k][j+k]-'a'+1))%MOD;
                upd(h,i,j,i+k,j+k);
            }
            h=0;
            for(int k=0;i-k>=0 && j-k>=0;k++){
                h = ((h*1ll*B)%MOD + (grid[i-k][j-k]-'a'+1))%MOD;
                upd(h,i,j,i-k,j-k);
            }
        }
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            int h=0;
            for(int k=0;i-k>=0 && k+j<c;k++){
                h = ((h*1ll*B)%MOD + (grid[i-k][j+k]-'a'+1))%MOD;
                upd(h,i,j,i-k,j+k);
            }
            h=0;
            for(int k=0;i+k<r && j-k>=0;k++){
                h = ((h*1ll*B)%MOD + (grid[i+k][j-k]-'a'+1))%MOD;
                upd(h,i,j,i+k,j-k);
            }
        }
    }
    while(q--){
        cin >> s;
        int h1=0;
        for(int i=0;i<s.size();i++){
            h1=((h1*1ll*B)%MOD)+(s[i]-'a'+1)%MOD;
        }

        if(pos.count(h1)==0){
            puts("-1");
        }else {
            pair<pair<int,int> ,pair<int,int> > p = pos[h1];
            cout << p.first.first << " " << p.first.second << " " << p.second.first << " " << p.second.second << endl;
        }


    }

    return 0;
}
