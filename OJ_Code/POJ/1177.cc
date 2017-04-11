//Problem:[POJ1177][IOI1998][Picture]
//Powered By HYS.
//Accepted at 18:50,2017/04/11 on VJudge.
#include<cstring>
#include<iostream>
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#define lson (now->lc)
#define rson (now->rc)
#define mid ((now->l+now->r)>>1)
#define nl (now->l)//左边界
#define nr (now->r)//右边界
#define nw (now->w)//原宽度（未离散化前）
#define nc (now->cov)//覆盖层数
#define ncl (now->col)//最左覆盖区间点
#define ncr (now->cor)//最右覆盖区间点
#define ns (now->sum)//覆盖长度
#define ng (now->ger)
#define root (&seg[1])
using namespace std;
const int N=10010;
typedef long long ull_t;
int n,top=0,pnt=0,seglen=0,x_1,y_1,x_2,y_2,map[N];
ull_t ans=0*1LL;
struct seg_t{int sum,ger,cov,col,cor,w,l,r;seg_t *lc,*rc;}seg[N<<2];
struct line_t{int l,r,h,s;}line[N];
inline bool cmp(line_t x,line_t y){return x.h<y.h;}
inline void in(int l,int r,int h,int s){
    line[++top].l=l,line[top].r=r,line[top].h=h,line[top].s=s;
}
inline int build(int l,int r){
    int temp=++pnt,m=((l+r)>>1);seg_t *now=&seg[temp];
    nl=l,nr=r,nw=map[r]-map[l],ns=nc=ncl=ncr=ng=0;
    if(r-l!=1)lson=&seg[build(l,m)],rson=&seg[build(m,r)];
    return temp;
}
inline int gethash(int key,int len){
    int l=1,r=len;
    while(l<=r){
        int m=(l+r)>>1;
        if(map[m]<key)l=m+1;
        else if(map[m]>key)r=m-1;
        else return m;
    }return -1;
}
inline void refresh(seg_t *now){
    ns=lson->sum+rson->sum,ng=lson->ger+rson->ger;
    if(rson->ger && rson->ger && rson->col==lson->cor)ng--;
    if(lson->ger && rson->ger)ncl=lson->col,ncr=rson->cor;
    else if(rson->ger)ncl=rson->col,ncr=rson->cor;
    else if(lson->ger)ncl=lson->col,ncr=lson->cor;
    else ncl=ncr=0;
}
inline void update(seg_t *now,int l,int r,int s){
    if(l<=nl && nr<=r){
        nc+=s;
        if(nc)ns=nw,ncl=nl,ncr=nr,ng=1;
        else ns=ncl=ncr=ng=0;
        if(!nc && nr-nl!=1)refresh(now);return;
    }int m=mid;
    if(l<mid)update(lson,l,r,s);if(r>mid)update(rson,l,r,s);
    if(!nc)refresh(now);
}
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&x_1,&y_1,&x_2,&y_2);
        /*x_2++,y_2++;*/in(x_1,x_2,y_1,1),map[top]=x_1,in(x_1,x_2,y_2,-1),map[top]=x_2;
    }
    sort(line+1,line+1+top,cmp),sort(map+1,map+1+top),seglen=unique(map+1,map+1+top)-map-1;
    build(1,seglen);int last=0;
    //for(int i=1;i<=top;i++){
    //    printf("[%d|%d]\n",i,line[i].h);
    //}
    for(int i=1;i<top;i++){
        int t1=gethash(line[i].l,seglen),t2=gethash(line[i].r,seglen);
        update(root,t1,t2,line[i].s);
        //printf("update:[%d,%d]",t1,t2);
        ans+=1LL*abs(last-root->sum);
        ans+=1LL*2*root->ger*(line[i+1].h-line[i].h);
        //printf("|1up:%d|2up:%d|ger:%d\n",abs(last-root->sum),2*root->ger*(line[i+1].h-line[i].h),root->ger);
        last=root->sum;
    }
    printf("%lld\n",ans+line[top].r-line[top].l);
}
int main(){
    freopen("input.txt","r",stdin),freopen("output.txt","w",stdout);
    solve();
    fclose(stdin),fclose(stdout);
    return 0;
}