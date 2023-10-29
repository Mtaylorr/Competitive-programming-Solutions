#include <bits/stdc++.h>

using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool safe(int i, int j, int &n, int &m) {
    return i>-1 && j>-1 && i<n && j<m;
}

int main() {
    //freopen("a.txt", "r", stdin);

    int n,m;
    cin>>n>>m;

    int v[n][m];
    double res[n][m];
    priority_queue<vector<double>> pq;
    for (int i=0 ; i<n ; i++) {
        for (int j=0 ; j<m ; j++) {
            cin>>v[i][j];
            res[i][j] = 1;
            pq.push({(double)v[i][j], (double)i, (double)j, res[i][j]});
        }
    }
    
    while(!pq.empty()) {
        vector<double> top = pq.top();
        int i = top[1];
        int j = top[2];
        double w = top[3];
        
        pq.pop();
        if (w < res[i][j])
            continue;
        
        int cnt = 0;
        for (int d=0 ; d<4 ; d++) {
            int di = i + dx[d];
            int dj = j + dy[d];
            
            if (safe(di, dj, n, m) && v[di][dj] < v[i][j]) {
                cnt++;
            }
        }
        
        for (int d=0 ; d<4 ; d++) {
            int di = i + dx[d];
            int dj = j + dy[d];
            
            if (safe(di, dj, n, m) && v[di][dj] < v[i][j]) {
                double xx = res[i][j]/double(cnt);
                res[di][dj] += xx;
                pq.push({(double)v[di][dj], (double)di, (double)dj, res[di][dj]});
            }
        }
    }
    
    double ans = 0;
    for (int i=0 ; i<n ; i++) {
        for (int j=0 ; j<m ; j++) {
            ans = max(ans, res[i][j]);
        }
    }
    cout<<ans<<endl;
    return 0;
}
