#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn=30+10;
const int inf=0x3f3f3f3f;

const int dx[]={-1,-1,1,1,-2,-2,2,2};
const int dy[]={2,-2,2,-2,1,-1,1,-1};

int N,M;
int map[maxn][maxn];

int m1[maxn][maxn][2]; //0 for min step,1 for ways
int m2[maxn][maxn][2];

struct Point
{
    Point(int xx,int yy):x(xx),y(yy){}
    Point (){}
    int x,y;
    bool check()
    {
        if(map[x][y]==2) return false;
        if(x>=0&&x<N&&y>=0&&y<M) return true;
        return false;
    }
};
Point start,end;

deque<Point> que;
bool in[maxn][maxn];
void getM(int sx,int sy,int mm[][maxn][2])
{
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            mm[i][j][0]=inf;
    memset(in,0,sizeof(in));
    mm[sx][sy][0]=0;
    mm[sx][sy][1]=1;
    in[sx][sy]=1;
    que.push_back(Point(sx,sy));
    Point now,tp;
    int dd;
    while(!que.empty())
    {
        now=que.front();
        que.pop_front();
        for(int i=0;i<8;i++)
        {
            tp.x=now.x+dx[i];
            tp.y=now.y+dy[i];
            if(tp.check())
            {
                dd=1;
                if(map[tp.x][tp.y]==1||map[tp.x][tp.y]==3||map[tp.x][tp.y]==4)
                    dd=0;
                if(mm[tp.x][tp.y][0]>mm[now.x][now.y][0]+dd)
                {
                    mm[tp.x][tp.y][0]=mm[now.x][now.y][0]+dd;
                    mm[tp.x][tp.y][1]=mm[now.x][now.y][1];
                    if(!in[tp.x][tp.y])
                    {
                        in[tp.x][tp.y]=1;
                        if(dd)
                            que.push_back(tp);
                        else que.push_front(tp);
                    }
                }
                else if(mm[tp.x][tp.y][0]==mm[now.x][now.y][0]+dd)
                    mm[tp.x][tp.y][1]+=mm[now.x][now.y][1];
            }
        }
        in[now.x][now.y]=0;
    }
}

void work()
{
    getM(start.x,start.y,m1);
    getM(end.x,end.y,m2);
    int res=inf,way;
    if(m1[end.x][end.y]==0)
    {
        printf("0\n0\n");
        return;
    }
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
        {
            if(map[i][j]!=0) continue;
            if(m1[i][j][0]+m2[i][j][0]<res)
            {
                res=m1[i][j][0]+m2[i][j][0];
                way=m1[i][j][1]*m2[i][j][1];
            }
            else if(m1[i][j][0]+m2[i][j][0]==res)
            {
                way+=m1[i][j][1]*m2[i][j][1];
            }
        }
    printf("%d\n%d\n",res-1,way/2);
}

void input()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
        {
            scanf("%d",&map[i][j]);
            if(map[i][j]==3)
            {
                start.x=i;
                start.y=j;
            }
            if(map[i][j]==4)
            {
                end.x=i;
                end.y=j;
            }
        }
}

int main()
{
    freopen("in.txt","r",stdin);
    while(~scanf("%d%d",&N,&M))
    {
        input();
        work();
    }
    return 0;
}
