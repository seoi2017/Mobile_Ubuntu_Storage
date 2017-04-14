//可持久化线段树-模板(单点修改+区间查询)
//2017/4/14 08:42
//Powered By Inv.
#include <iostream> //库引用
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <algorithm>
#define lson (now->lc) //左子节点
#define rson (now->rc) //右子节点
using namespace std;
const int N = 10010, K = 100010; //最大节点数N和版本数K
int n, k, top = 0, ver = 1;      //节点索引top和版本索引ver
struct seg_t
{                         //线段树节点
    int maxs, l, r;       //区间最大值,区间左右端点值
    seg_t *lc, *rc;       //左右子节点指针
} seg[N * 700], *root[K]; //节点内存池和根节点索引指针;节点数量要开大点,视题目而定
inline seg_t *build(int l, int r)
{                                //l到r区间建树
    seg_t *now = &seg[++top];    //申请新节点
    now->l = l, now->r = r;      //左右端点确定
    if (l == r)                  //是最末层节点
        scanf("%d", &now->maxs); //边建树边读入
    else
    {                                            //不是最末层节点
        int mid = (l + r) >> 1;                  //取中间值
        lson = build(l, mid);                    //左子节点
        rson = build(mid + 1, r);                //右子节点
        now->maxs = max(lson->maxs, rson->maxs); //更新区间最大值
    }
    return now; //返回此节点
}
inline seg_t *update(seg_t *old, int x, int s)
{                               //单点x更新为s,自上而下
    seg_t *now = &seg[++top];   //申请新版本节点
    int l = old->l, r = old->r; //旧版本同一节点左右端点值
    now->l = l, now->r = r;     //与旧版本同一节点左右端点值保持一致
    if (l == r)                 //是最末层节点
        now->maxs = s;          //直接更新
    else
    {                           //不是最末层节点
        int mid = (l + r) >> 1; //取中间值
        if (x <= mid)
        {                                 //要更新的点在左半区域
            rson = old->rc;               //右子节点与旧版本保持一致
            lson = update(old->lc, x, s); //左子节点更新
        }
        else
        {                                 //要更新的点在右半区域
            lson = old->lc;               //左子节点与旧版本保持一致
            rson = update(old->rc, x, s); //右子节点更新
        }
        now->maxs = max(lson->maxs, rson->maxs); //更新区间最大值
    }
    return now; //返回此节点
}
inline int query(seg_t *now, int l, int r)
{                                                 //查询l到r区间最大值
    if (l <= now->l && r >= now->r)               //此区间全部处于查询范围内
        return now->maxs;                         //直接返回区间最大值
    int lrmax = -1, mid = (now->l + now->r) >> 1; //临时最大值变量lrmax,并取中间值
    if (l <= mid)                                 //左半区域有要查询的部分
        lrmax = max(lrmax, query(lson, l, r));    //查询左子节点并更新临时最大值
    if (r > mid)                                  //右半区域有要查询的部分
        lrmax = max(lrmax, query(rson, l, r));    //查询右子节点并更新临时最大值
    return lrmax;                                 //返回区间最大值
}
int main()
{                                       //主函数
    freopen("input.txt", "r", stdin);   //文件读入
    freopen("output.txt", "w", stdout); //文件输出
    scanf("%d%d", &n, &k);              //初始数列数字总数n和查询\修改总数k
    root[1] = build(1, n);              //建树+读入,并得到初始版本根节点
    for (int i = 1; i <= k; i++)
    {                                             //循环读入查询\修改
        int x, v, a, b;                           //临时变量
        scanf("%d%d%d%d", &x, &v, &a, &b);        //读入查询\修改
        if (x == 0)                               //查询
            printf("%d\n", query(root[v], a, b)); //查询v版本的a到b区间最大值
        else                                      //修改
            root[++ver] = update(root[v], a, b);  //修改v版本的a点值为b,并得到新版本根节点
    }
    fclose(stdin);  //关闭输入流
    fclose(stdout); //关闭输出流
    return 0;
}