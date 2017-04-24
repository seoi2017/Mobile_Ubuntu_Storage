#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 100010
int P;//模数
typedef long long ll_t;
struct node_t{
    ll_t sum,mul,add;
    int l,r;
    node_t *lc,*rc;
};
/*
乘法原理:(a*x+b)*c+d=a*x*c+b*c+d
*/
struct Segment_Tree_t{
    node_t seg[N<<2];
    node_t *root;
    int top=0;
    node_t *build_in(int l,int r){//inside
        node_t *now=seg[++top];
        now->l=l,now->r=r;
        now->mul=1,now->add=0;
        if(l==r){
            scanf("%lld",&now->sum);
            now->lc=now->rc=NULL;
        }
        else{
            int mid=(l+r)>>1;
            now->lc=build_in(l,mid);
            now->rc=build_in(mid+1,r);
            now->s=now->lc->sum+now->rc->sum;
        }
        return now;
    }
    inline void build(int l,int r){//outside
        root=build_in(l,r);
    }
    inline int length(node_t *now){
        return (now->r-now->l);
    }
    inline void pushdown(node_t *now,node_t *lson,node_t *rson){
         
    }
    void mul_update(node_t *now,int l,int r,ll_t s){
        if(l<=now->l && r>=now->r){
            now->mul=now->mul*s%P;
            now->sum=now->sum*s%P;
            now->add=now->add*s%P;
            return;
        }
        node_t *lson=now->lc,*rson=now->rc;
        pushdown(now,lson,rson);
        int mid=(now->l+now->r)>>1;
        if(l<=mid)mul_update(lson,l,r);
        if(r>mid)mul_update(rson,l,r);
    }
    void add_update(node_t *now,int l,int r,ll_t s){
        if(l<=now->l && r>=now->r){
            lson
        }
        node_t *lson=now->lc,*rson=now->rc;
        pushdown(now,lson,rson);
        int mid=(now->l+now->r)>>1;
        if(l<=mid)add_update(lson,l,r);
        if(r>mid)add_update(rson,l,r);
    }
    ll_t query(node_t *now,int l,int r){
        if(l<=now->l && r>=now->r)return now->sum;
        node_t *lson=now->lc,*rson=now->rc;
        pushdown(now,lson,rson);
        ll_t ans=0;
        int mid=(now->l+now->r)>>1;
        if(l<=mid)ans+=query(lson,l,r);
        if(r>mid)ans+=query(rson,l,r);
        return ans;
    }
}seg;
//=========================================
int n,m,c,a,b;
ll_t s;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&P);
    seg.build(1,n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&c,&a,&b);
        if(c==3)printf("%lld\n",seg.query()%(1LL*P));//Query.
        scanf("%lld",&s);
        if(c==1)seg.mul_update(a,b,s%(1LL*P));//Mul.
        else seg.add_update(a,b,s%(1LL*P));//Add.
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}