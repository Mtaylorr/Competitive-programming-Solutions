//https://codeforces.com/problemset/problem/1439/A2
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;


vector<pair<int,int> > ans;
int grid[105][105];
char c;
int n,m,t;

void flip(int i,int j){
    grid[i][j]=1-grid[i][j];
    ans.pb({i,j});
}

void show(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("game.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        ans.clear();
        cin >> n >> m;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin >> c;
                grid[i][j]=c-'0';
            }
        }
        for(int i=0;i<n-1;i++){
            for(int j=0;j<m-1;j++){
                if(i<n-2 && j<m-2){
                    if(grid[i][j]){
                        flip(i,j);
                        flip(i+1,j);
                        flip(i+1,j+1);
                    }
                }
                else if(j==m-2 && i<n-2){
                    int nb=0;
                    if(grid[i][j] ==0 && grid[i][j+1]==0)
                        continue;
                    if(grid[i][j]) {
                        nb++;
                        flip(i, j);
                    }
                    if(grid[i][j+1]){
                        flip(i,j+1);
                        nb++;
                    }
                    if(nb<3){
                        flip(i+1,j);
                        nb++;
                    }
                    if(nb<3){
                        flip(i+1,j+1);
                        nb++;
                    }
                }
                else if(j<m-2 && i==n-2){
                    int nb=0;
                    if(grid[i][j] ==0 && grid[i+1][j]==0)
                        continue;
                    if(grid[i][j]) {
                        nb++;
                        flip(i, j);
                    }
                    if(grid[i+1][j]){
                        flip(i+1,j);
                        nb++;
                    }
                    if(nb<3){
                        flip(i,j+1);
                        nb++;
                    }
                    if(nb<3){
                        flip(i+1,j+1);
                        nb++;
                    }
                }
                else if(i==n-2 && j==m-2){
                    vector<pair<int,int> > ones, zeros;
                    for(int k=0;k<2;k++){
                        for(int o=0;o<2;o++){
                            if(grid[i+k][j+o]==1)
                                ones.pb({i+k,j+o});
                            else
                                zeros.pb({i+k,j+o});
                        }
                    }
                    if(ones.size()==1){
                        flip(ones[0].fi, ones[0].se);
                        flip(zeros[0].fi, zeros[0].se);
                        flip(zeros[1].fi, zeros[1].se);

                        flip(ones[0].fi, ones[0].se);
                        flip(zeros[0].fi, zeros[0].se);
                        flip(zeros[2].fi, zeros[2].se);

                        flip(ones[0].fi, ones[0].se);
                        flip(zeros[1].fi, zeros[1].se);
                        flip(zeros[2].fi, zeros[2].se);
                    }
                    else if(ones.size()==2){

                        flip(ones[0].fi, ones[0].se);
                        flip(zeros[0].fi, zeros[0].se);
                        flip(zeros[1].fi, zeros[1].se);


                        flip(ones[1].fi, ones[1].se);
                        flip(zeros[0].fi, zeros[0].se);
                        flip(zeros[1].fi, zeros[1].se);
                    }else if(ones.size()==3){
                        for(int k=0;k<3;k++){

                            flip(ones[k].fi, ones[k].se);
                        }
                    }else if(ones.size()==4){
                        for(int k=0;k<4;k++){
                            for(int o=0;o<3;o++){
                                flip(ones[(k+o)%4].fi, ones[(k+o)%4].se);
                            }
                        }
                    }
                }
               // show();
            }

        }
        cout << ans.size()/3 << endl;
        for(int i=0;i<ans.size();i+=3){
            for(int j=0;j<3;j++){
                cout << ans[i+j].fi+1 << " " << ans[i+j].se+1 << " ";
            }
            cout << endl;
        }
    }
    return 0;

}
