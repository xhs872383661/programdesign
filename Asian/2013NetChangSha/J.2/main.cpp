#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=100000+100;
int N,P;
int a[maxn];
int s[maxn];
int pr[maxn];

void dfs(int i)
{
    if(a[i]==-1) return;
    pr[i]=a[i];
    if(i>=3&&a[i-3]==-1)
    {
        a[i-3]=a[i]-s[i-1]+s[i-2];
        dfs(i-3);
    }
    if(i<N-3&&a[i+3]==-1)
    {
        a[i+3]=a[i]-s[i+1]+s[i+2];
        dfs(i+3);
    }
    if(i<N-1&&a[i+1]!=-1)
    {
        if(i>0&&a[i-1]==-1)
        {
            a[i-1]=s[i]-a[i]-a[i+1];
            dfs(i-1);
        }
        if(i<N-2&&a[i+2]==-1)
        {
            a[i+2]=s[i+1]-a[i]-a[i+1];
            dfs(i+2);
        }
    }
    if(i>0&&a[i-1]!=-1)
    {
        if(i>1&&a[i-2]==-1)
        {
            a[i-2]=s[i-1]-a[i]-a[i-1];
            dfs(i-2);
        }
        if(a[i+1]==-1&&i<N-1)
        {
            a[i+1]=s[i]-a[i]-a[i-1];
            dfs(i+1);
        }
    }
    if(i<N-2&&a[i+2]!=-1&&a[i+1]==-1)
    {
        a[i+1]=s[i+1]-a[i]-a[i+2];
        dfs(i+1);
    }
    if(i>1&&a[i-2]!=-1&&a[i-1]==-1)
    {
        a[i-1]=s[i-1]-a[i]-a[i-2];
        dfs(i-1);
    }
}

int main()
{
  //  freopen("in.txt","r",stdin);
  //  freopen("out.txt","w",stdout);

    while(~scanf("%d",&N))
    {
        for(int i=0; i<N; i++)
            scanf("%d",&a[i]);
        for(int i=0; i<N; i++)
            scanf("%d",&s[i]);
        a[2]=s[1]-s[0];
        for(int i=5; i<N; i+=3)
            a[i]=s[i-1]-s[i-2]+a[i-3];
        a[N-3]=s[N-2]-s[N-1];
        for(int i=N-6; i>=0; i-=3)
            a[i]=s[i+1]-s[i+2]+a[i+3];
        for(int i=0; i<N; i++)
        {
            dfs(i);
        }

        int np,nr;
        if(a[0]==-1)
        {
            pr[0]=s[0];
            if(a[1]!=-1)
                pr[0]-=a[1];
            np=0;
            for(int i=3;i<N;i+=3)
            {
                np+=s[i-1]-s[i-2];
                nr=s[i];
                if(i>0&&a[i-1]!=-1)
                    nr-=a[i-1];
                if(i<N-1&&a[i+1]!=-1)
                    nr-=a[i+1];
                pr[0]=min(pr[0],nr-np);
            }
            np=0;
            for(int i=3;i<N;i+=3)
            {
                np+=s[i-1]-s[i-2];
                pr[i]=pr[0]+np;
            }
        }

        if(a[1]==-1)
        {
            pr[1]=s[1]-a[2];
            if(a[0]!=-1)
                pr[1]-=a[0];
            np=0;
            for(int i=4;i<N;i+=3)
            {
                np+=s[i-1]-s[i-2];
                nr=s[i];
                if(i>0&&a[i-1]!=-1)
                    nr-=a[i-1];
                if(i<N-1&&a[i+1]!=-1)
                    nr-=a[i+1];
                pr[1]=min(pr[1],nr-np);
            }
            np=0;
            for(int i=4;i<N;i+=3)
            {
                np+=s[i-1]-s[i-2];
                pr[i]=pr[1]+np;
            }
        }

        scanf("%d",&P);
        int t;
        for(int i=0; i<P; i++)
        {
            scanf("%d",&t);
            printf("%d\n",pr[i]);
        }
/*
        for(int i=0;i<N;i++)
            printf("%d ",a[i]);
        puts("");
        for(int i=0;i<N;i++)
            printf("%d ",pr[i]);
        puts("");
*/
    }
    return 0;
}
