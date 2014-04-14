#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn=1000+100;
int N,Q;
struct Rec
{
    int xl,yl;
    int xr,yr;
    Rec *lc,*rc;
    Rec *fa;
    int h;
    bool vh;//0 for h,1 for v
    Rec():lc(0),rc(0){}
    Rec(Rec *f,int x1,int y1,int x2,int y2):fa(f)
    {
        lc=rc=0;
        xl=x1;
        xr=x2;
        yl=y1;
        yr=y2;
        h=fa->h+1;
        vh=fa->vh^1;
        if(xl>xr)
            swap(xl,xr);
        if(yl>yr)
            swap(yl,yr);
    }
    void reset()
    {
        if(lc)
        {
            lc->reset();
            delete lc;
            lc=0;
        }
        if(rc)
        {
            rc->reset();
            delete rc;
            rc=0;
        }
    }
};
Rec root;
Rec* lvs[maxn];//Ҷ��
int lvn;

struct SEG
{
    int x1,y1,x2,y2;
    void inputSeg()
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        if(x1>x2)
            swap(x1,x2);
        if(y1>y2)
            swap(y1,y2);
    }
    void inputQ()
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    }
};
SEG sgs[maxn];
SEG qry[maxn];

bool Bin(int x,int y,Rec* r)
{
    if(x>r->xl&&x<r->xr&&y>r->yl&&y<r->yr)
        return true;
    return false;
}

queue<Rec*> que;

void work()
{
    lvs[lvn++]=&root;
    root.fa=0;
    root.h=1;
    root.vh=0;
    Rec* now;
    que.push(&root);
    while(!que.empty())
    {
        now=que.front();
        que.pop();
        for(int i=0;i<N;i++)
        {
  //          if(usd[i]) continue;
            if(now->vh&&sgs[i].x1==sgs[i].x2&&sgs[i].y1==now->yl&&sgs[i].y2==now->yr&&sgs[i].x1>=now->xl&&sgs[i].x1<=now->xr)
            {
                now->lc=new Rec(now,now->xl,now->yl,sgs[i].x1,now->yr);
                que.push(now->lc);
                now->rc=new Rec(now,sgs[i].x1,now->yl,now->xr,now->yr);
                que.push(now->rc);
                break;
            }
            else if(!now->vh&&sgs[i].y1==sgs[i].y2&&sgs[i].x1==now->xl&&sgs[i].x2==now->xr&&sgs[i].y1>=now->yl&&sgs[i].y2<=now->yr)
            {
                now->lc=new Rec(now,now->xl,sgs[i].y1,now->xr,now->yr);
                que.push(now->lc);
                now->rc=new Rec(now,now->xl,now->yl,now->xr,sgs[i].y1);
                que.push(now->rc);
                break;
            }
            if(i==N-1)
            {
                lvs[lvn++]=now;
            }
        }
    }
    Rec *a,*b;
    int res=0;
    /*
    if(lvn!=N+1)
    {
        printf("%d",1/(res));
    }
    */
    for(int i=0;i<Q;i++)
    {
        res=0;
        a=0;b=0;
        for(int j=0;j<lvn;j++)
        {
            if(Bin(qry[i].x1,qry[i].y1,lvs[j]))
            {
                /*
                if(a)
                    printf("%d",1/(res));
                */
                a=lvs[j];
            }
            if(Bin(qry[i].x2,qry[i].y2,lvs[j]))
            {
                /*
                if(b)
                    printf("%d",1/(res));
                */
                b=lvs[j];
            }
        }
        while(a->h>b->h)
        {
            res++;
            a=a->fa;
        }
        while(b->h>a->h)
        {
            res++;
            b=b->fa;
        }
        while(a!=b)
        {
            res+=1;
            a=a->fa;
            b=b->fa;
            if(a==b) break;
            res+=1;
        }
        printf("%d\n",N+1-res);
    }
}

void input()
{
    if(root.xl>root.xr)
        swap(root.xl,root.xr);
    if(root.yl>root.yr)
        swap(root.yl,root.yr);
    scanf("%d%d",&N,&Q);
    for(int i=0;i<N;i++)
        sgs[i].inputSeg();
    for(int i=0;i<Q;i++)
        qry[i].inputQ();

}

void init()
{
    lvn=0;
    root.reset();
}

int main()
{
    freopen("in.txt","r",stdin);
    while(~scanf("%d%d%d%d",&root.xl,&root.yl,&root.xr,&root.yr))
    {
        init();
        input();
        work();
    }
    return 0;
}
