### 线段树-数据结构-算法笔记
## 应用：扫描线
# 序
扫描线是线段树的一种应用，广泛适用于下列题目：
二维：周长并、周长交、面积并、面积交；
三维：体积交、体积并；
并常与离散化配合使用。
# 注意事项
通常的说，一般的线段树在建树时会细分到l==r，如下所示：
              |-------------[1,6]-------------|
      |-----[1,3]-----|               |-----[4,6]-----|
  |-[1,2]-|         [3,3]         |-[4,5]-|         [6,6]
[1,1]   [2,2]                   [4,4]   [5,5]
但由于扫描线题目大多是几何题目，用标准线段树模式会导致宽度（区间）长度为零，
所以我们以如下方式建树：
              |=============[1,6]=============|
      |=====[1,3]=====|               |=====[3,6]=====|
    [1,2]           [2,3]           [3,4]         |=[4,6]=|
                                                [4,5]   [5,6]
不难看出，在扫描线的应用中，我们最小划分区间为1，每一段对应离散化两点间的线段。
而且，我们建树的时候不再以lson=(l,mid),rson=(mid+1,r)建树了，
而是以lson=(l,mid),rson=(mid,r)建树，因为如果还像以前一样的话，那就会丢失线段。
# 核心思想
# 离散化端点
# 扫描线段
# 更新（插入线段）
# 模板代码
见～/TempCode/Segtree_ScanLine.cc
# 例题
[POJ1177][COGS263]|[IOI1998][矩形周长\Picture]|[周长并]
[UVa11983]|[广告张贴]|[K次面积交]