ans = 0

def solve(i, j, r, x, groups,dp):
    if i>= len(x):
        return (j==len(groups) and r==0) or (r!=0 and j==len(groups)-1 and r==groups[j])
    if dp[i][j][r]!=-1:
        return dp[i][j][r]
    rs=0
    if x[i]=='.':
        if r==0 or (r==groups[j]):
            rs += solve(i+1,j+(r!=0 and r==groups[j]),0,x,groups, dp)
    elif x[i]=='#':
        if j<len(groups) and r+1 <= groups[j]:
            rs += solve(i+1,j,r+1,x,groups, dp)
    else:
        if r == 0 or (r == groups[j]):
            rs += solve(i + 1, j + (r != 0 and r == groups[j]), 0, x, groups, dp)
        if j < len(groups) and r + 1 <= groups[j]:
            rs += solve(i + 1, j, r + 1, x, groups, dp)
    dp[i][j][r]=rs
    return rs

while True:
    try:
        x,y = input().split()
        groups = list(map(int,y.split(',')))
        l = [x for i in range(5)]
        initial_groups = groups[::]
        x= '?'.join(l)
        for i in range(4):
            groups+=initial_groups
        n = len(x)
        m = len(groups)
        dp=[[[-1 for i in range(n+1)] for j in range(m+1)]for k in range(n+1)]
        rs = solve(0,0,0,x,groups,dp)
        ans += rs
    except:
        break
print(ans)
