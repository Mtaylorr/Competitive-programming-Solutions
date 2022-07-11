//https://codeforces.com/contest/1607/problem/F
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;

int n,m,t;
char grid[2005][2005];
int d[2005][2005];
int vis[2005][2005];

void dfs(int i, int j){
    int initial_i=i;
    int initial_j=j;
    while(1){
        vis[i][j]=1;
        int ni = i;
        int nj = j;
        switch(grid[i][j]){
            case 'R':
                nj++;
                break;
            case 'L' :
                nj--;
                break;
            case 'U':
                ni--;
                break;
            case 'D' :
                ni++;
                break;
        }
        if(ni>=0 && ni<n && nj>=0 && nj<m){
            if(vis[ni][nj]==1){
                int cur_d=1;
                int nii=ni;
                int njj=nj;
                while(nii!=i || njj!=j){
                    cur_d++;
                    switch(grid[nii][njj]){
                        case 'R':
                            njj++;
                            break;
                        case 'L' :
                            njj--;
                            break;
                        case 'U':
                            nii--;
                            break;
                        case 'D' :
                            nii++;
                            break;
                    }
                }
                int ans_d=cur_d;
                cur_d=1;
                nii=ni;
                njj=nj;
                while(nii!=i || njj!=j){
                    d[nii][njj]=ans_d;
                    switch(grid[nii][njj]){
                        case 'R':
                            njj++;
                            break;
                        case 'L' :
                            njj--;
                            break;
                        case 'U':
                            nii--;
                            break;
                        case 'D' :
                            nii++;
                            break;
                    }
                }
                d[i][j]=ans_d;
                break;
            }else if(vis[ni][nj]==0){
                i = ni;
                j = nj;
            }else{
                break;
            }
        }else{
            break;
        }
    }
    i=initial_i;
    j=initial_j;
    while(1){
        vis[i][j]=2;
        int ni = i;
        int nj = j;
        switch(grid[i][j]){
            case 'R':
                nj++;
                break;
            case 'L' :
                nj--;
                break;
            case 'U':
                ni--;
                break;
            case 'D' :
                ni++;
                break;
        }

        if(ni>=0 && ni<n && nj>=0 && nj<m && vis[ni][nj]!=2){
            i=ni;
            j=nj;
        }else{
            break;
        }
    }
}

void calcd(int i,int j){
    stack<pair<int,int> > st;
    pair<int,int> p;
    st.push({i,j});
    while(!st.empty()){
        p=st.top();
        int i = p.fi;
        int j = p.se;
        if(d[i][j]!=-1)
        {
            st.pop();
            continue;
        }
        int ni = i;
        int nj = j;

        switch(grid[i][j]){
            case 'R':
                nj++;
                break;
            case 'L' :
                nj--;
                break;
            case 'U':
                ni--;
                break;
            case 'D' :
                ni++;
                break;
        }
        if(ni>=0 && ni<n && nj>=0 && nj<m){
            //cout << i << " " << j << " " << ni << " " << nj << " " << d[ni][nj] << endl;
            if(d[ni][nj]==-1){
                st.push({ni,nj});
            }else{
                d[i][j]=1+d[ni][nj];
                st.pop();
            }

        }else{
            d[i][j]=1;
            st.pop();
        }
    }

}

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("game.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n >> m;
        for(int i=0;i<n;i++){
            cin >> grid[i];
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                vis[i][j]=0;
                d[i][j]=-1;
            }
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(!vis[i][j]){
                    dfs(i,j);
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(d[i][j]==-1){
                    calcd(i,j);
                }
            }
        }
        int ans = -1;
        int ansi=-1;
        int ansj=-1;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(d[i][j]>ans){
                    ans=d[i][j];
                    ansi=i;
                    ansj=j;
                }
            }
        }
        cout << ansi+1 << " " << ansj+1 << " " << ans << endl;


    }
    return 0;

}
