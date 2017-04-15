//Problem:[COGS330][NOI2003][Editor]
//Powered By HYS.
//Accepted at 15:49:54,2017/04/15 on COGS.
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#define N 6000010
#define get_size(x) (x?x->size:0)//这样求size可以防止访问空指针
using namespace std;
int node_top=0,n;
struct treap_t{
    treap_t *l,*r;
    int fix,size;
    char key;
    inline void init(char k){
        this->fix=rand();
        this->key=k;
        this->l=this->r=NULL;
        this->size=1;
    }
    inline void update(){
        this->size=1+get_size(l)+get_size(r);
    }
}treap[N],*root;
typedef pair<treap_t*,treap_t*> droot_t;
treap_t *marge(treap_t *a,treap_t* b){//合并
    if(!a)return b;
    if(!b)return a;
    if(a->fix<b->fix){
        a->r=marge(a->r,b);
        a->update();
        return a;
    }
    else{
        b->l=marge(a,b->l);
        b->update();
        return b;
    }
}
droot_t split(treap_t *x,int k){//拆分
    if(!x)return droot_t(NULL,NULL);
    droot_t y;
    if(get_size(x->l)>=k){
        y=split(x->l,k);
        x->l=y.second;
        x->update();
        y.second=x;
    }
    else{
        y=split(x->r,k-get_size(x->l)-1);
        x->r=y.first;
        x->update();
        y.first=x;
    }
    return y;
}
treap_t *newnode(char x){
    treap_t *temp=&treap[++node_top];
    temp->init(x);
    return temp;
}
inline void insert(int v,int l){//插入
    droot_t x=split(root,v);
    char chr;
    treap_t *temp;
    for(int i=1;i<=l;i++){
        scanf("%c",&chr);
        while(chr<32 || chr>126)scanf("%c",&chr);
        temp=newnode(chr);
        x.first=marge(x.first,temp);
    }
    root=marge(x.first,x.second);
}
inline void remove(int k,int l){//删除
    droot_t x=split(root,k);
    droot_t y=split(x.second,l);
    root=marge(x.first,y.second);
}
inline void output(treap_t *x){
    if(x->l)output(x->l);
    printf("%c",x->key);
    if(x->r)output(x->r);
}
int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    freopen("editor2003.in","r",stdin);
    freopen("editor2003.out","w",stdout);
    int temp,lnk=0;
    char command[20];
    droot_t a,b;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",command);
        if(command[0]=='M'){
            scanf("%d",&temp);
            lnk=temp;
        }
        else if(command[0]=='I'){
            scanf("%d",&temp);
            insert(lnk,temp);
        }
        else if(command[0]=='D'){
            scanf("%d",&temp);
            remove(lnk,temp);
        }
        else if(command[0]=='G'){
            scanf("%d",&temp);
            a=split(root,lnk);
            b=split(a.second,temp);
            output(b.first);
            printf("\n");
            a.second=marge(b.first,b.second);
            root=marge(a.first,a.second);
        }
        else if(command[0]=='P')lnk--;
        else if(command[0]=='N')lnk++;
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}