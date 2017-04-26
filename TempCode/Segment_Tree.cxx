//线段树-模板(极小常数)
//Powered By Inv.
//2016/4/25 20:25
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
        node_t *now=&seg[++top];
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
            now->sum=(now->lc->sum+now->rc->sum)%P;
        }
        return now;
    }
    inline void build(int l,int r){//outside
        root=build_in(l,r);
    }
    inline int length(node_t *now){
        return (now->r-now->l)+1;
    }
    inline void pushdown(node_t *now,node_t *lson,node_t *rson){
        lson->mul=(lson->mul*now->mul)%P;
        rson->mul=(rson->mul*now->mul)%P;
        lson->add=(lson->add*now->mul+now->add)%P;
        rson->add=(rson->add*now->mul+now->add)%P;
        lson->sum=(lson->sum*now->mul+length(lson)*now->add)%P;
        rson->sum=(rson->sum*now->mul+length(rson)*now->add)%P;
        now->mul=1;
        now->add=0;
    }
    void mul_update(node_t *now,int l,int r,ll_t s){
        int nl=now->l,nr=now->r;
        if(l<=nl && r>=nr){
            now->mul=(now->mul*s)%P;
            now->sum=(now->sum*s)%P;
            now->add=(now->add*s)%P;
            return;
        }
        node_t *lson=now->lc,*rson=now->rc;
        if(now->add!=0||now->mul!=1)pushdown(now,lson,rson);
        int mid=(nl+nr)>>1;
        if(l<=mid)mul_update(lson,l,r,s);
        if(r>mid)mul_update(rson,l,r,s);
        now->sum=(lson->sum+rson->sum)%P;
    }
    void add_update(node_t *now,int l,int r,ll_t s){
        int nl=now->l,nr=now->r;
        if(l<=nl && r>=nr){
            now->add=(now->add+s)%P;
            now->sum=(now->sum+((length(now)*s)%P))%P;
            return;
        }
        node_t *lson=now->lc,*rson=now->rc;
        if(now->add!=0||now->mul!=1)pushdown(now,lson,rson);
        int mid=(nl+nr)>>1;
        if(l<=mid)add_update(lson,l,r,s);
        if(r>mid)add_update(rson,l,r,s);
        now->sum=(lson->sum+rson->sum)%P;
    }
    ll_t query(node_t *now,int l,int r){
        int nl=now->l,nr=now->r;
        if(l<=nl && r>=nr)return now->sum;
        node_t *lson=now->lc,*rson=now->rc;
        if(now->add!=0||now->mul!=1)pushdown(now,lson,rson);
        ll_t ans=0;
        int mid=(nl+nr)>>1;
        if(l<=mid)ans=(ans+query(lson,l,r))%P;
        if(r>mid)ans=(ans+query(rson,l,r))%P;
        now->sum=(lson->sum+rson->sum)%P;
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
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&c,&a,&b);
        if(c==3)printf("%lld\n",seg.query(seg.root,a,b)%P);//Query.
        else{
            scanf("%lld",&s);
            if(c==1)seg.mul_update(seg.root,a,b,s%P);//Mul.
            else seg.add_update(seg.root,a,b,s%P);//Add.
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}