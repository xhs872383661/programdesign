#include <iostream>
#include <string>
#include <map>
#include <cstdio>
using namespace std;

int main()
{
    freopen("in.txt","r",stdin);
    int INF = 99999999, N, K, d[30][30], i, j, k, x, y, z;
    int dp[256][30], e[8], v[30], c, b;
    string s, t;
    while (cin >> N >> K && N)
    {
        map <string, int> cityMap;
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                d[i][j] = i == j ? 0 : INF;
        for (i = 0; i < N; i++)
        {
            cin >> s;
            cityMap[s] = i;
        }
        if (K)
            while (cin >> s >> t >> z, x = cityMap[s],
                    y = cityMap[t],
                    d[x][y] = d[y][x] = min(d[y][x], z), --K);
        for (k = 0; k < N; k++)
            for (i = 0; i < N; i++)
                for (j = 0; j < N; j++)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        for (i = 0; i < 8; i++)
        {
            cin >> s;
            e[i] = cityMap[s];
            for (j = 0; j < N; j++)
                dp[1 << i][j] = d[j][e[i]];
        }
        for (i = 1; i < 256; i++)
        {
            if (!(i & (i - 1)))
                continue;
// step1
            for (k = 0; k < N; k++)
            {
                dp[i][k] = INF;
                v[k] = 0;
                /*for (j = 1; j < i; j++)
                if ((i | j) == i)
                dp[i][k] = min(dp[i][k], dp[j][k] + dp[i-j][k]);*/
                for (int sub = i; sub; sub = (sub - 1) & i)
                {
                    dp[i][k] = min(dp[i][k], dp[sub][k] + dp[i - sub][k]);
                }
            }

// step2
            for (j = 0; b = INF, j < N; j++)
            {
                for (k = 0; k < N; k++)
                    if (dp[i][k] <= b && !v[k])
                        b = dp[i][c = k];
                for (k = 0, v[c] = 1; k < N; k++)
                    if(dp[i][k]+d[k][c]<dp[i][c])
                        dp[i][c] = min(dp[i][c], dp[i][k] + d[k][c]);
            }
        }

// step3
/*
        for (i = 0, b = INF; z = 0, i < 256; b = min(b, z), i++)
            for (j = 0; y = 0, j < 4; z += !!y * dp[y][x], j++)
                for (k = 0; k < 8; k += 2)
                    if ((i >> k & 3) == j)
                        y += 3 << k, x = e[k];
*/
        b = INF;
        for (i = 0; i < 256; i++)
        {
            z = 0;
            for (j = 0; j < 4; j++)
            {
                y = 0;
                for (k = 0; k < 8; k += 2)
                    if ((i >> k & 3) == j)
                        y += 3 << k, x = e[k];
                z += !!y * dp[y][x];
            }
            b = min(b, z);
        }

        cout << b << endl;
    }
    return 0;
}
