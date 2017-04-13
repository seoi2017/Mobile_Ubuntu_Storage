//可持久化线段树-模板
//Powered By HYS
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
const int N=100010,K=110;//最大节点数和版本数
int ind[K][N]={0};//各版本末节点索引
int root[K]={0};//各版本根节点索引
struct seg_t{//线段树节点
    int ver,maxs,l,r;
    seg_t *lc,*rc,*fa;
}seg[N<<20];//开大点
inline int build(int l,int r){//建树函数
    int temp=++top;
    seg_t *now=&seg[temp];
    now->l=l,now->r=r;
    now->ver=1;//第一版本
    if(l==r){
        lson=rson=NULL;
        scanf("%d",&now->maxs);///边建树边输入
        ind[1][l]=temp;
    }
    else{
        int mid=(l+r)>>1;
        lson=&seg[build(l,mid)];
        rson=&seg[build(mid+1,r)];
        lson->fa=rson->fa=now;
    }
    if(now->l==1 && now->r==n)root[1]=temp;//第一版本
    return temp;
}
inline int update(seg_t *now,int s,seg_t *son=NULL){//从末向上更新
    int temp=++top;
    seg_t *new_now=&seg[temp];//新建节点
    new_now->l=now->l;
    new_now->r=now->r;
    new_now->ver=now->ver+1;
    if(now->l==now->r){
        lson=rson=NULL;
        new_now->maxs=s;
        ind[new_now->ver][new_now->l]=temp;
    }
    else{
        new_now->lc=lson;
        new_now->rc=rson;
    }
    if()new_now->fa=&seg[update(now->fa,s,new_now)];
    if()
    if(now->l==1 && now->r==n)root[new_now->ver]=temp;
    return temp;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d%d\n",&n,&k);
    build(1,n);
    for(int i=1;i<=k;i++){
        scanf("%d%d%d%d\n");
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}