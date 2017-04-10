//Problem:[POJ1177][IOI1998][Picture]
//Powered By HYS.
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
#define root (&seg[1])
#define in(l,r,h,s) (line[++top].l=(l),line[top].r=(r),line[top].h=(h),line[top].s=(s))
using namespace std;
const int N=10010;
typedef unsigned long long ull_t;
int n,top=0,pnt=0,seglen=0,x1,y1,x2,y2,map[N];
ull_t ans=0*1LL;
struct seg_t{int sum,cov,col,cor,w,l,r;seg_t *lc,*rc;}seg[N<<2];
struct line_t{int l,r,h,s;}line[N];
inline bool cmp(line_t x,line_t y){return x.h<y.h;}
inline int build(int l,int r){
    int temp=++pnt,m=((l+r)>>1);seg_t *now=&seg[temp];
    nl=l,nr=r,nw=map[r]-map[l],ns=nc=ncl=ncr=0;
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
    ns=lson->sum+rson->sum;
    if()
}
inline void update(seg_t *now,int l,int r,int s){
    if(l<=nl && nr<=r){
        nc+=s,ns=nc?nw:0,ncl=nl,ncr=nr;return;
    }int m=mid;
    if(l<mid)update(lson,l,r,s);if(r>mid)update(rson,l,r,s);
    refresh(now);
}
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        x2++,y2++;in(x1,x2,y1,1),map[top]=x1,in(x1,x2,y2,-1),map[top]=x2;
    }
    sort(line+1,line+1+top,cmp),sort(map+1,map+1+top),seglen=unique(map+1,map+top)-1;
    build(1,seglen);int len=0;
    for(int i=1;i<top;i++){、
        update(root,gethash(line[i].l),gethash(line[i].r),line[i].s);
        ans+=root->sum*abs(last-root->len);
        //TODO:Add Up Answer.
    }
    printf("%llu\n",ans);
}
int main(){
    freopen("input.txt","r",stdin),freopen("output.txt","w",stdout);
    solve();
    fclose(stdin),fclose(stdout);
    return 0;
}