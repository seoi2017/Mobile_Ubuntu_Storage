//替罪羊树-模板(面向对象化编程)
//2017/4/16 15:41
//Powered By Inv.
#include <iostream> //库引用
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <vector>
#define N 2100010                     //最大节点数量
#define get_size(x) (x ? x->size : 0) //取以x为根的子树节点数量
using namespace std;
const double alpha = 0.75; //重构常量
struct node_t
{                         //节点结构体
    int size, val, cover; //有效节点数量,节点值,总结点数量
    bool exist;           //是否存在(若被删除,为false)
    node_t *l, *r;        //左右子节点
    inline void maintain()
    {                                                  //更新
        size = (int)exist + get_size(l) + get_size(r); //更新有效节点数
        cover = l->cover + r->cover + 1;               //更新总结点数
    }
    inline bool isbad()
    { //是否需要重构
        return ((l->cover > cover * alpha + 5) || (r->cover > cover * alpha + 5));
    }
};
struct ScapeGoat_Tree_t
{                               //替罪羊树结构体
    node_t node[N];             //节点内存池
    node_t *tail, *root, *null; //申请新节点指针,根节点指针,空节点指针
    node_t *bc[N];              //废弃节点池,用于重利用
    int bc_top;                 //废弃节点数量
    inline void init()
    {                                             //初始化(必须调用)
        tail = node;                              //从内存池第0位申请节点
        null = tail++;                            //第0位分配给空指针
        null->l = null->r = null;                 //空节点无子节点
        null->cover = null->size = null->val = 0; //空节点无数据
        root = null;                              //根节点为空
        bc_top = 0;                               //无废弃指针
    }
    inline node_t *newnode(int k)
    {                                               //申请值为k的新节点
        node_t *p = bc_top ? bc[--bc_top] : tail++; //申请新节点,若有废弃节点则重利用
        p->l = p->r = null;                         //无子节点
        p->size = p->cover = 1;                     //有效结点数和总节点数均为1
        p->exist = true;                            //该节点存在
        p->val = k;                                 //该节点值为k
        return p;                                   //返回此节点
    }
    node_t *divide(vector<node_t *> &v, int l, int r)
    { //二分重排节点,使之符合平衡树性质
        if (l >= r)
            return null;
        int mid = (l + r) >> 1;
        node_t *p = v[mid];
        p->l = divide(v, l, mid);
        p->r = divide(v, mid + 1, r);
        p->maintain();
        return p;
    }
    inline void rebuild(node_t *&p)
    { //重建子树
        static vector<node_t *> v;
        v.clear();
        travel(p, v);
        p = divide(v, 0, v.size());
    }
    void travel(node_t *p, vector<node_t *> &v)
    { //树形遍历,并写入vector
        if (p == null)
            return;
        travel(p->l, v);
        if (p->exist) //存在则写入
            v.push_back(p);
        else //不存在则丢入废弃节点池
            bc[bc_top++] = p;
        travel(p->r, v);
    }
    node_t **insert(node_t *&p, int s)
    { //插入元素(内层,核心)
        if (p == null)
        { //到达末层,插入节点
            p = newnode(s);
            return &null;
        }
        p->size++;
        p->cover++;
        node_t **res = insert((s >= p->val ? p->r : p->l), s); //依据大小分配到左右子树
        if (p->isbad())                                        //需要重构
            res = &p;                                          //返回重构节点
        return res;                                            //返回节点,若不需重构,应为空节点
    }
    inline void insert(int s)
    {                                 //插入元素(外层,重载)
        node_t **p = insert(root, s); //插入节点
        if (*p != null)               //若需重构
            rebuild(*p);              //重构节点
    }
    void remove(node_t *p, int id)
    { //删除名次为id的节点(内层,核心)
        p->size--;
        int offset = p->l->size + (int)p->exist;
        if (p->exist && id == offset)
        {
            p->exist = false;
            return;
        }
        else
        {
            if (id <= offset)
                remove(p->l, id);
            else
                remove(p->r, id - offset);
        }
    }
    inline int rank(int s)
    { //非递归取s名次
        node_t *now = root;
        int ans = 1;
        while (now != null)
        {
            if (now->val >= s)
                now = now->l;
            else
            {
                ans += now->l->size + (int)now->exist;
                now = now->r;
            }
        }
        return ans;
    }
    inline int get_kth(int k)
    { //非递归取第k名
        node_t *now = root;
        while (now != null)
        {
            if (now->l->size + 1 == k && (int)now->exist)
                return now->val;
            else if (now->l->size >= k)
                now = now->l;
            else
            {
                k -= now->l->size + (int)now->exist;
                now = now->r;
            }
        }
    }
    inline void remove(int k)
    {                          //删除值为k的节点(外层,重载)
        remove(root, rank(k)); //取得名次
        if (root->size < alpha * root->cover)
            rebuild(root); //若需重构则重构
    }
    inline void remove_kth(int k)
    { //删除名次为k的节点(外层)
        remove(root, k);
        if (root->size < alpha * root->cover)
            rebuild(root); //若需重构则重构
    }
} sct; //替罪羊树sct
//取前驱使用sct.get_kth(sct.rank(s) - 1);
//取后继使用sct.get_kth(sct.rank(s + 1));
//=============================
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, c, s;
    while (scanf("%d", &n) != EOF)
    {
        sct.init();
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &c, &s);
            if (c == 1)
                sct.insert(s);
            if (c == 2)
                sct.remove(s);
            if (c == 3)
                printf("%d\n", sct.rank(s));
            if (c == 4)
                printf("%d\n", sct.get_kth(s));
            if (c == 5)
                printf("%d\n", sct.get_kth(sct.rank(s) - 1));
            if (c == 6)
                printf("%d\n", sct.get_kth(sct.rank(s + 1)));
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}