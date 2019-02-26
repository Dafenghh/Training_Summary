
[Wannafly Camp补题进度总览表](https://github.com/Dafenghh/Training_Summary/blob/master/Wannafly%20Camp%E8%A1%A5%E9%A2%98%E8%BF%9B%E5%BA%A6%E6%80%BB%E8%A7%88%E8%A1%A8.md)

# Day1  
## A 机器人 By Dafeng [(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day1/A_dafeng.cpp)

经过若干推(W)理(A), 可以得到一个漂亮的结论。先分别求出要经过的A类点和B类点横跨的区间，`[MinA, MaxA]`和`[MinB, MaxB]`. 然后再将这两个区间往左右两边扩展，扩展到第一个特殊点，得到新的区间`[LA, RA]`和`[LB, RB]`。（注意对于A，点s也是特殊点）。答案就是区间`[min(LA, LB), max(RA, RB)]`的长度*2，如果要走到B的点，则加上2k.

(根据这个结论，是不是可以出道丧心病狂的动态题呢嘿嘿嘿~)


## B 吃豆豆 By Dafeng [(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day1/B_dafeng.cpp)

其实是常规的DP+倍增套路。首先不要被C的范围(1e18)吓到了。当C很小时，我们可以直接dp.

`dp[t][i][j]`表示第0秒从位置i出发，t秒时到达j时获得的糖水数。

考虑到数组T取值为1..10, 那么取1..10的lcm: 2520, 一定是所有格子的公共周期。知道了这点，就可以搞事情了。

我们可以对所有`t<=2520`的t求出`dp[t][i][j]`, 接着以2520为最小单位，依次倍增求出`dp[2520*2^k][i][j]`.

假设答案具有`A*2520+B`的形式，那么我们可以用求出来的`dp[2520*2^k][i][j]`的值逐位确定A，接着使用`dp[t][i][j], t<=2520`的值确定B，得到答案。

## D 超难的数学题 By Zayin  [未AC代码](https://paste.ubuntu.com/p/sstjqyhZ38/)[AC代码](https://paste.ubuntu.com/p/3c5NX4Gpxr/)  [Java版本](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day1/D_dafeng.java)

  PS:样例的答案应该是1464！！！  太过分了！！
  
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
  听说类似的题还有[ICPC 2016 Hong Kong G. Scaffolding](https://vjudge.net/contest/271028#problem/G) 
  BTW,其实可以不写背包。  

## I 起起落落 By Zayin[(代码点此)](https://paste.ubuntu.com/p/Mq2GGk5mwK/)

## J 夺宝奇兵 [By Dafeng](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day1/J_dafeng.cpp) [By Zayin](https://paste.ubuntu.com/p/qcTxNBB5Gr/)

对除自己外所有人按拥有宝物数降序排序，每个人拥有的宝物按升序排序。

假设拥有宝物最多的人有c个宝物。枚举除自己外所有人拥有宝物的最大数量h，从大到小枚举，即从c枚举到0.

这样每次枚举一个h时，将所有拥有宝物超过h个的人多出的宝物买过来（当然先买便宜的，所以每个人宝物按升序排序），这是第一部分的花费。然后统计下买过来的宝物数量够不够h+1，如果还差k，就从剩下没被取的宝物中买k个最便宜的宝物，这是第二部分的花费。

第一部分的花费可以直接对每个人维护一个队列，按需pop即可。第二部分的花费可以在这些队列的基础上，加一个权值线段树维护。（Zayin写了主席树，做法也差不多吧……）


## K 星球大战 By Zayin[(代码点此）](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day1/K_Zayin.cpp)  
  首先建立1号点的bfs树，邪恶点的入侵一定是按照bfs树的深度入侵的。  
  bfs树以外的边包含的点可视为关键点。
  然后就可以枚举光明点，预处理所有关键点到此光明点的距离，可以轻松计算出关键点被谁占领，关键点的多少级祖先是邪恶光明的分界线。

# Day2

## G Routes By Zayin[(代码点此）](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day2/G_Zayin.cpp)
  观察一：任意两点的最短路不超过2k-1.  
    
  首先从一个城市到另外一个城市只有两种本质不同路径，一种是不用热气球，一种是用热气球。  
  所以基本想法就是把任意两个点的min（不用热气球，用热气球）加起来。  
  不用热气球相当于只能在铁路上走，所以距离就等于|i-j|，暴力枚举某个点左右O(k)个点即可（因为|i-j|要不超过2k-1），这个很容易。  
  下面讨论怎么计算用热气球的路径总和。  
    
  先规定符号:  
  col[i]表示i号点的颜色;  
  f[i][c]表示i号点到颜色c的最短距离;  
  g[a][b]表示颜色a到颜色b的最短距离。  
    
  那么i到j用了热气球的最短路为min(f[i][c]+f[j][c]+1),+1表示在c这里用了一次热气球。  
  暴力枚举是O(n^2·k)的。  
  
  观察二：g[col[i]][c]<=f[i][c]<=g[col[i]][c]+1,即点到团的距离至多是团到团的距离加一。  
  推论：g[col[i]][col[j]]<=dis(i,j)<=g[col[i]][col[j]]+2。  
    
  那么可令一个二进制串sta[i]表示i这个点f和g的差，换言之，如果g[col[i]][c]==f[i][c],则sta[i]的第c位是0，否则为1.   
    
  如果枚举起点i，终点的颜色b，中转热气球是a，那么用预处理的sta[]可以做到O(nk^2)，这里不做过多阐述。   
    
  考虑枚举起点i的颜色a，终点j的颜色b。  
  那么a到b的路径大概可以分成一下几类：  
  1、dis(i,j)==g[a][b]且i->j用过热气球。  
  2、dis(i,j)==g[a][b]但i->j没用过热气球。  
  3、dis(i,j)==g[a][b]+1且i->j用过热气球。  
  4、dis(i,j)==g[a][b]+1但i->j没用过热气球。  
  5、dis(i,j)==g[a][b]+2.  
    
  5是最容易的，因为如果dis(i,j)==g[a][b]+2的话，中间一定用过热气球。  
  1、3也很容易，因为走过去的时候就用过热气球了。  
  考虑2和4，因为走过去的时候没用过热气球，所以要在a或b那里额外再用一次，答案额外+1。  
  
  那么只要利用预处理的sta[]还有另外一些东西就可以统计出以上五种路径的数量，那么就做完了。  
  
  
  复杂度是O(nk+k^3+k^2·2^k)：  
  O(nk)是算f[][]和暴力枚举不走热气球的复杂度，O(k^3)是算g[][]还有一些奇奇怪怪的预处理，  
  O(k^2·2^k)是O(k^2)枚举起点终点O(2^k)统计路径条数  以及  一些二进制卷积之类的。 
    
  ##### 感想  
  
  这不仅是一道思维题，还是一道考验编程能力的题。。。  
  首先把i转成二进制就已经很神奇了，更神奇还在后面预处理中转点和统计路径，~~是我没见过的船新二进制技巧，orztls~~  
  另外有一些写预处理的方法，就算理论复杂度是对的，但也有可能会T，所以要更深的琢磨怎么预处理，~~反正这题就是太神仙了~~。  
    
  强烈建议把这题补了！！！  
  还有一道类似但非常简单的二进制处理题[HDU5823](http://acm.hdu.edu.cn/showproblem.php?pid=5823)  
  
## I Square Subsequences By Zayin[(代码点此）](https://paste.ubuntu.com/p/q4TCR5YNZC/)
  枚举分段点然后左右两边做最长公共子序列即可，但这样是O(n^3)的。  
  使用位运算加速dp，可做到O(n^3/w)，w取120(__int128)。  
  但是这样依然是卡不过去的...~~可能是我常数太大~~，所以要使用一些奇奇怪怪的卡常姿势，~~鬼知道我卡了多久。~~
  
  还有就是__builtin_popcount只能算int的1个数，因为这个也WA了很久。。。  
  [位运算加速dp提交请戳这](https://loj.ac/problem/6564)
  
## J Square Substrings By Zayin[(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day2/J_Zayin.cpp)
  其实我看得不太懂题解ppt在说啥。。。下面是我YY的做法。
  对于一个平方字串s[l..r],如果我们把(l,r)画在二维平面上，那么询问(L,R)就是问一个矩形（实际上是一个三角形，因为l<r,L<R）内点的个数。  
  那么其实做法就很显然了，先把所有平方串抠出来转成二维点，再询问矩形（三角形）内点的个数。  
  如果平方串的个数很少的话，那么这是一个经典的数据结构题。  
  但我们可以构造出类似aaaaaa形式的串，这样的话平方串个数是O(n^2)的。  
  回忆我们用后缀数组找平方串的过程，其实我们找的是平方字串组（开始下标连续且长度相同），那么最多有O(nlogn)个平方组。  
  所以这题其实就是给出不超过O(nlogn)段斜率为1的离散点，询问一个矩形（三角形）内点的个数，这个随便用一些数据结构瞎搞就可以了。  
  复杂度为O(p(n)logn+qlogn),p(n)是平方组的个数。  
  而事实上，根据[runs theorem](http://cn.arxiv.org/pdf/1406.0263v7),一个串的runs(极大平方字串组)个数是O(n)级别的。  
  所以真正的复杂度是O(nlogn+mlogn)。  
  
  
  ## 吐槽
  首先是对群里一些人的吐槽，TM我问一个问题，一堆人给出不知道是什么的答案，整整带偏我一个星期。。。
  ```
  BTW：平方串的个数是O(n)级别。  
  这句话可以有两种解释。 
  一：一个串的极大平方字串组的个数是O(n)级别的，这个是这题要用到的结论（其实也没啥用，证明复杂度而已。。。）  
  二：一个串本质不同的（本原）平方字串个数是O(n)级别的，这个TM就是群里一堆人给的答案，不过也好，起码学习了一波先进的字符串姿势~  
  ```
  其次是对OJ的吐槽，这个OJ评测可不可以再苟一点。。。真的是活活被这个OJ气si。。。  
  
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

# Day 5

## B Diameter By Zayin[(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day5/B_Zayin.cpp)
其实真的是可以做到O( (nlogn)^2 )的。。。因为转移是个卷积的形式，所以理论上套个分治FFT就可以做到一轮转移O(nlog^2n)。。。  
但从实际效果来看。。。emmmmmmm。。。FFT常数太大。。。任意模数导致常数又要乘个4。。。CDQ。。。感觉常数乘起来比n还大了。。。  
~~专心优化常数吧~~

## C Division By Zayin[(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day5/C_Zayin.cpp)

## F Kropki By Zayin[(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day5/F_Zayin.cpp)
  考虑容斥，首先肯定是规定哪些位置一定要满足两倍关系，其他任意，然后统计这种规定下的方案数，暴力算至少是O(2^n)的。  
  可以观察到，根据上述规定，一条长度为n的数链被划分为若干条不相干的短链，实际上就是对n进行整数拆分，所以状态数是P(n)=20W，不至于O(2^n)。  
  统计方案数其实是一个相同的过程，所以这题就轻易解决了，时间复杂度为O(P(n)*n).  
  类似的题还有今年青岛的某道容斥题，还有某场opentrain的压缩状态数的题（忘记哪场了）。。。

## G Least Common Multiple[(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day5/G_Zayin.cpp)
  首先转化原问题，可证(cai)明(ce)答案就是max PI(x+ai)/LCM(x+ai),因为x^n与 PI(x+ai)其实是同阶无穷大。 
  观察上式，等价于求 算LCM(x+ai) 时最多可以除掉多大的数。  
  那么根据中国剩余定理，每个素数贡献独立（可以根据x mod p^e的取值还原出x）。  
  对于一个素数p，假设LCM中p的指数是e，那么一定存在一个i使得p^e|x+ai(LCM的性质)，所以对于其他的j，x+aj中p的指数就被除掉了。  
  枚举e和i，统计剩下的j对指数的贡献即可。  
 
## H Nested Tree By Zayin[(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day5/H_Zayin.cpp)
  其实思路和普通的树上计数没什么区别。。。  
  赛场上想到的是虚树，所以觉得很难打，其实可以直接写树剖，超级容易写。。。  
  PS：我已深深地爱上了标记永久化的线段树【呲嘴笑】.
  

# Day 7
## B 重新定义字典序 By Zayin[(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day7/B_Zayin.cpp)
  枚举B中是第p[k]小的数小于A，然后就相当于给出两个大小分别为x，y的数集，问在这两个集合中选出t个数，并且x中选的数的个数不少于p的方案数。  
  直接暴力枚举x或y中选的个数是O(n^2)的，但如果是枚举x和y的最小集合中选的数个数，复杂度就降到了O(nlogn)，因为一个位置最多被枚举O(logn)次。  
  
## I 集合 By Zayin [(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day7/I_Zayin.cpp)
  题解PPT说的已经很完全了。。。~~其实是个大水题~~
 
## J 强壮的排列 By Zayin [(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day7/J_Zayin.cpp)
  神仙题。。。真的神仙题。。。我对生成函数计数一无所知【喷血】。。。

# Day 8
## I 岸边露伴的人生经验 By Zayin[(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day8/I_Zayin.cpp)
  首先做出如下转变 0->00,1->01,2->11,则|x-y|-> (sx^sy)中1的个数。FWT后再统计一下即可。
