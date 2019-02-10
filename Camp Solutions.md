
[Wannafly Camp补题进度总览表](https://github.com/Dafenghh/Training_Summary/blob/master/Wannafly%20Camp%E8%A1%A5%E9%A2%98%E8%BF%9B%E5%BA%A6%E6%80%BB%E8%A7%88%E8%A1%A8.md)

# Day1  
## A 机器人 By Dafeng [(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day1/A_dafeng.cpp)

经过若干推(W)理(A), 可以得到一个漂亮的结论。先分别求出要经过的A类点和B类点横跨的区间，`[MinA, MaxA]`和`[MinB, MaxB]`. 然后再依次将这两个区间往左右两边扩展，扩展到第一个特殊点，得到新的区间`[LA, RA]`和`[LB, RB]`。（注意对于A，点s也是特殊点）。答案就是区间`[min(LA, LB), max(RA, RB)]`的长度*2，如果要走到B的点，则加上2k.

(根据这个结论，是不是可以出道丧心病狂的动态题呢嘿嘿嘿~)


## B 吃豆豆 By Dafeng [(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day1/B_dafeng.cpp)

其实是常规的DP+倍增套路。首先不要被C的范围(1e18)吓到了。当C很小时，我们可以直接dp.

`dp[t][i][j]`表示第0秒从位置i出发，t秒时到达j时获得的糖水数。

考虑到数组T取值为1..10, 那么取1..10的lcm: 2520, 一定是所有格子的公共周期。知道了这点，就可以搞事情了。

我们可以对所有`t<=2520`的t求出`dp[t][i][j]`, 接着以2520为最小单位，依次倍增求出`dp[2520*2^k][i][j]`.

假设答案具有`A*2520+B`的形式，那么我们可以用求出来的`dp[2520*2^k][i][j]`的值逐位确定A，接着使用`dp[t][i][j], t<=2520`的值确定B，得到答案。

## D 超难的数学题 By Zayin[(未AC代码）](https://paste.ubuntu.com/p/sstjqyhZ38/)[(AC代码）](https://paste.ubuntu.com/p/3c5NX4Gpxr/)  
  PS:样例的答案应该是1464！！！  
  
  此类问题是一种新套路。  
  定义f(n)=[1,n]中满足性质P的数字个数占[1,n]的比例，求解f(n)>=p的最小的n。  
    
  这类问题的解法是先找一个初始解b,并定义a为[1,b]中满足性质P的数字个数，然后根据a和b来调整。  
  怎么调整呢？因为现在的比例是a/b,找到最小的c满足(a+c)/(b+c)>=p,即假设b后面的数字全部满足性质。  
  这是最优的情况，所以无论如何都要调整c这么多，更新b+=c,然后重新计算a，继续迭代直到找到答案。  
    
  可(bu)以(hui)证明最多调整O(log)次便能找到答案。
  
  ~~回到这题，按照上面的套路做即可，但为什么还未AC呢？~~  
  因为假设p=0.99999,那么答案可能非常大。。。~~要实现高精度整数和小数~~。。。弃疗了。。。  
  （经检验unsigned LL范围内p最大是0.9）
  
  --------后更---------  
  实际上并不用实现高精度小数，因为p最多是5位，所以转成p=q/100000的形式，交叉相乘就可以避免使用小数。  
  但依然还是要使用高精度整数（加法，单精乘法，单精除法）。  
  
  看了一下所有AC的，他们估计是真的写了高精度小数，因为我只有69ms，他们最少是699ms。。。。  
  
## H 割葱 By Zayin[(代码点此)](https://paste.ubuntu.com/p/xxbz9mT2PM/)
  令dp[l][r][h][k]表示[l,r]这个区间之前在高度h被割过，还剩k刀可以用的最大值。注意到[l,r]的有效区间只有O(n)个即可。  
  这种类型的题是利用了状态较少的性质————笛卡尔树的节点只有O(n)个。  
  听说类似的题还有[ICPC 2016 Hong Kong G. Scaffolding](ttps://vjudge.net/contest/271028#problem/G) 
  BTW,其实可以不写背包。  

## I 起起落落 By Zayin[(代码点此)](https://paste.ubuntu.com/p/Mq2GGk5mwK/)

## J 夺宝奇兵 [By Dafeng](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day1/J_dafeng.cpp) [By Zayin](https://paste.ubuntu.com/p/qcTxNBB5Gr/)

对除自己外所有人按拥有宝物数降序排序，每个人拥有的宝物按升序排序。

假设拥有宝物最多的人有c个宝物。枚举除自己外所有人拥有宝物的最大数量h，从大到小枚举，即从c枚举到0.

这样每次枚举一个h时，将所有拥有宝物超过h个的人多出的宝物买过来（当然先买便宜的，所以每个人宝物按升序排序），这是第一部分的花费。然后统计下买过来的宝物数量够不够h+1，如果还差k，就从剩下没被取的宝物中买k个最便宜的宝物，这是第二部分的花费。

第一部分的花费可以直接对每个人维护一个队列，按需pop即可。第二部分的花费可以在这些队列的基础上，加一个权值线段树维护。（Zayin写了主席树，做法也差不多吧……）


## K 星球大战 By Zayin[(代码点此）](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day1/K_Zayin.cpp)  
  首先建立1号点的bfs树，邪恶点的入侵一定是按照bfs树的深度入侵的。  
  然后就可以枚举光明点，预处理所有关键点到此光明点的距离，可以轻松计算出关键点被谁占领，关键点的多少级祖先是邪恶光明的分界线。

# Day2
## I Square Subsequences By Zayin[(代码点此）](https://paste.ubuntu.com/p/q4TCR5YNZC/)
  枚举分段点然后左右两边做最长公共子序列即可，但这样是O(n^3)的。  
  使用位运算加速dp，可做到O(n^3/w)，w取120(__int128)。  
  但是这样依然是卡不过去的...~~可能是我常数太大~~，所以要使用一些奇奇怪怪的卡常姿势，~~鬼知道我卡了多久。~~
  
  还有就是__builtin_popcount只能算int的1个数，因为这个也WA了很久。。。  
  [位运算加速dp提交请戳这](https://loj.ac/problem/6564)
  
## L Pyramid By Zayin[(代码点此）](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day2/L_Zayin.cpp)
  一个任意放置的三角形总能恰好被一个正立的三角形套住，剩下的都是推公式了。。。
  
# Day3
## C 小游戏 By Zayin[(代码点此）](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day3/C_Zayin.cpp)
  dp好题！！！非常好！！！  
  重新回顾了姿势：缺什么状态就补上什么状态，直到可以完美表示为止。  
  记dp[i][a][1/2]为以i结尾且该类型的能量是a，当前序列末尾有1/2个。  
  其实往后更新的dp是很容易写的，但会TLE，所以一定要写成从前贡献的dp，用前缀和优化即可。  
  不懂可以直接看代码，挺短的2333.
  
## F 小清新数论 By Zayin[(代码点此）](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day3/F_Zayin.cpp)
  经典杜教筛。  
  sigma (f·g)(i) [1<=i<=n]= sigma (f·g·1)(i)  [1<=i<=n] - sigma (f·g)(n/i)  [2<=i<=n]
  
## H 涂鸦 By Zayin[(代码点此）](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day3/H_Zayin.cpp)
  标记永久化其实还挺好写的...

## J 子序列 By Zayin[(代码点此）](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day3/J_Zayin.cpp)
  我们先考虑一个普通字符串怎么统计子序列个数。  
  记f[i]为以i结尾的子序列个数，sum为当前总子序列个数，初始时sum=1（空串）。  
  每遇到一个字符c，则有f'[c]=sum,sum'=2*sum-f[c]，那么每个字符都可以写成一个转移矩阵。  
  回到这题，字符串的变化是 S <- SaS，那么矩阵对应乘起来即可。  
  类似的题还有[Loj6074](https://loj.ac/problem/6074)


# Day 4

## H 命命命运 By Dafeng [(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day4/H_dafeng.cpp)

我们需要求出对于i号玩家，第j轮，获得第k块地的概率，然后把所有j,k取值下的概率累加起来，就是每个人获得地的块数的期望。i号玩家，获得第j块地等价于`1..(i-1)`号玩家前j轮不曾走到k，i号玩家第j轮第一次走到k，`(i+1)..6`号玩家前(j-1)轮未曾走到k.

于是我们要求出两个概率来，`never[i][j][k]`表示i号玩家前j轮未曾走到k的概率，`first[i][j][k]`表示i号玩家第j轮第一次走到k的概率。

为了求出这两个东西，我们还需要一维状态，即玩家当前所处的位置。所以`pos[i][j][k][m]`表示i号玩家前j轮未曾走到k，走完第i轮后位于m的概率。

转移式很好写出来。于是我们得到了一个个复杂度`O(6*6*500*n^2)`的优秀算法, n为500， 爆了。

那么怎么优化这个东西呢？

突破口在于，pos数组的k只需要求前7块地就可以了。这样由pos的结果得到前7块地的first和never值，而后面8..n块地的first,never值可以直接由前面7块地的first,never值分别递推出来。因为每一轮掷骰子的概率是独立的，跟所处位置无关，j轮移动可以看成1+(j-1)轮，即走完第一轮再走j-1轮。例如，我们求`first[i][j][k]`, 可以枚举第一轮移动的步数t，贡献就是`p[i][t]*first[i][j-1][k-t]`. never同理。

于是我们得到了正解。


# Day 7
## I 集合 By Zayin [(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day7/I_Zayin.cpp)
  题解PPT说的已经很完全了。。。~~其实是个大水题~~

# Day 8
## I 岸边露伴的人生经验 By Zayin[(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day8/I_Zayin.cpp)
  首先做出如下转变 0->00,1->01,2->11,则|x-y|-> (sx^sy)中1的个数。FWT后再统计一下即可。
