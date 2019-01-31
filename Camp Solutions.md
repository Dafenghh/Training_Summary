# Day1  

## B 吃豆豆 By Dafeng [(代码点此)](https://github.com/Dafenghh/Training_Summary/blob/master/code/CCPC_Wannafly_Camp_2019/day1/b_dafeng.cpp)

其实是常规的DP+倍增套路。首先不要被C的范围(1e18)吓到了。当C很小时，我们可以直接dp.

`dp[t][i][j]`表示从第位置i出发，t秒后到达j时获得的糖水数。

考虑到数组T取值为1..10, 那么取1..10的lcm: 2520, 一定是所有格子的公共周期。知道了这点，就可以搞事情了。

我们可以对所有`t<=2520`的t求出`dp[t][i][j]`, 接着以2520为最小单位，依次倍增求出`dp[2520*2^k][i][j]`.

假设答案具有`A*2520+B`的形式，那么我们可以用求出来的`dp[2520*2^k][i][j]`的值逐位确定A，接着使用`dp[t][i][j], t<=2520`的值确定B，得到答案。

## D 超难的数学题 By Zayin[(未AC代码）](https://paste.ubuntu.com/p/sstjqyhZ38/)[(AC代码）](https://paste.ubuntu.com/p/3c5NX4Gpxr/)  
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

## J 夺宝奇兵 By Zayin[(代码点此）](https://paste.ubuntu.com/p/qcTxNBB5Gr/)

# Day2
## I Square Subsequences By Zayin[(代码点此）](https://paste.ubuntu.com/p/q4TCR5YNZC/)
  枚举分段点然后左右两边做最长公共子序列即可，但这样是O(n^3)的。  
  使用位运算加速dp，可做到O(n^3/w)，w取120(__int128)。  
  但是这样依然是卡不过去的...~~可能是我常数太大~~，所以要使用一些奇奇怪怪的卡常姿势，~~鬼知道我卡了多久。~~
  
  还有就是__builtin_popcount只能算int的1个数，因为这个也WA了很久。。。
  