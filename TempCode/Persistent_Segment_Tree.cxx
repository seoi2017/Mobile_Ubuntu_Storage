//可持久化线段树-模板(单点修改+区间查询)
//2017/4/14 08:42
//Powered By Inv.
#include<iostream>//库引用
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
#define lson (now->lc)//左子节点
#define rson (now->rc)//右子节点
#define get_root(x) (&seg[root[x]])//取第x版本根节点
using namespace std;
const int N=10010,K=110;//最大节点数和版本数
int root[K]={0};//各版本根节点索引
int n,k,top=0,ver=1;
struct seg_t{//线段树节点
    int maxs,l,r;
    seg_t *lc,*rc;
}seg[N*700];//开大点
inline int build(int l,int r){//建树函数
    int temp=++top;
    seg_t *now=&seg[temp];
    now->l=l,now->r=r;
    if(l==r)scanf("%d",&now->maxs);///边建树边输入
    else{
        int mid=(l+r)>>1;
        lson=&seg[build(l,mid)];
        rson=&seg[build(mid+1,r)];
        now->maxs=max(lson->maxs,rson->maxs);
    }
    return temp;
}
inline int update(seg_t *now,int x,int s){
    int temp=++top,nl=now->l,nr=now->r;
    seg_t *new_now=&seg[temp];
    new_now->l=nl,new_now->r=nr;
    if(nl==nr)new_now->maxs=s;
    else{
        int mid=(nl+nr)>>1;
        if(x<=mid){
            new_now->lc=&seg[update(lson,x,s)];
            new_now->rc=rson;
        }
        else{
            new_now->rc=&seg[update(rson,x,s)];
            new_now->lc=lson;
        }
        new_now->maxs=max(new_now->lc->maxs,new_now->rc->maxs);
    }
    return temp;
}
inline int query(seg_t *now,int l,int r){
    if(l<=now->l && now->r<=r)return now->maxs;
    int mid=(now->l+now->r)>>1,lrmax=-1;
    if(l<=mid)lrmax=max(lrmax,query(lson,l,r));
    if(r>mid)lrmax=max(lrmax,query(rson,l,r));
    return lrmax;
}
int main(){
    //freopen("longterm_segtree.in","r",stdin);
    //freopen("longterm_segtree.out","w",stdout);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d%d",&n,&k);
    root[1]=build(1,n);
    int x,v,a,b;
    for(int i=1;i<=k;i++){
        scanf("%d%d%d%d",&x,&v,&a,&b);
        if(x==0)printf("%d\n",query(get_root(v),a,b));
        else root[++ver]=update(get_root(v),a,b);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}